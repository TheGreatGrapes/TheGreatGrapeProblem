#ifndef PATH_H
#define PATH_H
#include "pvector.h"
#include <vector>

class Path
{
public:
    Path();
    Path(float,float,float,float);

    Pvector *start;
    Pvector *end;

    std::vector<Pvector*> points;

    float radius;

    void addPoints(float, float);
};

#endif // PATH_H
