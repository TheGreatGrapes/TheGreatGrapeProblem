/*
 * ///////////////// Multi-Agent Traffic simulation ////////////////
 * 
 * Version 1.0
 * 
 * Agent number:
 * Single agent
 * 
 * Functionalities: 
 * Report position / Move at constant velocity / Make decision at crossroad
 * 
 * Explanation:
 *      An agent (Car) is initialized at (0,0) in the beginning. 
 *      It can choose from different path (equations) to go, if (0,0), then up or right,
 *      Our map provides at least two options , at most four options at the crossroad.
 *      The car is allowed to turn back, it moves and stops at every node, and decides randomly 
 *      to connet to different pathes. 
 *      Simulation time is set, yet according to the postion of object, it might jump to the next 
 *      if-statement, which would not counted by the counter.
 * 
 * This is how the map looks like (but no 2D array needed) :
 * 
 *                         (5,10)
 *        (0,10) *  *  *  *  *  *  *  *  * (10,10)
 *               *           *           *
 *               *           *           *
 *               *           *           *
 *               *           * (5,5)     *
 *         (0,5) *  *  *  *  *  *  *  *  * (10,5)
 *               *           *           *
 *               *           *           *
 *               *           *           *
 *               *           *           *
 *         (0,0) *  *  *  *  *  *  *  *  * (10,0)
 *                         (5,0)          
 * 
 *      
 *  There're two classes: Car & Map
 *  Car class 
 *      1. can report position (or directly access since the variable is public)
 *      2. is used as an argument a function in Map class
 *      3. has indexX & indexY as the coordinates of Car object (x,y)
 *      4. has function called check() to check current position of object 
 *      5. 's object is initilized at (0,0)
 * 
 *  Map class
 *      1. has 6 functions, each of them represents one street. 
 *      2. is actually an update center, updating the position of the imported object.
 *      3. E.g. 
 * 
 *         yEqualsZero(Car* obj, int velo, bool dir)
 *          ＾               ＾       ＾          ＾
 *     Name of street     Object   Velocity   Forward/Backward
 *      
 *      for(int i = 0; i < 5; i++) {                 // Go along the street, 5 is the distance between nodes, say, (0,0) - (5,0)
            if(dir == 1)  obj->indexX += velo;       // If dir is 1, go forward / upward
            else          obj->indexX -= velo;       //           0,    backward/ downward
        
            obj->indexY = obj->indexX * 0 + 0;       // Update coordinate Y according to X.
    
            cout << "(" << obj->getIndexX() << ", " << obj->getIndexY() << ")" << endl;
        }
 *      
 *  Possible tasks to further work on:
 *      1. Initialize a random position for object, not only on crossroads.
 *      2. Pack the if-statement and switches into individual functions, make the main() cleaner.
 *      3. How to add another object to simulation? Array?
 *      4. Collision avoidance / Car follow
 *      5. Better way of implementing map?
 * 
 *   Last modified 06.05.2017 01:42 TIMPERATOR
*/
#include <iostream>
#include <time.h>
#include "Map.h"

using namespace std;

static int counter = 0;       

const int simulationTime = 50;  

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
            case 0: {m->yEqualsZero(a_ptr, 1, 1);break;}
            case 1: {m->xEqualsZero(a_ptr, 1, 1);break;}
            default: { cout << "Something is wrong with 0,0!" << endl; }
            }
        }
        if(a.check(5, 0)) {
            switch(chooseThreePath) {
            case 0: {m->xEqualsFive(a_ptr, 1, 1);break;}
            case 1: {m->yEqualsZero(a_ptr, 1, 1);break;}
            case 2: {m->yEqualsZero(a_ptr, 1, 0);break;}
            default: { cout << "Something is wrong with 5,0!" << endl; }
            }
        }
        if(a.check(10, 0)){
            switch(chooseTwoPath){
            case 0: {m->yEqualsZero(a_ptr, 1, 0);break;}
            case 1: {m->xEqualsTen(a_ptr, 1, 1);break;}
            default: { cout << "Something is wrong with 10,0!" << endl; }
            }
        }
        if(a.check(0, 5)){
            switch(chooseThreePath){
            case 0: {m->xEqualsZero(a_ptr, 1, 1);break;}
            case 1: {m->xEqualsZero(a_ptr, 1, 0);break;}
            case 2: {m->yEqualsFive(a_ptr, 1, 1);break;}
            default: { cout << "Something is wrong with 0,5!" << endl; }
            }            
        }
        if(a.check(5,5)){
            switch(chooseFourPath){
            case 0: {m->xEqualsFive(a_ptr, 1, 1);break;}
            case 1: {m->xEqualsFive(a_ptr, 1, 0);break;}
            case 2: {m->yEqualsFive(a_ptr, 1, 1);break;}
            case 3: {m->yEqualsFive(a_ptr, 1, 0);break;}
            default: { cout << "Something is wrong with 5,5!" << endl; }
            }
        }
        if(a.check(10,5)){
            switch(chooseThreePath){
            case 0: {m->xEqualsTen(a_ptr, 1, 1);break;}
            case 1: {m->xEqualsTen(a_ptr, 1, 0);break;}
            case 2: {m->yEqualsFive(a_ptr, 1, 0);break;}
            default: { cout << "Something is wrong with 10,5!" << endl; }
            }
        }
        if(a.check(0,10)){
            switch(chooseTwoPath){
            case 0: {m->yEqualsTen(a_ptr, 1, 1);break;}
            case 1: {m->xEqualsZero(a_ptr, 1, 0);break;}
            default: { cout << "Something is wrong with 0,10!" << endl; }
            }
        }
        if(a.check(5,10)){
            switch(chooseThreePath){
            case 0: {m->xEqualsFive(a_ptr, 1, 0);break;}
            case 1: {m->yEqualsTen(a_ptr, 1, 1);break;}
            case 2: {m->yEqualsTen(a_ptr, 1, 0);break;}
            default: { cout << "Something is wrong with 5,10!" << endl; }
            }            
        }
        if(a.check(10,10)){
            switch(chooseTwoPath){
            case 0: {m->xEqualsTen(a_ptr, 1, 0);break;}
            case 1: {m->yEqualsTen(a_ptr, 1, 0);break;}
            default: { cout << "Something is wrong with 10,10!" << endl; }
            }            
        }
        else {}
        
    } while(counter < simulationTime);

    //////////////////////////////////////////////////////////////////////

    ////////////////////////// Simulation Ends////////////////////////////

    return 0;
}