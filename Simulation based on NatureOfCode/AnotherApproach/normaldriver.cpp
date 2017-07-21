#include "normaldriver.h"

NormalDriver::NormalDriver(float posX, float posY, int _id, float maxV, Path* p)
    : Vehicle(posX, posY, _id, maxV, p)
{
    setInitDest(p);
}

void NormalDriver::move(std::vector<Vehicle *> vehicles){

    applyBehaviour(vehicles);

}

void NormalDriver::makeTurn(Path* p){

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



// Driving towards my goal (junction points), but follow someone when someone is there (No too close to him though)
Pvector* NormalDriver::arrive(std::vector<Vehicle *> vehicles)
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

                float distToHim = Pvector::dist(possibleCars[i]->location, location);

                if(hisDistToThere < myDistToThere && distToHim < tempD){
                    followSomeone = true;
                    whoIfollowed = i;
                    tempD = distToHim;

                }
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
        else{                               // Cannot not find anyone to follow? okay, then go where you planned to go
            sum = goToJunction();
        }
    }else{
        sum = goToJunction();
    }

    possibleCars.clear();
    return sum;

}
// Go to my goal (junction points)
Pvector * NormalDriver::goToJunction(){

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

void NormalDriver::findSomeoneInFront(std::vector<Vehicle *> vehicles){

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

Pvector* NormalDriver::separate(std::vector<Vehicle*> vehicles)    // is not a void function now
{
    float desiredSeperation = 10; //5= radius of car object
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

    }

    if (sum->mag() > 0)
    {
        sum->setMag(maxspeed);
        sum->sub(velocity);
        sum->limit(maxforce);
    }
    return sum;   //returns the force vector to be applied

}

// Behaviour function (following and separation)

void NormalDriver::applyBehaviour(std::vector<Vehicle*> vehicles)   //overwritten with introduced weights for seperate and follow
{
    //Pvector* sep = separate(vehicles);
    Pvector* arr = arrive(vehicles);
    Pvector* foll = follow();

    foll->mult(0.5);
    //sep->mult(1);                      //weight for seperate behaviour (high value will mean high consideration for *seperation*)
    arr->mult(1);

    //applyForce(sep);
    applyForce(foll);
    applyForce(arr);

}




