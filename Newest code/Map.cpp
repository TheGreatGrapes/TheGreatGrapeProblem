#include "Map.h"
#include <iostream>

using namespace std;
Map::Map() {
}

Map::~Map() {
}

///////////////////////// Streets / Equations //////////////////////////////
/////////////////////////// Vertical Street ////////////////////////////////
void Map::yEqualsZero(Car* obj, int velo, bool dir) {
    for(int i = 0; i < 5; i++) {
        if(dir == 1)  obj->indexX += velo;               // Increment of index X per loop
        else          obj->indexX -= velo;
        
        obj->indexY = obj->indexX * 0 + 0; // Result of index Y accordingly
        cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
    }
}
void Map::yEqualsFive(Car* obj, int velo, bool dir) {
    for(int i = 0; i < 5; i++) {
        if(dir == 1)  obj->indexX += velo;               // Increment of index X per loop
        else          obj->indexX -= velo;    
        
        obj->indexY = obj->indexX * 0 + 5; // Result of index Y accordingly
        cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
    }
}
void Map::yEqualsTen(Car* obj, int velo, bool dir) {
    for(int i = 0; i < 5; i++) {
        if(dir == 1)  obj->indexX += velo;                // Increment of index X per loop
        else          obj->indexX -= velo;
        obj->indexY = obj->indexX * 0 + 10; // Result of index Y accordingly
        cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
    }
}

///////////////////////////// Horizontal Street ////////////////////////////////
void Map::xEqualsZero(Car* obj, int velo, bool dir) {
    for(int i = 0; i < 5; i++) {
        if(dir == 1)   obj->indexY += velo;
        else          obj->indexY -= velo;
        obj->indexX = obj->indexY * 0 + 0;
        cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
    }
}
void Map::xEqualsFive(Car* obj, int velo, bool dir) {
    for(int i = 0; i < 5; i++) {
        if(dir == 1)   obj->indexY += velo;
        else          obj->indexY -= velo;
        obj->indexX = obj->indexY * 0 + 5;
        cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
    }
}
void Map::xEqualsTen(Car* obj, int velo, bool dir) {
    for(int i = 0; i < 5; i++) {
        if(dir == 1)   obj->indexY += velo;
        else          obj->indexY -= velo;
        obj->indexX = obj->indexY * 0 + 10;
        cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
    }
}