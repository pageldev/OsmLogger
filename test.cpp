#include "OsmLogger.hpp"

int main(void)
{
    std::vector<Eigen::Vector2d> pts{Eigen::Vector2d(1, 2), Eigen::Vector2d(3, 4)};
    std::vector<Eigen::Vector3d> pts_3d{Eigen::Vector3d(1, 2, 3), Eigen::Vector3d(4, 5, 6)};

    OsmLogger::instance().log(pts);
    OsmLogger::instance().log(pts_3d, {{"Hello", "there"}});
    OsmLogger::instance().osm_xml.print(std::cout);
    
    return 0;
}