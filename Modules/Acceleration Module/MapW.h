#ifndef MAPW_H
#define MAPW_H

class MapW
{
public:
    MapW();
    ~MapW();
    
    void Path1(CarC obj, float v);
    float Pos[2];
    friend class CarC;

};

#endif // MAPW_H
