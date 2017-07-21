#include "dialog.h"
#include "ui_dialog.h"


///////////// Global Variables //////////////////

int numberOfNormalCars = 50 ;              // Self-explanatory
int numberOfDrunkCars = 0 ;                // Self-explanatory
int numberOfRoamingCars = 50;              // Self-explanatory

unsigned long counter = 0;                 // Counting the loops

int r = 5;
bool confirm = false;

///////////////////////////////////////////////

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
    /////////////// System Settings ////////////////
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect( -250, -250, 250*2, 250*2 );
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(theLoop()));
    timer->start(1); // run in 1ms

    ///////////// Object Initiations ////////////////

    srand(time(NULL));

    p = new Path();

    for(int i = 0; i < numberOfNormalCars; i++)
    {
        vehicles.push_back( new NormalDriver( rand() % 800 - 400, rand() % 800 - 400, 1, rand() % 3 + 1, p));
    }
    for(int i = 0; i < numberOfDrunkCars; i++)
    {
        vehicles.push_back( new DrunkDriver( rand() % 800 - 400, rand() % 800 - 400, 2, rand() % 3 + 1, p ));
    }
    for(int i = 0; i < numberOfRoamingCars; i++)
    {
        vehicles.push_back( new RoamingDriver( rand() % 800 - 400, rand() % 800 - 400, 3, rand() % 3 + 1, p ));
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

    QString counterString;
    QString Car1;
    QString Car2;
    QString Car3;
    QString Car4;
    QString Car5;
    /////////////// Main Code here /////////////////

    // Behavior of cars
    run(vehicles, p);

    if(counter == 0){
        addExperiDriver(10);
        confirm = true;
    }

    ////////////////  Draw Streets ////////////////
    // Draw Streets
    drawMap(lightGray, black);


    // Showing the accessible points on the map, red means no way, yellow means o.k. (It's deactivated now)
    //showJunctions( p, yellow, red);

    ////////////////  Draw Objects ////////////////

    // Color the car by their speed / behavior
    // Drunk drivers are now marked in red, other colors represent only different speed of normal drivers
    drawDest(p, yellow, red);
    drawCars(vehicles, darkCyan, black, darkMagenta, red, blue);

    //////////////////  Counter //////////////////

    counterString.setNum(counter);
    ui->label->setText("Global Time : " + counterString);
    counter++;

    Car1.setNum(vehicles[0]->timesTaken);
    ui->label_3->setText("Car1: " + Car1);

}


void Dialog::run(std::vector<Vehicle *> &vehicles, Path* p){

    if(vehicles.size() == 100 && confirm == true){
        timer->stop();
    }

    for(std::vector<Vehicle*>::iterator i = vehicles.begin(); i < vehicles.end(); i++){

        (*i)->chooseJunction(p);
        (*i)->makeTurn(p);
        (*i)->move(vehicles);
        (*i)->update();

        if((*i)->reachedDest == true)
        {
            vehicles.erase(i);
        }
    }
}

void Dialog::addExperiDriver(unsigned long numberOfExperiCars)
{
    for(int i = 0; i < numberOfExperiCars; i++)
    {
        vehicles.push_back( new DrunkDriver( rand() % 800 - 400, rand() % 800 - 400, 4, 3, p));
    }
}

void Dialog::on_pushButton_clicked()
{
    if(timer->isActive()) timer->stop();
    else timer->start(1);
}

void Dialog::drawMap(QPen lightGray, QPen black)
{
    scene->addLine(-400,-400,-400, 400, lightGray);
    scene->addLine(-400, 400, 400, 400, lightGray);
    scene->addLine( 400, 400, 400,-400, lightGray);
    scene->addLine( 400,-400,-400,-400, lightGray);
    scene->addLine(-400,   0, 400,   0, lightGray);
    scene->addLine(   0,-400,   0, 400, lightGray);
    scene->addLine(-200, 400,-200,-400, lightGray);
    scene->addLine( 200,-400, 200, 400, lightGray);
    scene->addLine(-400,-200, 400,-200, lightGray);
    scene->addLine(-400, 200, 400, 200, lightGray);


    scene->addLine(-400,-400,-400, 400, black);
    scene->addLine(-400, 400, 400, 400, black);
    scene->addLine( 400, 400, 400,-400, black);
    scene->addLine( 400,-400,-400,-400, black);
    scene->addLine(-400,   0, 400,   0, black);
    scene->addLine(   0,-400,   0, 400, black);
    scene->addLine(-400,-200, 400,-200, black);
    scene->addLine(-400, 200, 400, 200, black);
    scene->addLine( 200,-400, 200, 400, black);
    scene->addLine(-200, 400,-200,-400, black);
}

void Dialog::drawCars(std::vector<Vehicle *> &vehicles, QPen darkCyan, QPen black, QPen darkMagenta, QPen red, QPen blue)
{
    std::vector<Vehicle*>::iterator i;

    for( i = vehicles.begin(); i < vehicles.end(); i++){

        if((*i)->reachedDest == true){
            scene->addEllipse((*i)->location->x -(r/2), (*i)->location->y - (r/2), r, r, red, QBrush(Qt::red));
        }
        else if((*i)->id == 1){
            scene->addEllipse((*i)->location->x -(r/2), (*i)->location->y - (r/2), r, r, blue, QBrush(Qt::blue));
        }
        else if((*i)->id == 2){
            scene->addEllipse((*i)->location->x -(r/2), (*i)->location->y - (r/2), r, r, darkCyan, QBrush(Qt::yellow));
        }
        else if((*i)->id == 3){
            scene->addEllipse((*i)->location->x -(r/2), (*i)->location->y - (r/2), r, r, black, QBrush(Qt::yellow));
        }
        else if((*i)->id == 4){
            scene->addEllipse((*i)->location->x -(r/2), (*i)->location->y - (r/2), r, r, red, QBrush(Qt::black));
        }
    }
}

void Dialog::drawDest(Path* p, QPen yellow, QPen red)
{
    unsigned long numOfDest = p->Destinations.size();

    for(unsigned long i = 0; i < numOfDest; i++){
        scene->addEllipse(p->Destinations[i]->x -r, p->Destinations[i]->y - r, 2*r, 2*r, yellow, QBrush(Qt::black));
    }
}

void Dialog::showJunctions(Path* p, QPen yellow, QPen red){

    for(std::vector<Junction*>::iterator i = p->mainJunctions.begin(); i < p->mainJunctions.end(); i++){

        for(std::vector<JunctionPoint*>::iterator j = (*i)->subJunctions.begin(); j < (*i)->subJunctions.end(); j++){

            if((*j)->accessible == false) // <-- change it here
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

void Dialog::on_verticalSlider_valueChanged(int value)
{
    timer->start(value);
}

