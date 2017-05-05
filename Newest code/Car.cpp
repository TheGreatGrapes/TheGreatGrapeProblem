#include "Car.h"
#include <iostream>

using namespace std;

Car::Car() // Instantiate initial position (x,y) = (0,0)
{
    indexX = 0;
    indexY = 0;
}

Car::Car(int x, int y) // Instantiate initial position (x,y)
{
    indexX = x;
    indexY = y;
}

Car::~Car() {
}

///////////// Position Info //////////////
int Car::getIndexX() { // Report index X in the array
    return indexX;
}

int Car::getIndexY() { // Report index Y in the array
    return indexY;
}

int Car::check(int x, int y) {
    if(this->indexX == x && this->indexY == y){
        return 1;
    }else 
        return 0;
}
////////////////////////////////////////////


///////// Please Ignore ///////////
/*
void Car::forwardSpeed(int veloX = 0, int veloY = 0) { // Size of the step is represent velocity
    indexX += veloX;
    indexY += veloY;
}

void Car::backwardSpeed(int veloX = 0, int veloY = 0) {
    indexX -= veloX;
    indexX -= veloY;
}
*/

/*
int Car::printPosX(int mapX[]) { // Report value X at index X in the array
    return mapX[indexX];
}
int Car::printPosY(int mapY[]) { // Report value Y at index Y  in the array
    return mapY[indexY];
}
*/
/////////////////////////////////////



