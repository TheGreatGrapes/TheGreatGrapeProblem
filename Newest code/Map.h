#ifndef MAP_H
#define MAP_H
#include "Car.h"



class Map {

public:
    Map();
    ~Map();
    

//////////////// Vertical Street ////////////////////

    void xEquals_0(Car*, bool); // x = 0
    void xEquals_120(Car*, bool); // x = 4
    void xEquals_240(Car*, bool);  // x = 8

//////////////// Horizontal Street //////////////////
    void yEquals_0(Car*, bool); // y = 0
    void yEquals_120(Car*, bool); // y = 4
    void yEquals_240(Car*, bool);  // y = 8


//////////////// Other Functions //////////////////
    void checkDirX(Car* obj, double, bool);
    void checkDirY(Car* obj, double, bool);
    void printPos(Car *, double);

};

#endif // MAP_H
