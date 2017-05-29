#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "cNodes.h"
#include "cVehicle.h"
#include "cNetwork.h"

using namespace std;

const int COUNTER_MAX = 50;     //Simulation end time
int counter = 0;                //Simulation start time

vector<cNodes> listOfNodes;
vector<cNetwork> listOfNetworks;
vector<cVehicle> listOfVehicles;

int main()
{
    //CREATE THE OBJECTS
    //Junctions
    listOfNodes.push_back(cNodes(1, 0, 0));
    listOfNodes.push_back(cNodes(2, 100, 0));

    //Roads
    listOfNetworks.push_back(cNetwork(1, &listOfNodes[0], &listOfNodes[1], 2));

    //Vehicles
    listOfVehicles.push_back(cVehicle(1, 0.5, 1, 0, &listOfNetworks[0], 1 ));
    //listOfVehicles.push_back(cVehicle(2, 0, 3, 0, &listOfNetworks[0], 1 ));

   /* do{

        counter++;          //increment the counter i.e. time

    }while(counter<=COUNTER_MAX);*/

    return 0;
}
