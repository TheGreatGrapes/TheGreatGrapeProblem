#include <stdio.h>
#include <iostream>
#include <math.h>  
#include "CarC.h"



using namespace std;


/*CarC::CarC(float loc[2])
    {
    xPos=loc[0];
    yPos=loc[1];
    Vmax=4.0;
    Acc=(Vmax*Vmax)/(2.0*(50.0/3.0));
    Loc[0]=xPos;
    Loc[1]=yPos;
    
    }*/
    
CarC::CarC(){
    
    xPos=0;
    yPos=0;
    Vmax=4.0;
    Acc=(Vmax*Vmax)/(2.0*(50.0/3.0));
    Loc[0]=xPos;
    Loc[1]=yPos;
}

CarC::~CarC()
{
}

//void CarC::moveCar(MapW ob, float v){
    //ob.Path1(this , v);
//}
