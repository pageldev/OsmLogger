# OsmLogger

Simple C++14 Logger for logging positional data to an osm file

Pass a vector or an array of point types *(point type can be an array, vector or an Eigen::Matrix<T, S, 1>)* or a point type to **OsmLogger::log** to add it to the Osm XML. Use OsmLogger::dump or access OsmLogger::osm_xml directly.

## Compile
```bash
g++ -std=c++14 `pkg-config --cflags --libs pugixml eigen3` test.cpp -o test
```

## Example
```c++
#include "OsmLogger.hpp"
...
OsmLogger::instance().log(std::vector<Eigen::Vector3d>{Eigen::Vector3d(77, 88, 0), Eigen::Vector3d(99, 11, 0)});
```
