#include "OsmLogger.hpp"
#include "Eigen/Core"
#include <vector>

int main(void)
{
    std::vector<Eigen::Vector2d> pts{Eigen::Vector2d(22.4, 2.4), Eigen::Vector2d(22.3, 2.6)};
    OsmLogger::instance().log(pts, {{"Hello", "there"}});

    OsmLogger::instance().osm_xml.print(std::cout);

    return 0;
}