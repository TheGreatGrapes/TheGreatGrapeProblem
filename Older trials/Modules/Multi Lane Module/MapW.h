#ifndef MAPW_H
#define MAPW_H

class MapW
{
public:
    MapW();
    ~MapW();
    void Path1(CarC obj1, CarC obj2, float v1, float v2);
    void Path(std::vector<CarC*> c);
    int time;
    //float Pos[2];
    friend class CarC;

};

#endif // MAPW_H
