#ifndef MAP_H
#define MAP_H
#include "Car.h"

class Map {

public:
    Map();
    ~Map();

    //// Functions ////

//////////////// Vertical Street ////////////////////
    void xEqualsZero(Car*, int, bool); // x = 0
    void xEqualsFive(Car*, int, bool); // x = 4
    void xEqualsTen(Car*, int, bool);  // x = 8

//////////////// Horizontal Street //////////////////
    void yEqualsZero(Car*, int, bool); // y = 0
    void yEqualsFive(Car*, int, bool); // y = 4
    void yEqualsTen(Car*, int, bool);  // y = 8
};

#endif // MAP_H
