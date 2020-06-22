#pragma once

#include "Eigen/Core"
#include "pugixml.hpp"

#include <vector>
#include <iostream>
#include <map>

class OsmLogger
{
    using IdType = std::size_t;

public:
    static OsmLogger &instance()
    {
        static OsmLogger instance;
        return instance;
    }

    OsmLogger(const OsmLogger &) = delete;
    void operator=(const OsmLogger &) = delete;

    void dump(const std::string &filename)
    {
        osm_xml.save_file(filename.c_str());
    }

    /*containers of points*/
    template <typename T, typename std::enable_if_t<!std::is_arithmetic<T>::value> * = nullptr>
    void log(const std::vector<T> &vec)
    {
        std::vector<IdType> osm_node_ids(vec.size());
        for (std::size_t idx = 0; idx < vec.size(); idx++)
            osm_node_ids[idx] = log(vec.at(idx));
        add_way(osm_node_ids.data(), osm_node_ids.size());
    }

    template <typename T, std::size_t S, typename std::enable_if_t<!std::is_arithmetic<T>::value> * = nullptr>
    void log(const std::array<T, S> &arr)
    {
        std::array<IdType, S> osm_node_ids;
        for (std::size_t idx = 0; idx < S; idx++)
            osm_node_ids[idx] = log(arr.at(idx));
        add_way(osm_node_ids.data(), osm_node_ids.size());
    }

    /*point containers*/
    template <typename T, std::size_t S, typename std::enable_if_t<std::is_arithmetic<T>::value> * = nullptr>
    IdType log(const std::array<T, S> &arr)
    {
        static_assert(S > 1, "array size must be > 1");
        return log(arr.data());
    }

    template <typename T, typename std::enable_if_t<std::is_arithmetic<T>::value> * = nullptr>
    IdType log(const std::vector<T> &vec)
    {
        assert(vec.size() > 1);
        return log(vec.data());
    }

    template <typename T, int S, typename std::enable_if_t<std::is_arithmetic<T>::value> * = nullptr>
    IdType log(const Eigen::Matrix<T, S, 1> &vec)
    {
        static_assert(S > 1, "vector size must be > 1");
        return log(vec.data());
    }

    pugi::xml_document osm_xml;

private:
    OsmLogger()
    {
        osm_xml.append_child("osm").append_attribute("version") = "0.6";
    }

    template <typename T, typename std::enable_if_t<std::is_arithmetic<T>::value> * = nullptr>
    IdType log(const T *const data)
    {
        pugi::xml_node osm_node = osm_xml.child("osm").append_child("node");
        osm_node.append_attribute("id") = std::to_string(cur_id).c_str();
        osm_node.append_attribute("version") = 1;
        osm_node.append_attribute("lat") = std::to_string(data[0]).c_str();
        osm_node.append_attribute("lon") = std::to_string(data[1]).c_str();
        return cur_id++;
    }

    IdType add_way(const IdType *const begin, const std::size_t size)
    {
        pugi::xml_node osm_way = osm_xml.child("osm").append_child("way");
        osm_way.append_attribute("id") = cur_id;
        osm_way.append_attribute("version") = 1;
        for (std::size_t idx = 0; idx < size; idx++)
            osm_way.append_child("nd").append_attribute("ref") = std::to_string(begin[idx]).c_str();
        return cur_id++;
    }

    IdType cur_id = 1000;
};
