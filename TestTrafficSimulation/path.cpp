#include "path.h"

Path::Path(){

    addPoints(-200, 200);
    addPoints(   0, 200);
    addPoints( 200, 200);
    addPoints( 200,   0);
    addPoints( 200,-200);
    addPoints(   0,-200);
    addPoints(-200,-200);
    addPoints(-200,   0);
    addPoints(   0,   0);
}

Path::Path(float start_x, float start_y, float end_x,float end_y)
{
    radius = 10;
    start = new Pvector(start_x,start_y);
    end = new Pvector(end_x,end_y);
}


void Path::addPoints(float x, float y){
    Pvector *point = new Pvector(x, y);
    points.push_back(point);
}
