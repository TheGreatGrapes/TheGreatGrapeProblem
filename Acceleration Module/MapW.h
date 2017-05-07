#ifndef MAPW_H
#define MAPW_H

class MapW
{
public:
    MapW();
    ~MapW();
    //int *Path1(CarC obj, int v, int acc);
    void Path1(CarC obj, float v);
    float Pos[2];
    //int count=0;
    
    //static int v=0;
    friend class CarC;

};

#endif // MAPW_H
