#pragma once

#include "Eigen/Core"
#include "pugixml.hpp"

#include <vector>
#include <iostream>
#include <map>

class OsmLogger
{
public:
    static OsmLogger &instance()
    {
        static OsmLogger instance;
        return instance;
    }

    OsmLogger(const OsmLogger &) = delete;
    void operator=(const OsmLogger &) = delete;

    void log(const std::vector<Eigen::Vector3d> &pts, const std::map<std::string, std::string> tags = {})
    {
        std::vector<Eigen::Vector2d> pts_2d(pts.size());
        std::transform(pts.begin(), pts.end(), pts_2d.begin(), [](const Eigen::Vector3d &pt) { return pt.head(2); });
        this->log(pts_2d, tags);
    }

    void log(const std::vector<Eigen::Vector2d> &pts, const std::map<std::string, std::string> tags = {})
    {
        std::vector<std::size_t> osm_node_ids;
        osm_node_ids.reserve(pts.size());
        for (const Eigen::Vector2d &pt : pts)
        {
            osm_node_ids.push_back(cur_id++);
            pugi::xml_node osm_node = osm_xml.child("osm").append_child("node");
            osm_node.append_attribute("id") = osm_node_ids.back();
            osm_node.append_attribute("version") = 1;
            osm_node.append_attribute("lat") = pt.x();
            osm_node.append_attribute("lon") = pt.y();
        }

        pugi::xml_node osm_way = osm_xml.child("osm").append_child("way");
        osm_way.append_attribute("id") = cur_id++;
        osm_way.append_attribute("version") = 1;
        for (const std::size_t osm_id : osm_node_ids)
            osm_way.append_child("nd").append_attribute("ref") = osm_id;

        for (const std::pair<std::string, std::string> &tag : tags)
        {
            pugi::xml_node osm_way_tag = osm_way.append_child("tag");
            osm_way_tag.append_attribute("k") = tag.first.c_str();
            osm_way_tag.append_attribute("v") = tag.second.c_str();
        }
    }

    void dump(const std::string filename)
    {
        osm_xml.save_file(filename.c_str());
    }

    pugi::xml_document osm_xml;

private:
    OsmLogger()
    {
        osm_xml.append_child("osm").append_attribute("version") = "0.6";
    }

    std::size_t cur_id = 1000;
};