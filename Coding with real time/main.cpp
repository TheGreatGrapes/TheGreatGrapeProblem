#include <iostream>
#include <ctime>
#include "Timer.h"
#include "Car.h"

using namespace std;

int main() {

    const int STREETLENGTH = 1000;
    const int VELOCITY = 10;
    
    int mapX[STREETLENGTH];
    bool running = true;
    int counter = 0;
    
    // Initiate one timer.
    // Timer zeit;
    // Create an object
    Car a(0);
    Timer zeit;
    

    
    // Fill up the map with coordinates from 0 - 99
    for(int i = 0; i < STREETLENGTH; i++) {
        mapX[i] = i;
    }

    while(running) {
        // Initiate another timer.
        zeit.timeInit();

        if(zeit.measureTime() == 1) {
            // Move forward
            a.moveForward(VELOCITY);
            a.printPos(mapX);
            // Reset the timer
            zeit.resetTimer();
            // To avoid the problem when sec goes from 59 to 00
            zeit.check();
            
        }
        counter++;
    }

    return 0;
}
