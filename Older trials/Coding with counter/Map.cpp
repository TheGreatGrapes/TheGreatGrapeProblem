#include <iostream>
#include "Map.h"
#include "Car.h"

using namespace std;

Map::Map() {
}

Map::~Map() {
}

/////// Streets / Equations ///////

void Map::yEqualsZero(Car* obj, int velo) {
    obj->indexX += velo;              // Increment of index X per loop
    obj->indexY = obj->indexX * 0 + 0; // Result of index Y accordingly
}

void Map::xEqualsZero(Car& obj, int velo) {
    obj.indexY += velo;
    obj.indexX = obj.indexY * 0 + 0;
}

void Map::xEqualsTwenty(Car& obj, int velo) {
    obj.indexY += velo;
    obj.indexX = obj.indexY * 0 + 4;
}
