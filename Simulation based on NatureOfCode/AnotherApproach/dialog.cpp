#include "dialog.h"
#include "ui_dialog.h"


///////////// Global Variables //////////////////

extern int windowSize;
int numberOfcars = 10;

///////////////////////////////////////////////

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ///////////// System Settings ////////////////
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(-windowSize,-windowSize,windowSize*2,windowSize*2);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(theLoop()));
    timer->start(5); // run in 1ms

    ///////////// Object Initiations ////////////////

    srand(time(NULL));

    p = new Path();

    for(int i = 0; i < numberOfcars; i++)
    {
        vehicles.push_back( new Vehicle( rand() % 500 - 250, rand() % 500 - 250, rand() % 5, rand() % 8 + 4));
    }

}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::theLoop(){

    ///////////// Graphics Settings ////////////////
    scene->clear();
    QPen darkCyan = QPen(Qt::darkCyan, 3);
    QPen yellow = QPen(Qt::yellow, 3);
    QPen lightGray = QPen(Qt::lightGray, 40);
    QPen darkMagenta = QPen(Qt::darkMagenta, 3);
    QPen black = QPen(Qt::black, 3);
    QPen red = QPen(Qt::red, 3);
    QPen blue = QPen(Qt::blue, 3);

    /////////////// Main Code here /////////////////

    // Behavior of cars
    run(vehicles, p);

    ////////////////  Draw Streets ////////////////
    // Draw Streets
    drawMap(lightGray, black);


    // Showing the accessible points on the map, red means no way, yellow means o.k. (It's deactivated now)
    //showJunctions( p, yellow, red);

    ////////////////  Draw Objects ////////////////

    // Color the car by their car-id
    drawCars(vehicles, darkCyan, yellow, darkMagenta, red, blue);



}


void Dialog::run(std::vector<Vehicle *> &vehicles, Path* p){

    for(std::vector<Vehicle*>::iterator i = vehicles.begin(); i < vehicles.end(); i++){

        (*i)->chooseJunction(p);
        (*i)->makeTurn(p);
        (*i)->arrive();
        //(*i)->separate(vehicles);
        (*i)->update();
    }
}

void Dialog::on_pushButton_clicked()
{
    if(timer->isActive()) timer->stop();
    else timer->start(1);
}

void Dialog::drawMap(QPen lightGray, QPen black)
{
    scene->addLine(-200,-200,-200, 200, lightGray);
    scene->addLine(-200, 200, 200, 200, lightGray);
    scene->addLine( 200, 200, 200,-200, lightGray);
    scene->addLine( 200,-200,-200,-200, lightGray);
    scene->addLine(-200,   0, 200,   0, lightGray);
    scene->addLine(   0,-200,   0, 200, lightGray);
    scene->addLine(-200,-200,-200, 200, black);
    scene->addLine(-200, 200, 200, 200, black);
    scene->addLine( 200, 200, 200,-200, black);
    scene->addLine( 200,-200,-200,-200, black);
    scene->addLine(-200,   0, 200,   0, black);
    scene->addLine(   0,-200,   0, 200, black);
}

void Dialog::drawCars(std::vector<Vehicle *> &vehicles, QPen darkCyan, QPen yellow, QPen darkMagenta, QPen red, QPen blue)
{
    std::vector<Vehicle*>::iterator i;

    for( i = vehicles.begin(); i < vehicles.end(); i++){

        if((*i)->id == 0){
            scene->addEllipse((*i)->location->x -5, (*i)->location->y -5, 10, 10, darkCyan, QBrush(Qt::darkCyan));
        }
        else if((*i)->id == 1){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y -5, 10, 10, yellow, QBrush(Qt::yellow));
        }
        else if((*i)->id == 2){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y-5, 10, 10, darkMagenta, QBrush(Qt::darkMagenta));
        }
        else if((*i)->id == 3){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y-5, 10, 10, red, QBrush(Qt::red));
        }
        else if((*i)->id == 4){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y-5, 10, 10, blue, QBrush(Qt::blue));
        }
    }
}

void Dialog::showJunctions(Path* p, QPen yellow, QPen red){

    for(std::vector<Junction*>::iterator i = p->mainJunctions.begin(); i < p->mainJunctions.end(); i++){

        for(std::vector<JunctionPoint*>::iterator j = (*i)->subJunctions.begin(); j < (*i)->subJunctions.end(); j++){

            if((*j)->accessible == false)
            {
                scene->addEllipse( (*j)->x -5, (*j)->y -5, 10, 10, red, QBrush(Qt::red));
            }
            else{
                scene->addEllipse( (*j)->x -5, (*j)->y -5, 10, 10, yellow, QBrush(Qt::yellow));
            }
        }          // Alternatively,
        // showing the in/out points at the junction, by changing the keyword from "accessible" to "inOrOut"
    }              // false = 0 means out, true = 1 means in.
}
