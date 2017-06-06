#include "vehicle.h"


///////////////// Constructor ///////////////

Vehicle::Vehicle(float x, float y, int _id, float v)
{
    location = new Pvector(x,y);
    velocity = new Pvector(0,0);
    acceleration= new Pvector(0,0);
    goal = new JunctionPoint(0,0,0);    // A point that attracts agent
    counter = 0;                        // To make sure only one behavior is being carried out at a time
    maxforce= 0.3;                      // Stronger the max force, more directly it's attracted
    maxspeed= v;                        // Higher the max speed, faster it goes

    lifespan =250;                      // No use
    mass =1;                            // No use
    id= _id;                            // No use
}

///////////////// Main Functions ///////////////

void Vehicle::chooseJunction(Path* p){

    float distance = 0;
    float smallest = 100000;

    if(setGoal() && aboutToGo()){                           // is true if the car is ready to drive in to a street (i.e. at an "in" point)

        tempVar = tempGoal;

        unsigned long index = this->goal->index;            // get the index of the standing point in terms of all 8 junction points
        index = (index + 5) % 8;                            // calculate the corresponding position at the other junction to "drive out"

        for(unsigned long i = 0; i < p->mainJunctions.size(); i++){

            if(isAccessible(p, i, index) && i != tempVar){  // if the point asked is accessible and it's not at my own junction

                distance = Pvector::dist(p->mainJunctions[i]->subJunctions[index], this->location);

                if(distance < smallest){
                    smallest = distance;
                    tempGoal = i;                            // find out which junction has the cloest "drive out" point
                }
            }
        }
        // set my goal to that junciton, in particular the corresponding point
        *(this->goal) = p->mainJunctions[tempGoal]->subJunctions[index]->get();

        this->counter += 1;
    }

    else if(setGoal()){                                      // is true if the car is on a street or somewhere else, but not at the in/out points

        for( unsigned long i = 0; i < p->mainJunctions.size(); i++){

            distance = Pvector::dist( p->mainJunctions[i]->junLocation, this->location); // calculate the dist to all junctions

            if(distance <= smallest){
                smallest = distance;
                tempGoal = i;                                                            // find out which junction is the closet
            }
        }
        // randomly pick up one junction point to arrive at the chosen junction
        for( unsigned long i = 0; i < p->mainJunctions[tempGoal]->subJunctions.size(); i ++){

            if(isInOrOut(p, this->tempGoal, i, 0) && isAccessible(p, this->tempGoal, i) != false){

                JunctionPoint point = p->mainJunctions[tempGoal]->subJunctions[i]->get();

                this->possibleDest.push_back(point);

            }
        }

        int options = this->possibleDest.size();
        int decision = rand() % options;

        *(this->goal) = this->possibleDest[decision].get();
        this->possibleDest.clear();

        this->counter += 1;
    }
    stopIfCloseEnough();
}

void Vehicle::makeTurn(Path* p){

    if(setGoal() && isArrived()){                    // is true if the car is arrived at the "drive out" point and ready to make turn

        for(unsigned long i = 0; i < p->mainJunctions[tempGoal]->subJunctions.size(); i++){

            // check only the "drive in" points in this junction and if they are accesssible
            if(isInOrOut(p, this->tempGoal, i, 1) && isAccessible(p, this->tempGoal, i)){

                JunctionPoint point = p->mainJunctions[tempGoal]->subJunctions[i]->get();

                this->possibleDest.push_back(point); // randomly choose one junction points, and set it as goal
            }
        }
        int options = this->possibleDest.size();
        int decision = rand() % options;

        *(this->goal) = this->possibleDest[decision].get();
        this->possibleDest.clear();

        this->counter += 1;
    }
    stopIfCloseEnough();
}

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

void Vehicle::seek(Pvector* target)
{
    Pvector *desired = Pvector::sub(target, this->location);
    desired->normalize();
    desired->mult(.9);

    Pvector *steer= Pvector::sub(desired, this->velocity);
    limit(steer,maxforce);
    applyForce(steer);
}

void Vehicle::update()
{
    velocity->add(acceleration);
    limit(velocity, maxspeed);
    location->add(velocity);
    acceleration->mult(0);
}

void Vehicle::separate(std::vector<Vehicle*> vehicles)
{
    float desiredSeperation = 10 * 2; //5= radius of car object
    int tooCloseCount =0;
    Pvector *sum = new Pvector(0,0);

    for (std::vector<Vehicle*>::iterator it = vehicles.begin() ; it != vehicles.end(); ++it )
    {
        float d = Pvector::dist(location, (*it)->location);

        if ((d > 0) && (d < desiredSeperation))
        {
            Pvector *diff = Pvector::sub(location, (*it)->location);  //Calculate vector pointing away from neighbor
            diff->normalize();
            diff->div(d);           //weight by distance
            sum->add(diff);

            tooCloseCount ++;       // keeping track
        }

    }

    // Average //

    if(tooCloseCount > 0)
    {
        sum->div(tooCloseCount);
        sum->setMag(maxspeed);

        Pvector *steer = Pvector::sub(sum, velocity);
        steer->limit(maxforce);
        applyForce(steer);
    }

}

///////////////// Sub Functions ///////////////

// Stop the car if it is very close to goal, and reset counter back to zero, so that next behavior can be carried out
void Vehicle::stopIfCloseEnough(){

    float approach = Pvector::dist(this->goal, this->location);

    if(approach < 1){
        *(this->location) = *(this->goal);
        this->counter = 0;
    }

}

// Return true only if the previous behaior is finished (i.e. counter = 0)
bool Vehicle::setGoal(){
    bool yesOrNo = true;

    if(this->counter > 0){
        yesOrNo = false;
    }

    return yesOrNo;
}

// Return true if the car has reached the goal (i.e. at the "out" point)
bool Vehicle::isArrived(){
    if(this->location->x == this->goal->x && this->location->y == this->goal->y && this->goal->inOrOut == 0){
        return true;
    }else
        return false;
}

// Return true if the car has reached the goal (i.e. at the "in" point)
bool Vehicle::aboutToGo(){
    if(this->location->x == this->goal->x && this->location->y == this->goal->y && this->goal->inOrOut == 1){
        return true;
    }else
        return false;
}

// Return true if the point asked is accessible ( p->mainJunctions[argument1]->subJunctions[argument2]->accessible )
bool Vehicle::isAccessible(Path* p, unsigned long i, unsigned long j){
    if (p->mainJunctions[i]->subJunctions[j]->accessible == 1){
        return true;
    }else{
        return false;
    }
}

// Return true if the point asked is In or Out ( p->mainJunctions[argument1]->subJunctions[argument2]->argument3 )
bool Vehicle::isInOrOut(Path* p, unsigned long i, unsigned long j, bool in_or_out){
    if (p->mainJunctions[i]->subJunctions[j]->inOrOut == in_or_out){
        return true;
    }else{
        return false;
    }
}



void Vehicle::limit(Pvector* vec,float max){
    if (vec->mag() > max)
    {
        vec->normalize();
        vec->mult(max);
    }
}

float Vehicle::map(float d, float ilb, float iub, float olb, float oub)
{
    return (((oub-olb)*d)/(iub-ilb));
}


///////////////// Unused Functions ///////////////
/*
void Vehicle::follow(Path* p){

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

    Pvector *target = p->end;

    seek(target);
}
*/

