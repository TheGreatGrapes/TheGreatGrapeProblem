#include <iostream>
#include "Car.h"
#include "Map.h"

using namespace std;

static int counter = 0;

const int simulationTime = 50;

int main() {

    //// Parameter Setup ////
    const int STREETLENGTH = 100; // length 1000cm
    int mapX[STREETLENGTH];
    int mapY[STREETLENGTH];
    int j = 0.0;
    ////////////////////////////

    //// Instantiate Object ////
    Car a;
    Car* a_ptr = &a;

    Map map;
    Map* m = &map;

    ////////////////////////////

    //////// Create a map ////////
    // Fill up the map with coordinates from 00 - 999
    for(int i = 0; i < STREETLENGTH; i++) {
        mapX[i] = j;
        mapY[i] = j;
        j += 1;
    }
    ///////////////////////////////

    /////////// Simulation ///////////

    do {
        counter += 1;

        cout << endl;

        if(a_ptr->getIndexY() == 0)
        m->yEqualsZero(&a, 1);        
        
        //if(a_ptr->getIndexX() == 4)
        //m->xEqualsTwenty(a,1);
        
        cout << "(" << a_ptr->getIndexX() << ", " << a_ptr->getIndexY() << ")" << endl;
 
    } while(counter < simulationTime);

    ///////////////////////////////////


    return 0;
}
