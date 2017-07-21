#include "drunkdriver.h"

DrunkDriver::DrunkDriver(float posX, float posY, int _id, float maxV, Path* p)
    :Vehicle(posX, posY, _id, maxV, p)
{
    setInitDest(p);
}

void DrunkDriver::move(std::vector<Vehicle *> vehicles){

    applyBehaviour(vehicles);


    float tmpDist = Pvector::dist(location, longTermDest);

    if( tmpDist < 20 ){
        reachedDest = true;
    }

    if(reachedDest != true){
        timesTaken++;
    }

}

void DrunkDriver::makeTurn(Path* p){

    if(setGoal() && isArrived()){                    // is true if the car is arrived at the "drive out" point and ready to make turn

        for(unsigned long i = 0; i < p->mainJunctions[tempGoal]->subJunctions.size(); i++){

            // check only the "drive in" points in this junction and if they are accesssible
            if(isInOrOut(p, this->tempGoal, i, 1) && isAccessible(p, this->tempGoal, i)){

                JunctionPoint point = p->mainJunctions[tempGoal]->subJunctions[i]->get();

                this->possibleDest.push_back(point); // randomly choose one junction points, and set it as goal
            }
        }
        unsigned long options = this->possibleDest.size();

        ///
        Pvector* destVec = Pvector::sub(longTermDest, goal);

        int tempChoice = 0;
        float tempAngle = 1800;

        for(unsigned long i = 0; i < options; i++){

            Pvector* tmpVec = Pvector::sub(&possibleDest[i], goal);
            float angle = Pvector::angleBetween(destVec, tmpVec);

            if(angle < tempAngle){

                tempAngle = angle;
                tempChoice = i;
            }
        }
        *(this->goal) = this->possibleDest[tempChoice].get();
        ///

        this->possibleDest.clear();

        goals.erase (goals.begin());
        goals.push_back(goal);

        this->counter += 1;
    }
}

Pvector* DrunkDriver::follow()
{

    Pvector *here = new Pvector(0,0);
    *here = this->goals[myCurrentGoal]->get();

    Pvector *there = new Pvector(0,0);
    *there = this->goals[myCurrentGoal + 1]->get();

    float worldRecord = 1000000;
    Pvector *foll =  new Pvector(0,0);

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

    if (worldRecord > 5)    //5 is the path radius
    {
        foll = seek(target);

    }
    return foll;

}

Pvector* DrunkDriver::separate(std::vector<Vehicle*> vehicles)
{
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
        return sum;
    }
}

// Behaviour function (following and separation)
void DrunkDriver::applyBehaviour(std::vector<Vehicle*> vehicles)   //overwritten with introduced weights for seperate and follow
{
    Pvector* sep = separate(vehicles);
    Pvector* foll = follow();
    Pvector* arr = arrive(vehicles);

    sep->mult(sepWeight);       //weight for seperate behaviour (high value will mean high consideration for *seperation*)
    foll->mult(folWeight);    //weight for follow behaviour (  "  *follow*)
    arr->mult(0.5);

    calulateDist();
    //applyForce(sep);
    applyForce(foll);
    applyForce(arr);

}


void DrunkDriver::calulateDist()
{
    float panic = 0;
    float dist = Pvector::dist(location, longTermDest);

    if(dist < 400){

        panic = map(dist, 0, 400, 2, 10);

        folWeight = 2;

        arrWeight = 0.2 ;
    }
}

