# OsmLogger

Simple C++11 Logger for logging positional data to an osm file

## Compile
```bash
g++ -std=c++11 `pkg-config --cflags --libs pugixml eigen3` test.cpp -o test
```

## Example
```c++
#include "OsmLogger.hpp"
...
OsmLogger::instance().log(std::vector<Eigen::Vector2d>{Eigen::Vector2d(22.4, 2.5)}, {{"Hello", "there"}});
```
