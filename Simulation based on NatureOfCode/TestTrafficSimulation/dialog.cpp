#include "dialog.h"
#include "ui_dialog.h"

extern int windowSize;
///////////// Global Variables //////////////////

float c = 0.001;
int numberOfcars = 80;
int carS =5;
//double t=0;

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
    timer->start(3); // run in 1ms

    ///////////// Object Initiations ////////////////

    srand(time(NULL));

    //create cars
    createCars(vehicles, numberOfcars);
    createCars(vehicles1, 70);


    //ps = new ParticleSystem();
    //repeller = new Repeller(50,200);


    p = new Path();

    p->addPoints(-200, -200);
    p->addPoints(200, -200);
    //p->addPoints(0, -200);
    //p->addPoints(200, 0);
    p->addPoints(200, 200);
    p->addPoints(-200, 200);
    //p->addPoints(0, 200);
    p->addPoints(-200, -200);
    //p->addPoints(200, 0);
    //p->addPoints(-200, 0);
    p->addPoints(-200, -200);

    //p->addPoints(200, 200);

    p1 = new Path();

    p1->addPoints(-180, -180);
    p1->addPoints(180, -180);
    p1->addPoints(180, 180);
    p1->addPoints(-180, 180);
    p1->addPoints(-180, -180);
    //p1->addPoints(180, 180);


   /*
   p->addPoints(-200,00);
   p->addPoints(-120,-80);
   p->addPoints(50,0);
   p->addPoints(200,-100);
*/

    //p->addPoints(-200,-200);

    //wind = new Pvector(0.001,0);
    //gravity = new Pvector(0,0.1);
    //friction = new Pvector(0,0);
    //force = new Pvector(0,0);
    //repellForce = new Pvector(0,0);

    //car = new Vehicle(-100, 0, 1 );
    //car1= new Vehicle(-100,80,5);
    //car1->maxspeed=.5;
    //target= new Pvector(-50,-100);
    //target= car1->location;
}



Dialog::~Dialog()
{
    delete ui;
}


void Dialog::theLoop(){

    ///////////// Graphics Settings ////////////////
    scene->clear();
    QPen redPen = QPen(Qt::darkCyan, 3);
    QPen bluePen = QPen(Qt::yellow, 3);
    QPen greenPen = QPen(Qt::lightGray, 20);
    QPen yellowPen = QPen(Qt::darkGray, 3);
    QPen grayPen = QPen(Qt::gray, 20);
    QPen blackPen = QPen(Qt::black, 3);
    QPen magentaPen = QPen(Qt::magenta, 3);
    QPen darkRedPen = QPen(Qt::darkRed, 3);


    /////////////// *Main Code here* /////////////////


    //ps->addParticle();
    //ps->applyForce(gravity);
    //ps->applyRepeller(repeller);
    //ps->run();

    ////////////  Update objects /////////

    for(std::vector<Vehicle*>::iterator i = vehicles.begin(); i < vehicles.end(); i++){

        (*i)->follow(p,1);
        (*i)->separate(vehicles);
        (*i)->update();
        //(*i)->borders(p);
        }

    for(std::vector<Vehicle*>::iterator i = vehicles1.begin(); i < vehicles1.end(); i++){

        (*i)->follow(p1,2);
        (*i)->separate(vehicles1);
        (*i)->update();
        //(*i)->borders(p);
        }

    ////////////////  Draw Objects ////////////////

    // Streets

    drawStreets(p, greenPen);
    drawStreets(p1, grayPen);

    // Vehicles

    drawCars(vehicles, redPen, bluePen, yellowPen);
    drawCars(vehicles1, blackPen, magentaPen, darkRedPen);

    /*
    car->follow(p);
    car->update();
    car->borders(p);

    car1->follow(p);
    car1->update();
    car1->borders(p);
    scene->addEllipse(target->x, target->y,40,40,bluePen);
    */


    ///////////// Counter Settings ////////////////
    /*

    char v=' ';
    QString counter1;
    QString counter2;
    counter1.setNum(double(numberOfcars),v, 1);
    counter2.setNum(t++,v, 1);
    ui->label->setText(counter1);
    ui->label_2->setText(counter2);
*/


}

void Dialog::on_pushButton_clicked()
{
    if(timer->isActive()) timer->stop();
    else timer->start(1);
}

void Dialog::drawStreets(Path* p, QPen pen)
{
    for (int i = 0; i < p->getSize(); i++)
    {
        if(i < p->getSize()-1)
        {
            scene->addLine(p->getPoint(i)->x , p->getPoint(i)->y, p->getPoint(i+1)->x, p->getPoint(i+1)->y, pen );
        }
        else
        {
            scene->addLine(p->getPoint(i)->x , p->getPoint(i)->y, p->getPoint(0)->x, p->getPoint(0)->y, pen );
        }
    }
}

void Dialog::drawCars(std::vector<Vehicle*> vehicles, QPen p1, QPen p2, QPen p3)
{
    for(std::vector<Vehicle*>::iterator i = vehicles.begin(); i < vehicles.end(); i++){

        if((*i)->id == 1){
            scene->addEllipse((*i)->location->x, (*i)->location->y,carS,carS,p1, QBrush(Qt::darkCyan));
        }else if((*i)->id == 2){
            scene->addEllipse((*i)->location->x, (*i)->location->y,carS,carS,p2, QBrush(Qt::yellow));
        }
        else if((*i)->id == 3){
            scene->addEllipse((*i)->location->x, (*i)->location->y,carS,carS, p3, QBrush(Qt::darkGray));
        //scene->addEllipse(repeller->location->x, repeller->location->y,30,30,greenPen);
        }
    }
}

void Dialog::createCars(std::vector<Vehicle*>& vehicles, int n)
{
    for(int m = 0; m < n; m++)
    {
        vehicles.push_back( new Vehicle( rand() % 500-250, rand() % 500-250, rand() % 3 + 1, rand() % 8 + 2 ));
    }
}
