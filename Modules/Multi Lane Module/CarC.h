#ifndef CARC_H
#define CARC_H



class CarC
{
public:
    CarC(float v);
    ~CarC();

    float xPos;
    float yPos;
    float Vmax;
    float Acc;
    float Vin;
    int time;
    
    friend class MapW;

    
    float Loc[2];
    
    
};

#endif // CARC_H
