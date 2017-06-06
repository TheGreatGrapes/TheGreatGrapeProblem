#include "vehicle.h"
extern int windowSize;

Vehicle::Vehicle()
{
    location = new Pvector(0,0);
    velocity = new Pvector(0,0);
    acceleration = new Pvector(0,0);
}



Vehicle::Vehicle(float l, float v, int _id, float maxS)
{
    location = new Pvector(l,v);
    velocity = new Pvector(0,0);
    acceleration= new Pvector(0,0);
    lifespan = 250;
    mass = 1;
    id= _id;
    maxforce= .01;
    maxspeed= maxS;
}



void Vehicle::update()
{
    velocity->add(acceleration);
    limit(velocity,maxspeed);
    location->add(velocity);
    acceleration->mult(0);
    //checkEdge();
}


void Vehicle::checkEdge(){
    if(location->x < -windowSize){
        location->x = -windowSize;
        velocity->x *= -1;
    }else if (location->x > windowSize){
        velocity->x *= -1;
        location->x = windowSize;
    }

    if(location->y < -windowSize){
        location->y = -windowSize;
        velocity->y *= -1;
    }else if (location->y > windowSize){
        velocity->y *= -1;
        location->y = windowSize;
    }
}


void Vehicle::applyForce(Pvector* force)
{
    Pvector *f= Pvector::div(force,this->mass);
    acceleration->add(f);
}



void Vehicle::limit(Pvector* vec,float max){
    if (vec->mag()>max)
    {
        vec->normalize();
        vec->mult(max);
    }
}



void Vehicle::seek(Pvector *target)
{
    Pvector *desired = Pvector::sub(target, location);
    desired->normalize();
    desired->mult(.4);

    Pvector *steer = Pvector::sub(desired, velocity);
    limit(steer,maxforce);
    applyForce(steer);
}



float Vehicle::map(float d, float ilb, float iub, float olb, float oub)
{
    return (((oub-olb)*d)/(iub-ilb));
}



void Vehicle::arrive(Pvector* target)
{
    Pvector *desired= Pvector::sub(target,this->location);

    float d= desired->mag();
    desired->normalize();

    if(d < 100)
    {
        float m= map(d,0,100,0,maxspeed);
        desired->mult(m);

    }
    else {
        desired->mult(maxspeed);
    }
    Pvector *steer = Pvector::sub(desired, this->velocity);
    limit(steer, maxforce);
    applyForce(steer);
}


void Vehicle::follow(Path* p, int d)
{
    Pvector target(0,0);
    float worldRecord = 1000000;

    Pvector predict = velocity->get();
    predict.normalize();
    predict.mult(25);
    Pvector *predictLoc = Pvector::add(location, &predict );

    //Multiple points
    for (int i = 0; i < int(p->points.size())-1; i++ )
    {
        Pvector *a = p->points[i];
        Pvector *b =  p->points[i+1];
        Pvector *normalPoint = Pvector::getNormalPoint(predictLoc, a, b);

        if(normalPoint->x < fmin(a->x,b->x) || normalPoint->x > fmax(a->x,b->x))
        {
            *normalPoint = b->get();
        }
        else if(normalPoint->y < fmin(a->y,b->y) || normalPoint->y > fmax(a->y,b->y))
        {
            *normalPoint = b->get();
        }



        float distance = Pvector::dist(predictLoc, normalPoint);

        if (distance < worldRecord)
        {
            worldRecord = distance;
            target = normalPoint->get();   //check if using a pointer works here
            Pvector *dir = Pvector::sub(b, a);
            dir->normalize();
            if(d == 1)
            {
                dir->mult(10);
            }
            else
            {
                dir->mult(-10);
            }
            target.add(dir);
        }
    }

    if (worldRecord > p->radius)
    {
        seek(&target);
    }



    //Single path
    /*
    Pvector *a = p->start;
    Pvector *b = p->end;
    Pvector *normalPoint = Pvector::getNormalPoint(predictLoc, a, b);

    Pvector *dir =Pvector::sub(b, a);
    dir->normalize();
    dir->mult(10);
    Pvector *target = Pvector::add(normalPoint, dir);

    float distance = Pvector::dist(normalPoint, predictLoc);
    if(distance >p->radius)
    {
        seek(target);
    }
*/

}

void Vehicle::borders(Path *p)
{
    if (location->x > p->getEnd()->x + 5)
    {
        location->x = p->getStart()->x -5;
        location->y = p->getStart()->y+ (location->y - p->getEnd()->y);
    }
}


void Vehicle::separate(std::vector<Vehicle*> vehicles)
{
    float desiredSeperation = 10 * 2; //5= radius of car object
    int tooClosecount =0;
    int radius = 50;
    Pvector *sum = new Pvector(0,0);

    for (std::vector<Vehicle*>::iterator it = vehicles.begin() ; it != vehicles.end(); ++it )
    {
        float d = Pvector::dist(location, (*it)->location);

        if (d < radius)
        {
            if ((d > 0) && (d < desiredSeperation))
            {
                Pvector *diff = Pvector::sub(location, (*it)->location);  //Calculate vector pointing away from neighbor
                diff->normalize();
                diff->div(d);

                //diff->mult(0);
                //weight by distance
                sum->add(diff);
                tooClosecount ++;       // keeping track
            }
        }

    }

    // Average //

    if(tooClosecount > 0)
    {
        if(tooClosecount > 3 && tooClosecount < 7)     //  simulating a traffic jam
        {
            sum->div(tooClosecount);
            sum->setMag(0);
        }
        else {
            sum->div(tooClosecount);
            sum->setMag(maxspeed);
        }

        Pvector *steer = Pvector::sub(sum, velocity);
        steer->limit(maxforce);
        applyForce(steer);
    }

}

