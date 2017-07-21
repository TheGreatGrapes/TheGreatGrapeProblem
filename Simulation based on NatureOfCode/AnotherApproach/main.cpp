/*****************************************************************
 * Project:     Traffic Simulation through Agent-based Modelling
 *
 * Lecture:     System & Self-Organization
 *
 * Objective:   Modelling the driving behavior in a pre-defined
 *              area by implementing different behavior of agents.
 *              The driving behavior is stongly influenced by the
 *              interaction with other drivers on the road. A traffic
 *              scenario can therefore be simulated by intrducing
 *              different kinds/ numbers of agents in the simulation.
 *
 * Last update: 21.07.2017
 ******************************************************************/


#include "dialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
