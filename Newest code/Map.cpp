#include "Map.h"
#include <math.h>
#include <iostream>

using namespace std;
Map::Map() {
}

Map::~Map() {
}

///////////////////////// Streets / Equations //////////////////////////////
/////////////////////////// Vertical Street ////////////////////////////////

void Map::yEquals_0(Car* obj, bool dir) {
    double velo = 0.0;
    double tempX = obj->indexX;     // Remember initial position
        
    do{                             // Accelerating
        velo += obj->Acc;
        checkDirX(obj, velo, dir);  
        obj->indexY = obj->indexX * 0 + 0; 
        printPos(obj, velo);
    }while(fabs(obj->indexX - tempX) < dist/3);
        
    do{                             // Cruising
        checkDirX(obj, velo, dir);
        obj->indexY = obj->indexX * 0 + 0;
        printPos(obj, velo);
    }while(fabs(obj->indexX - tempX) <= dist*2/3);
        
    do{                             // Breaking
        velo -= obj->Acc;
        checkDirX(obj, velo, dir);
        obj->indexY = obj->indexX * 0 + 0; 
        printPos(obj, velo);
    }while( dist - fabs(obj->indexX - tempX) > 1);
    
    if (dir == 1) obj->indexX = tempX + dist;             // Hit the break before junction.
    else          obj->indexX = tempX - dist;             // Hit the break before junction.
    velo = 0;
    printPos(obj, velo);
}
void Map::yEquals_120(Car* obj,  bool dir) {
    double velo = 0.0;
    double tempX = obj->indexX;     // Remember initial position
        
    do{                             // Accelerating
        velo += obj->Acc;
        checkDirX(obj, velo, dir);  
        obj->indexY = obj->indexX * 0 + 120; 
        printPos(obj, velo);
    }while(fabs(obj->indexX - tempX) < dist/3);
        
    do{                             // Cruising
        checkDirX(obj, velo, dir);
        obj->indexY = obj->indexX * 0 + 120;
        printPos(obj, velo);
    }while(fabs(obj->indexX - tempX) <= dist*2/3);
        
    do{                             // Breaking
        velo -= obj->Acc;
        checkDirX(obj, velo, dir);
        obj->indexY = obj->indexX * 0 + 120; 
        printPos(obj, velo);
    }while( dist - fabs(obj->indexX - tempX)  > 1);

    if (dir == 1) obj->indexX = tempX + dist;             // Hit the break before junction.
    else          obj->indexX = tempX - dist;             // Hit the break before junction.
    velo = 0;
    printPos(obj, velo);
}
void Map::yEquals_240(Car* obj,  bool dir) {
    double velo = 0.0;
    double tempX = obj->indexX;     // Remember initial position
        
    do{                             // Accelerating
        velo += obj->Acc;
        checkDirX(obj, velo, dir);  
        obj->indexY = obj->indexX * 0 + 240; 
        printPos(obj, velo);
    }while(fabs(obj->indexX - tempX) < dist/3);
        
    do{                             // Cruising
        checkDirX(obj, velo, dir);
        obj->indexY = obj->indexX * 0 + 240;
        printPos(obj, velo);
    }while(fabs(obj->indexX - tempX) <= dist*2/3);
        
    do{                             // Breaking
        velo -= obj->Acc;
        checkDirX(obj, velo, dir);
        obj->indexY = obj->indexX * 0 + 240; 
        printPos(obj, velo);
    }while( dist - fabs(obj->indexX - tempX) > 1);
    
    if (dir == 1) obj->indexX = tempX + dist;             // Hit the break before junction.
    else          obj->indexX = tempX - dist;             // Hit the break before junction.
    velo = 0;
    printPos(obj, velo);
}

///////////////////////////// Horizontal Street ////////////////////////////////
void Map::xEquals_0(Car* obj, bool dir) {
    double velo = 0.0;
    double tempY = obj->indexY;     // Remember initial position
        
    do{                             // Accelerating
        velo += obj->Acc;
        checkDirY(obj, velo, dir);  
        obj->indexX = obj->indexY * 0 + 0; 
        printPos(obj, velo);
    }while(fabs(obj->indexY - tempY) < dist/3);
        
    do{                             // Cruising
        checkDirY(obj, velo, dir);
        obj->indexX = obj->indexY * 0 + 0;
        printPos(obj, velo);
    }while(fabs(obj->indexY - tempY) <= dist*2/3);
        
    do{                             // Breaking
        velo -= obj->Acc;
        checkDirY(obj, velo, dir);
        obj->indexX = obj->indexY * 0 + 0; 
        printPos(obj, velo);
    }while( dist - fabs(obj->indexY - tempY) > 1);
    
    if (dir == 1) obj->indexY = tempY + dist;             // Hit the break before junction.
    else          obj->indexY = tempY - dist;             // Hit the break before junction.
    velo = 0;
    printPos(obj, velo);
}
void Map::xEquals_120(Car* obj, bool dir) {
    double velo = 0.0;
    double tempY = obj->indexY;     // Remember initial position
        
    do{                             // Accelerating
        velo += obj->Acc;
        checkDirY(obj, velo, dir);  
        obj->indexX = obj->indexY * 0 + 120; 
        printPos(obj, velo);
    }while(fabs(obj->indexY - tempY) < dist/3);
        
    do{                             // Cruising
        checkDirY(obj, velo, dir);
        obj->indexX = obj->indexY * 0 + 120;
        printPos(obj, velo);
    }while(fabs(obj->indexY - tempY) <= dist*2/3);
        
    do{                             // Breaking
        velo -= obj->Acc;
        checkDirY(obj, velo, dir);
        obj->indexX = obj->indexY * 0 + 120; 
        printPos(obj, velo);
    }while( dist - fabs(obj->indexY - tempY) > 1);
    
    if (dir == 1) obj->indexY = tempY + dist;             // Hit the break before junction.
    else          obj->indexY = tempY - dist;             // Hit the break before junction.
    velo = 0;
    printPos(obj, velo);
}
void Map::xEquals_240(Car* obj, bool dir) {
    double velo = 0.0;
    double tempY = obj->indexY;     // Remember initial position
        
    do{                             // Accelerating
        velo += obj->Acc;
        checkDirY(obj, velo, dir);  
        obj->indexX = obj->indexY * 0 + 240; 
        printPos(obj, velo);
    }while(fabs(obj->indexY - tempY) < dist/3);
        
    do{                             // Cruising
        checkDirY(obj, velo, dir);
        obj->indexX = obj->indexY * 0 + 240;
        printPos(obj, velo);
    }while(fabs(obj->indexY - tempY) <= dist*2/3);
        
    do{                             // Breaking
        velo -= obj->Acc;
        checkDirY(obj, velo, dir);
        obj->indexX = obj->indexY * 0 + 240; 
        printPos(obj, velo);
    }while( dist - fabs(obj->indexY - tempY) > 1);
    
    if (dir == 1) obj->indexY = tempY + dist;             // Hit the break before junction.
    else          obj->indexY = tempY - dist;             // Hit the break before junction.
    velo = 0;
    printPos(obj, velo);
}


void Map::checkDirX(Car* obj, double velocity, bool direction){
        if(direction == 1)   obj->indexX += velocity;
        else                 obj->indexX -= velocity;
}

void Map::checkDirY(Car * obj, double velocity, bool direction){
        if(direction == 1)   obj->indexY += velocity;
        else                 obj->indexY -= velocity;    
}

void Map::printPos(Car * obj, double velo){
    cout << "(" << obj->indexX << ", " << obj->indexY << ") v= " << velo << endl;
}
