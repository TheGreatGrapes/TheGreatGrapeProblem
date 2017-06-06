#include <stdio.h>
#include <iostream>
#include <math.h>  
#include "CarC.h"
#include "MapW.h"
#include <vector>

using namespace std;


int main(int argc, char **argv)

{
    
    vector<CarC*> car(2);    //car vector
    car[0] = new CarC(4.0);
    car[1] = new CarC(3.0);
    //car[2] = new CarC(2.0);
    
    MapW *m = new MapW;  //Map object
    
    m->Path(car);  //
    
}

