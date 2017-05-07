#ifndef CARC_H
#define CARC_H



class CarC
{
public:
    CarC();
    ~CarC();

    float xPos;
    float yPos;
    float Vmax;
    float Acc;
    
    friend class MapW;

    
    float Loc[2];
    
    
};

#endif // CARC_H
