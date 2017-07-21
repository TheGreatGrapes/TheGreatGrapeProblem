#include "vehicle.h"



///////////////// Constructor ///////////////

Vehicle::Vehicle(float x, float y, int _id, float v, Path* p)
{

    location = new Pvector(x,y);
    velocity = new Pvector(0,0);
    acceleration = new Pvector(0,0);
    mySteerForce = new Pvector(0,0);
    longTermDest = new Pvector(0,0);
    goal = new JunctionPoint(0,0,0);    // A point that attracts agent

    counter = 0;                        // To make sure only one behavior is being carried out at a time
    maxforce= 0.5 * v;                  // Stronger the max force, more directly it's attracted
    maxspeed= v;                        // Higher the max speed, faster it goes
    myCurrentGoal = 0;                  // Work as an index pointing to the current goal in a vector
    onlyOnce = 0;                       // A variable that make sure an if-statement runs only once
    whoIfollowed = 0;                   // The index of the guy i am followed in terms of in an array(vector)
    timesReached = 0;
    timesTaken = 0;

    // Behaviour weight
    sepWeight = 0.5;
    folWeight = 1;
    arrWeight = 0.7;

    reachedDest = false;
    followSomeone = false;              // True if i am following someone

    goals.push_back(location);

    ///////// No Used Variable ////////
    id= _id;                            // Identity
    mass = 1;                           // No use

}

Vehicle::~Vehicle()
{

}

///////////////// Behaviors ///////////////

void Vehicle::move(std::vector<Vehicle *> vehicles){

}



// Choose which main junction to go
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

        goals.erase (goals.begin());
        goals.push_back(goal);

        this->counter += 1;
    }

    else if(setGoal() && onlyOnce == 0){                                      // is true if the car is on a street or somewhere else, but not at the in/out points

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

        goals.push_back(goal);

        this->counter += 1;
        onlyOnce ++;
    }
}

// Choose which junction points to turn
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

        goals.erase (goals.begin());
        goals.push_back(goal);

        this->counter += 1;
    }
}

// Driving towards my goal (junction points), but follow someone when he is there (No too close to him though)
Pvector* Vehicle::arrive(std::vector<Vehicle *> vehicles)
{
    Pvector *sum = new Pvector(0,0);

    if(followSomeone == false && goal->inOrOut == 0){

        findSomeoneInFront(vehicles);

        // Find if anyone is in front of me
        for(unsigned long i = 0; i < possibleCars.size(); i++){

            float sameGoal = Pvector::dist(goal, possibleCars[i]->goal);
            float tempD = 10000;

            if(sameGoal == 0 && possibleCars[i]->goal->inOrOut == goal->inOrOut){

                float myDistToThere = Pvector::dist(goal, location);
                float hisDistToThere = Pvector::dist(possibleCars[i]->goal, possibleCars[i]->location);
                //float myReachingTime = myDistToThere / velocity->mag();
                //float hisReachingTime = hisDistToThere / possibleCars[i]->velocity->mag();
                float distToHim = Pvector::dist(possibleCars[i]->location, location);

                if(hisDistToThere < myDistToThere && distToHim < tempD){
                    followSomeone = true;
                    whoIfollowed = i;
                    tempD = distToHim;
                    //  if(possibleCars[i]->followSomeone == true && possibleCars[i]->possibleCars[possibleCars[i]->whoIfollowed]->id == id ){

                }//else{
            //}
            }
        }
    }


    if(followSomeone == true && goal->inOrOut == 0){

        float distToSomeone = Pvector::dist( possibleCars[whoIfollowed]->location, location); // check the distance and the guy driving ahead

        if(velocity->mag() != 0)            // Stay where i am at the moment i find him
        {
            *mySteerForce = velocity->get();
            mySteerForce->mult(-1);
            applyForce(mySteerForce);

        }else if(distToSomeone < 20){       // Wait and do nothing until someone in front is already 30 pixel away

        }
        else{                                                       // Cannot not find anyone to follow? okay, then go where you planned to go
            sum = goToJunction();
        }
    }else{
        sum = goToJunction();
    }

    possibleCars.clear();
    return sum;

}


Pvector* Vehicle::follow()   //is not a void function now
{

    Pvector *here = new Pvector(0,0);
    *here = this->goals[myCurrentGoal]->get();

    float worldRecord = 1000000;

    Pvector *there = new Pvector(0,0);
    *there = this->goals[myCurrentGoal + 1]->get();
    Pvector *foll = new Pvector(0,0);

    Pvector predict = velocity->get();
    predict.normalize();
    predict.mult(25);
    Pvector *predictLoc = Pvector::add(location, &predict );

    //Single path

    Pvector *normalPoint = Pvector::getNormalPoint(predictLoc, here, there);

    if(normalPoint->x < fmin(here->x, there->x) || normalPoint->x > fmax(here->x, there->x))
    {
        *normalPoint = there->get();
    }
    else if(normalPoint->y < fmin(here->y, there->y) || normalPoint->y > fmax(here->y, there->y))
    {
        *normalPoint = there->get();
    }

    Pvector *dir = Pvector::sub(there, here);
    dir->normalize();
    dir->mult(10);
    Pvector *target = Pvector::add(normalPoint, dir);

    //float distance = Pvector::dist(normalPoint, predictLoc);
    //if(distance > 10)
    //{
    if (worldRecord > 5)
    {
        foll = seek(target);

    }
    return foll;   //returns the force required to follow a path

    //}
}

