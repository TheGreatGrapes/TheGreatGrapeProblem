#ifndef PVECTOR_H
#define PVECTOR_H
#include "math.h"



class Pvector
{
public:
    Pvector(float, float);

//////// Position //////////
    float x;
    float y;
    Pvector ap(float, float);
    Pvector ab(float, float);

//////// Functions //////////
    void add(Pvector*);
    void sub(Pvector*);
    void mult(float);
    void div(float);
    float mag();
    void normalize();
    Pvector get();
    void setMag(float);
    void limit(float max);

//////// Static Functions //////////
    Pvector* Add(Pvector,Pvector);
    //static Pvector* Sub(Pvector, Pvector);
    Pvector* Mult(Pvector,float);
    Pvector* Div(Pvector,float);
    Pvector Subt(Pvector, Pvector);


    static Pvector* add(Pvector*,Pvector*);
    static Pvector* sub(Pvector*,Pvector*);
    static Pvector* mult(Pvector*,float);
    static Pvector* div(Pvector*,float);
    static float dot(Pvector*, Pvector*);
    static float angleBetween(Pvector*, Pvector*);
    static Pvector* getNormalPoint(Pvector*, Pvector*, Pvector*);
    static float dist(Pvector*, Pvector*);
};

#endif // PVECTOR_H
