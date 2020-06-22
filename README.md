# OsmLogger

Simple C++14 Logger for logging positional data to an osm file

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
