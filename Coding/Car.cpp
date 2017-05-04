#include <iostream>
#include "Car.h"

using namespace std;

Car::Car() // Instantiate initial position (x,y) = (0,0)
{
    indexX = 0;
    indexY = 0;
}

Car::~Car() {
}

/*
///////// Motion ///////////
void Car::forwardSpeed(int velo = 0) { // Size of the step is represent velocity
    indexX += velo;
    indexY += velo;
}

void Car::backwardSpeed(int veloX = 0, int veloY = 0) {
    indexX -= veloX;
    indexX -= veloY;
}
////////////////////////////
*/



///////// Position Info ///////////
int Car::getIndexX() {              // Report index X in the array
    return indexX;
}

int Car::getIndexY() {              // Report index Y in the array
    return indexY;
}

int Car::printPosX(int mapX[]) { // Report value X at index X in the array
    return mapX[indexX];
}
int Car::printPosY(int mapY[]) { // Report value Y at index Y  in the array
    return mapY[indexY];
}
////////////////////////////