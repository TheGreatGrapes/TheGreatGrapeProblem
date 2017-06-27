#include "normaldriver.h"

NormalDriver::NormalDriver(float posX, float posY, int _id, float maxV)
  : Vehicle(posX, posY, _id, maxV)
{

}

void NormalDriver::move(std::vector<Vehicle *> vehicles){
    arrive(vehicles);
}

// Driving towards my goal (junction points), but follow someone when someone is there (No too close to him though)
void NormalDriver::arrive(std::vector<Vehicle *> vehicles)
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

    /*
    if(followSomeone == false)                                   // Find someone if i am not following anyone
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



// Go to my goal (junction points)
void NormalDriver::goToJunction(){

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
    applyForce(steer);

    followSomeone = false;
}

void NormalDriver::findSomeoneInFront(std::vector<Vehicle *> vehicles){

    float desiredSeperation = 15;                                                 // 5 = radius of car object
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
