#include "OsmLogger.hpp"
#include "Eigen/Core"

#include <array>
#include <vector>

int main(void)
{
    std::array<double, 2> arr{410, 420};
    OsmLogger::instance().log(arr);

    std::vector<double> vec{69, 402};
    OsmLogger::instance().log(vec);

    const Eigen::Vector3d pt(8800, 1, 2);
    OsmLogger::instance().log(pt);

    std::array<Eigen::Vector3d, 2> pts_arr{Eigen::Vector3d(11, 22, 33), Eigen::Vector3d(44, 55, 66)};
    OsmLogger::instance().log(pts_arr);

    std::vector<Eigen::Vector3d> pts_vec{Eigen::Vector3d(77, 88, 0), Eigen::Vector3d(99, 11, 0)};
    OsmLogger::instance().log(pts_vec);

    OsmLogger::instance().osm_xml.save(std::cout);

    return 0;
}