Pvector* Vehicle::separate(std::vector<Vehicle*> vehicles)    // is not a void function now
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

        //Pvector *steer = Pvector::sub(sum, velocity);
        //steer->limit(maxforce);
        //applyForce(steer);
    }
    if (sum->mag() > 0)
    {
        sum->setMag(maxspeed);
        sum->sub(velocity);
        sum->limit(maxforce);
    }
    return sum;   //returns the force vector to be applied
}


// Behaviour function (following and separation)   (overwritten for drunk drivers in drunkdriver class)
void Vehicle::applyBehaviour(std::vector<Vehicle*> vehicles)
{
/*    Pvector* sep = separate(vehicles);
    Pvector* foll = follow();

    sep->mult(1);       //weight for seperate behaviour (high value will mean high consideration for *seperation*)
    foll->mult(1);    //weight for follow behaviour (  "  *follow*)
    //arr->mult(1.5);

    applyForce(sep);
    applyForce(foll);*/
}


// Go to my goal (junction points)
Pvector* Vehicle::goToJunction(){

    Pvector *desired = Pvector::sub(this->goal, this->location);

    float d = desired->mag();
    desired->normalize();

    if(d < 100)
    {
        float m= map(d, 0, 100, 0, maxspeed);
        desired->mult(m);
    }
    else {
        desired->mult(maxspeed);
    }

    Pvector *steer = Pvector::sub(desired, this->velocity);
    steer->limit(maxforce);
    //applyForce(steer);

    followSomeone = false;
    return steer;
}


Pvector* Vehicle::seek(Pvector* target)
{
    Pvector *desired = Pvector::sub(target, this->location);
    desired->normalize();
    float desiredMax = maxspeed * 0.7;
    desired->mult(desiredMax);

    Pvector *steer= Pvector::sub(desired, this->velocity);
    steer->limit(maxforce);
    //applyForce(steer);

    followSomeone = false;
    return steer;
}




// Loop through all cars except myself, see if i can find someone driving ahead of me. If yes, then i will remember him.
void Vehicle::findSomeoneInFront(std::vector<Vehicle *> vehicles){

    // Look around
    float desiredSeperation = 18;                                                 // 5 = radius of car object

    for ( unsigned long i = 0 ; i < vehicles.size(); i++ )
    {
        Pvector *pointToSomeone = Pvector::sub( vehicles[i]->location, location); // Calculate vector pointing to neighbor
        float angle = Pvector::angleBetween(velocity, pointToSomeone);
        float d = pointToSomeone->mag();

        if( d != 0 && d <= desiredSeperation && angle < 20){

            possibleCars.push_back(vehicles[i]);
        }
    }
}


void Vehicle::applyForce(Pvector* force)
{
    Pvector *f= Pvector::div(force,this->mass);
    acceleration->add(f);
}

void Vehicle::update()
{
    velocity->add(acceleration);
    velocity->limit(maxspeed);
    location->add(velocity);
    acceleration->mult(0);

    stopIfCloseEnough();

}
/*
void Vehicle::makeNewDest(Path* p)
{
    float tmpDist = Pvector::dist(location, destination);
    int tmpMain = 0;

    if((tmpDist < 20) or (destination->x == 1000 and destination->y==1000) ){

        do{

            tmpMain = rand() % p->mainJunctions.size();

            tmpDist = Pvector::dist(p->mainJunctions[tmpMain]->junLocation, location);

        }while(tmpDist < 300);

        for(unsigned long i = 0; i < p->mainJunctions[tmpMain]->subJunctions.size(); i++){

            // check only the "drive in" points in this junction and if they are accesssible
            if(isInOrOut(p, this->tempGoal, i, 1) && isAccessible(p, tmpMain, i)){

                JunctionPoint point = p->mainJunctions[tmpMain]->subJunctions[i]->get();

                possibleDest.push_back(point); // randomly choose one junction points, and set it as goal
            }
        }
        int options = possibleDest.size();

        float tmpSub = rand() % options;

        *destination = possibleDest[tmpSub].get();

        timesReached++;

        possibleDest.clear();

    }

    if(timesReached >= 5){
        reachedDest = true;
    }
}
*/

void Vehicle::setInitDest(Path* p)
{
    unsigned long size = p->Destinations.size();
    int ran = rand() % size;
    *longTermDest = p->Destinations[ran]->get();
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


float Vehicle::map(float d, float ilb, float iub, float olb, float oub)
{
    return (((oub-olb)*d)/(iub-ilb));
}

