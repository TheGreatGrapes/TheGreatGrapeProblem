#include "Car.h"
#include <iostream>

using namespace std;

Car::Car(int x) {
    positionX = x;
}

Car::~Car() {
}

void Car::moveForward(int step) {
    positionX += step;
}
void Car::moveBackward(int step) {
    positionX -= step;
}
void Car::printPos(int map[]) { //
    cout << map[positionX] << endl;
}
int Car::returnPos() {
    return positionX;
}