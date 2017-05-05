#ifndef MAP_H
#define MAP_H
#include "Car.h"

class Map{

public:
    Map();
    ~Map();


    //// Functions ////
    void yEqualsZero(Car*, int velo);   // y = 0
    void xEqualsZero(Car&, int velo);   // x = 0
    void xEqualsTwenty(Car&, int velo); // x = 20
    
};

#endif // MAP_H
