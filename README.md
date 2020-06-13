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
OsmLogger::instance().log({Eigen::Vector2d(42.1, 44.0)}, {{"Hello", "there"}});
```
