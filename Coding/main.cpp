#include <iostream>
#include "Timer.h"
#include "Car.h"
#include <ctime>

using namespace std;

int main() {

    const int streetLength = 100;
    int velocity = 10;
    int mapX[streetLength];
    bool running = true;

    // Initiate one timer.
    Timer zeit;
    // Create an object
    Car a(0);
    
    // Fill up the map with coordinates from 0 - 99
    for(int i = 0; i < streetLength; i++) {
        mapX[i] = i;
    }

    while(running) {
        // Initiate another timer.
        zeit.timeInit();

        if(zeit.measureTime() == 1) {
            // Move forward
            a.moveForward(velocity);
            a.printPos(mapX);
            // Reset the timer
            zeit.resetTimer();
            // To avoid the problem when sec goes from 59 to 00
            zeit.check();
        }
    }

    return 0;
}
