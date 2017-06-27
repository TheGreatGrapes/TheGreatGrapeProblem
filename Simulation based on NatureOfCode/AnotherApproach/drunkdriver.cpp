#include "drunkdriver.h"

DrunkDriver::DrunkDriver(float posX, float posY, int _id, float maxV)
    :Vehicle(posX, posY, _id, maxV)
{

}

void DrunkDriver::move(std::vector<Vehicle *> vehicles){
    follow();
    separate(vehicles);
}

void DrunkDriver::follow()
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

void DrunkDriver::separate(std::vector<Vehicle*> vehicles)
{
    float desiredSeperation = 15 ; //5= radius of car object
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
