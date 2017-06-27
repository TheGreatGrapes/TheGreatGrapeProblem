#include "vehicle.h"



///////////////// Constructor ///////////////

Vehicle::Vehicle(float x, float y, int _id, float v)
{
    location = new Pvector(x,y);
    velocity = new Pvector(0,0);
    acceleration = new Pvector(0,0);
    mySteerForce = new Pvector(0,0);

    goals.push_back(location);

    goal = new JunctionPoint(0,0,0);    // A point that attracts agent
    counter = 0;                        // To make sure only one behavior is being carried out at a time
    maxforce= 0.5 * v;                  // Stronger the max force, more directly it's attracted
    maxspeed= v;                        // Higher the max speed, faster it goes
    followSomeone = false;              // True if i am following someone
    myCurrentGoal = 0;                  // Work as an index pointing to the current goal in a vector
    onlyOnce = 0;                       // A variable that make sure an if-statement runs only once
    whoIfollowed = 0;                   // The index of the guy i am followed in terms of in an array(vector)

    id= _id;                            // Identity

    lifespan =250;                      // No use
    mass = 1;                           // No use


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
        ;

        *(this->goal) = this->possibleDest[decision].get();
        this->possibleDest.clear();

        goals.erase (goals.begin());
        goals.push_back(goal);

        this->counter += 1;
    }
}

// Driving towards my goal (junction points), but follow someone when he is there (No too close to him though)
void Vehicle::arrive(std::vector<Vehicle *> vehicles)
{
    if(followSomeone == false)                                   // Find someone if i am not following anyone
    {
        findSomeoneInFront(vehicles);
    }

    float distToSomeone = Pvector::dist( vehicles[whoIfollowed]->location, location); // check the distance and the guy driving ahead

    if(followSomeone == true && velocity->mag() != 0)            // Stay where i am at the moment i find him
    {
        *mySteerForce = velocity->get();
        mySteerForce->mult(-1);
        applyForce(mySteerForce);

    }else if(followSomeone == true && distToSomeone < 30){       // Wait and do nothing until someone in front is already 30 pixel away

    }else                                                        // Cannot not find anyone to follow? okay, then go where you planned to go
    {
        goToJunction();
    }

    // Ignore below commented code, Tim is experimenting something

    /*if(followSomeone == false)                                   // Find someone if i am not following anyone
    {
        findSomeoneInFront(vehicles);
    }

    Pvector* pointToSomeone = Pvector::sub(vehicles[whoIfollowed]->location, location);
    float distToSomeone = pointToSomeone->mag();
    float angle = Pvector::angleBetween(velocity, pointToSomeone);
    float sameGoal = Pvector::dist( vehicles[whoIfollowed]->goal, goal);

    if(followSomeone == true && angle < 0.1 && velocity->mag() != 0 && sameGoal == 0)
    {
        *mySteerForce = velocity->get();
        mySteerForce->mult(-1);
        applyForce(mySteerForce);
    }

    else if( followSomeone == true && velocity->mag() != 0 && priority < vehicles[whoIfollowed]->priority)
    {
        *mySteerForce = velocity->get();
        mySteerForce->mult(-1);
        applyForce(mySteerForce);
    }

    else if( followSomeone == true && velocity->mag() != 0 && priority > vehicles[whoIfollowed]->priority)
    {
        follow();
    }

    else if( followSomeone == true && velocity->mag() != 0 && priority == vehicles[whoIfollowed]->priority)
    {

        float myDistToThere = Pvector::dist(goals[1], location);
        float hisDistToThere = Pvector::dist(vehicles[whoIfollowed]->goals[1], vehicles[whoIfollowed]->location);

        if(myDistToThere > hisDistToThere)
        {
            *mySteerForce = velocity->get();
            mySteerForce->mult(-1);
            applyForce(mySteerForce);
        }
        else{
            follow();
        }
    }
    else if(followSomeone == true && velocity->mag() == 0 && distToSomeone < 30)         // Wait and do nothing until someone in front is already 30 pixel away
    {
        // *mySteerForce = vehicles[whoIfollowed]->velocity
    }
    else                                                        // Cannot not find anyone to follow? okay, then go where you planned to go
    {

        //goToJunction();
        follow();
    }
    */
}


void Vehicle::follow()
{

    Pvector *here = new Pvector(0,0);
    *here = this->goals[myCurrentGoal]->get();

    Pvector *there = new Pvector(0,0);
    *there = this->goals[myCurrentGoal + 1]->get();

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
    seek(target);
    //}
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

// Go to my goal (junction points)
void Vehicle::goToJunction(){

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
    steer->limit(maxforce);
    applyForce(steer);

    followSomeone = false;
}


void Vehicle::seek(Pvector* target)
{
    Pvector *desired = Pvector::sub(target, this->location);
    desired->normalize();
    float desiredMax = maxspeed * 0.7;
    desired->mult(desiredMax);

    Pvector *steer= Pvector::sub(desired, this->velocity);
    steer->limit(maxforce);
    applyForce(steer);

    followSomeone = false;
}

// Loop through all cars except myself, see if i can find someone driving ahead of me. If yes, then i will remember him.
void Vehicle::findSomeoneInFront(std::vector<Vehicle *> vehicles){

    float desiredSeperation = 20;                                                 // 5 = radius of car object
    float tempD = 100000;

    for ( unsigned long i = 0 ; i < vehicles.size(); i++ )
    {
        Pvector *pointToSomeone = Pvector::sub( vehicles[i]->location, location); // Calculate vector pointing to neighbor
        float angle = Pvector::angleBetween(velocity, pointToSomeone);
        float d = pointToSomeone->mag();

        // if someone is driving ahead of me on the same street (pick the cloest someone), remember him
        if( d != 0 && d <= desiredSeperation && angle == 0 && d < tempD){

            followSomeone = true;
            whoIfollowed = i;
            tempD = d;
        }
    }

    // Ignore below commented code, Tim is experimenting something

    /*
    float desiredSeperation = 17;                                                 // 5 = radius of car object
    float tempD = 100000;

    for ( unsigned long i = 0 ; i < vehicles.size(); i++ )
    {
        Pvector *pointToSomeone = Pvector::sub( vehicles[i]->location, location); // Calculate vector pointing to neighbor
        float angle = Pvector::angleBetween(velocity, pointToSomeone);
        float d = pointToSomeone->mag();

        // if someone is driving ahead of me on the same street (pick the cloest someone), remember him
        if( d != 0 && d <= desiredSeperation && angle < 10 && d < tempD){

            followSomeone = true;
            whoIfollowed = i;
            tempD = d;
        }
    }
*/
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

