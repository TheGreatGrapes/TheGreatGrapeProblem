#include "vehicle.h"


///////////////// Constructor ///////////////

Vehicle::Vehicle()
{
    location = new Pvector(0,0);
    velocity = new Pvector(0,0);
    acceleration = new Pvector(0,0);

    addCars(-200,200,4,2.5);
    addCars(-200,200,1,3);
    addCars(-200,200,5,2);
    addCars(-200,200,1,4);
    addCars(-200,200,10,1.5);

}

Vehicle::Vehicle(float x, float y, int _id, float v)
{
    location = new Pvector(x,y);
    velocity = new Pvector(0,0);
    acceleration= new Pvector(0,0);
    goal = new Pvector(0,0);
    maxforce=1;
    maxspeed=v;

    lifespan =250;                  //// No use
    mass =1;                        //// No use
    id= _id;                        //// No use
}

///////////////// Main Functions ///////////////

void Vehicle::arrive()
{
    Pvector *desired = Pvector::sub(this->goal, this->location);

    float d = desired->mag();
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

void Vehicle::applyForce(Pvector* force)
{
    Pvector *f= Pvector::div(force,this->mass);
    acceleration->add(f);
}

void Vehicle::seek(Pvector *target)
{
    Pvector *desired = Pvector::sub(target, this->location);
    desired->normalize();
    desired->mult(.9);

    Pvector *steer= Pvector::sub(desired, this->velocity);
    limit(steer,maxforce);
    applyForce(steer);
}

///////////////// Sub Functions ///////////////

void Vehicle::addCars(float x, float y, int _id, float speed){
    Vehicle *car = new Vehicle(x, y, _id, speed);
    cars.push_back(car);
}

void Vehicle::update()
{
    velocity->add(acceleration);
    limit(velocity,maxspeed);
    location->add(velocity);
    acceleration->mult(0);
}

void Vehicle::limit(Pvector* vec,float max){
    if (vec->mag()>max)
    {
        vec->normalize();
        vec->mult(max);
    }
}

float Vehicle::map(float d, float ilb, float iub, float olb, float oub)
{
    return (((oub-olb)*d)/(iub-ilb));
}

void Vehicle::stopAtJunction(){

    float approach = Pvector::dist(this->goal, this->location);

    if(approach < 1){
        *(this->location) = *(this->goal);
    }
}

void Vehicle::chooseJunction(Path* p){

    if( this->ifAtJunction(p) ){
        float distance = 0;

        for(unsigned long i = 0; i < p->points.size(); i++){
            distance = Pvector::dist(p->points[i],this->location);

            if(distance == 200){
                this->possibleDest.push_back(*(p->points[i]));
            }
        }
        int options = possibleDest.size();
        int decision = rand() % options;

        *(this->goal) = this->possibleDest[decision];
        this->possibleDest.clear();
    }
}

bool Vehicle::ifAtJunction(Path* p){
    bool yesOrNo = false;
    for(unsigned long i = 0; i < p->points.size(); i++){
        if(this->location->x == p->points[i]->x && this->location->y == p->points[i]->y){
            yesOrNo = true;
        }
    }
    return yesOrNo;
}

///////////////// Unused Functions ///////////////

void Vehicle::follow(Path* p){
    /*
    Pvector *predict = new Pvector(0,0);
    *predict = velocity->get();

    predict->normalize();
    predict->mult(50);
    Pvector *predictLoc = Pvector::add(this->location, predict);

    Pvector *a = p->start;
    Pvector *b = p->end;

    Pvector* normalPoint = Pvector::getNormalPoint(predictLoc, a, b);

    Pvector *dir = Pvector::sub(b,a);
    dir->normalize();
    dir->mult(10);
    Pvector *target = Pvector::add(normalPoint, dir);

    float distance = Pvector::dist(normalPoint, predictLoc);
    if(distance > p->radius){
        seek(target);
    }
    */
    Pvector *target = p->end;

    seek(target);
}


