
#include <iostream>
#include <time.h>
#include "Map.h"

using namespace std;

static int counter = 0;       

const int simulationTime = 10;  

int dist = 120; //Dist between streets

int main() {
    ////////////////////Ignore below commented code ////////////////////
    /*
    //// Parameter Setup ////
    const int STREETLENGTH = 100; // length 100cm
    int mapX[STREETLENGTH];
    int mapY[STREETLENGTH];
    int j = 0.0;
    ////////////////////////////////////////////////////////////////////

    ////////////////////////// Create a map //////////////////////////
    // Fill up the map with coordinates from 00 - 999
    for(int i = 0; i < STREETLENGTH; i++) {
        mapX[i] = j;
        mapY[i] = j;
        j += 1;
    }
    ///////////////////////////////////////////////////////////////////
    */

    ////////////////////////// Random Generator /////////////////////////
    srand(time(NULL));

    int chooseThreePath = 0, chooseTwoPath = 0, chooseFourPath = 0;

    //////////////////////////////////////////////////////////////////////

    ///////////////////////// Instantiate Object /////////////////////////
    Car a;
    Car* a_ptr = &a;

    Map map;
    Map* m = &map;

    /////////////////////////////////////////////////////////////////////

    ////////////////////////// Simulation Starts///////////////////////////
    
    do {
        counter += 1;
        chooseFourPath = rand() % 4;  // Generate number from 0,1,2,3
        chooseThreePath = rand() % 3; // Generate number from 0,1,2
        chooseTwoPath = rand() % 2;   // Generate number from 0,1
        
    ////////////////////// set up checking points ////////////////////////
        
        if(a.check(0, 0)) {
            switch(chooseTwoPath) {
            case 0: {m->yEquals_0(a_ptr, 1);break;}
            case 1: {m->xEquals_0(a_ptr, 1);break;}
            default: { cout << "Something is wrong with 0,0!" << endl; }
            }
        }
        
        if(a.check(120, 0)) {
            switch(chooseThreePath) {
            case 0: {m->xEquals_120(a_ptr, 1);break;}
            case 1: {m->yEquals_0(a_ptr, 1);break;}
            case 2: {m->yEquals_0(a_ptr, 0);break;}
            default: { cout << "Something is wrong with 5,0!" << endl; }
            }
        }
        if(a.check(240, 0)){
            switch(chooseTwoPath){
            case 0: {m->yEquals_0(a_ptr, 0);break;}
            case 1: {m->xEquals_240(a_ptr, 1);break;}
            default: { cout << "Something is wrong with 10,0!" << endl; }
            }
        }
        if(a.check(0, 120)){
            switch(chooseThreePath){
            case 0: {m->xEquals_0(a_ptr, 1);break;}
            case 1: {m->xEquals_0(a_ptr, 0);break;}
            case 2: {m->yEquals_120(a_ptr, 1);break;}
            default: { cout << "Something is wrong with 0,5!" << endl; }
            }            
        }
        if(a.check(120 ,120)){
            switch(chooseFourPath){
            case 0: {m->xEquals_120(a_ptr, 1);break;}
            case 1: {m->xEquals_120(a_ptr, 0);break;}
            case 2: {m->yEquals_120(a_ptr, 1);break;}
            case 3: {m->yEquals_120(a_ptr, 0);break;}
            default: { cout << "Something is wrong with 5,5!" << endl; }
            }
        }
        if(a.check(240,120)){
            switch(chooseThreePath){
            case 0: {m->xEquals_240(a_ptr, 1);break;}
            case 1: {m->xEquals_240(a_ptr, 0);break;}
            case 2: {m->yEquals_120(a_ptr, 0);break;}
            default: { cout << "Something is wrong with 10,5!" << endl; }
            }
        }
        if(a.check(0,240)){
            switch(chooseTwoPath){
            case 0: {m->yEquals_240(a_ptr, 1);break;}
            case 1: {m->xEquals_0(a_ptr, 0);break;}
            default: { cout << "Something is wrong with 0,10!" << endl; }
            }
        }
        if(a.check(120,240)){
            switch(chooseThreePath){
            case 0: {m->xEquals_120(a_ptr, 0);break;}
            case 1: {m->yEquals_240(a_ptr, 1);break;}
            case 2: {m->yEquals_240(a_ptr, 0);break;}
            default: { cout << "Something is wrong with 5,10!" << endl; }
            }            
        }
        if(a.check(240,240)){
            switch(chooseTwoPath){
            case 0: {m->xEquals_240(a_ptr, 0);break;}
            case 1: {m->yEquals_240(a_ptr, 0);break;}
            default: { cout << "Something is wrong with 10,10!" << endl; }
            }            
        }
        else {}
        
    } while(counter < simulationTime);
    
    //////////////////////////////////////////////////////////////////////

    ////////////////////////// Simulation Ends////////////////////////////

    return 0;
}