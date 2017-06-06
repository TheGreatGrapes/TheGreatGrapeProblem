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

//////// Functions //////////
    void add(Pvector*);
    void sub(Pvector*);
    void mult(float);
    void div(float);
    void normalize();
    void setMag(float);
    void limit(float max);

    float mag();

    Pvector get();

//////// Static Functions //////////
    static Pvector* add(Pvector*,Pvector*);
    static Pvector* sub(Pvector*,Pvector*);
    static Pvector* mult(Pvector*,float);
    static Pvector* div(Pvector*,float);
    static Pvector* getNormalPoint(Pvector*, Pvector*, Pvector*);

    static float dot(Pvector*, Pvector*);
    static float angleBetween(Pvector*, Pvector*);
    static float dist(Pvector*, Pvector*);
};

#endif // PVECTOR_H
