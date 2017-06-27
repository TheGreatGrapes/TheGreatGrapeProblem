#include "dialog.h"
#include "ui_dialog.h"


///////////// Global Variables //////////////////

int numberOfNormalcars = 200 ;          // Self-explanatory
int numberOfDrunkcars = 10 ;            // Self-explanatory
long long counter = 0;                  // Counting the loops

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

     srand(1);

    p = new Path();

    for(int i = 0; i < numberOfNormalcars; i++)
    {
        vehicles.push_back( new NormalDriver( rand() % 800 - 400, rand() % 800 - 400, rand() % 5, rand() % 3 + 1));
    }
    for(int i = 0; i < numberOfDrunkcars; i++)
    {
        vehicles.push_back( new DrunkDriver( rand() % 800 - 400, rand() % 800 - 400, 5 , rand() % 3 + 1 ));
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

    // Color the car by their speed / behavior
    // Drunk drivers are now marked in red, other colors represent only different speed of normal drivers
    drawCars(vehicles, darkCyan, yellow, darkMagenta, red, blue);

    //////////////////  Counter //////////////////

    QString counterString;
    counterString.setNum(counter);
    ui->label->setText(counterString);
    counter++;
}


void Dialog::run(std::vector<Vehicle *> &vehicles, Path* p){

    for(std::vector<Vehicle*>::iterator i = vehicles.begin(); i < vehicles.end(); i++){

        (*i)->chooseJunction(p);
        (*i)->makeTurn(p);
        (*i)->move(vehicles);
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

void Dialog::drawCars(std::vector<Vehicle *> &vehicles, QPen darkCyan, QPen yellow, QPen darkMagenta, QPen red, QPen blue)
{
    std::vector<Vehicle*>::iterator i;

    for( i = vehicles.begin(); i < vehicles.end(); i++){

        if((*i)->id == 5){
            scene->addEllipse((*i)->location->x -5, (*i)->location->y -5, 8, 8, red, QBrush(Qt::red));
        }
        else if((*i)->maxspeed == 1){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y -5, 8, 8, yellow, QBrush(Qt::yellow));
        }
        else if((*i)->maxspeed == 2){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y-5, 8, 8, darkMagenta, QBrush(Qt::darkMagenta));
        }
        else if((*i)->maxspeed == 3){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y-5, 8, 8, blue, QBrush(Qt::blue));
        }
        else if((*i)->maxspeed == 4){
            scene->addEllipse((*i)->location->x-5, (*i)->location->y-5, 8, 8, darkCyan, QBrush(Qt::darkCyan));
        }
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
