#ifndef CARC_H
#define CARC_H
//#include "CarC.h"
//#include "MapW.h"


class CarC
{
public:
    CarC();
    ~CarC();
    //CarC(float loc[2]);
    float xPos;
    float yPos;
    float Vmax;
    float Acc;
    
    friend class MapW;
    //void moveCar(MapW obj, float v);
    void moveCar(MapW ob, float v);
    
    float Loc[2];
    
    
};

#endif // CARC_H
