#include "dialog.h"
#include "ui_dialog.h"


///////////// Global Variables //////////////////

extern int windowSize;

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

    ///////////// Commented Initiations ////////////////
    //for(int i = 0; i < numberOfcars; i++){
    //    particles.push_back( new Particle( rand() % 500-250, rand() % 500-250));
    //}
    //repeller = new Repeller(50,200);
    //ps = new ParticleSystem();
    //wind = new Pvector(0.001,0);
    //gravity = new Pvector(0,0.1);
    //friction = new Pvector(0,0);
    //force = new Pvector(0,0);
    //repellForce = new Pvector(0,0);
    //target= new Pvector(-50,-200);

    ///////////// Object Initiations ////////////////

    srand(time(NULL));

    p = new Path();
    c = new Vehicle();
}



Dialog::~Dialog()
{
    delete ui;
}


void Dialog::theLoop(){

    ///////////// Graphics Settings ////////////////
    scene->clear();
    QPen redPen = QPen(Qt::red, 3);
    QPen bluePen = QPen(Qt::blue, 3);
    QPen greenPen = QPen(Qt::green, 3);
    QPen blackPen = QPen(Qt::black, 3);
    QPen yellowPen = QPen(Qt::yellow, 3);


    /////////////// Main Code here /////////////////


    for(unsigned long i = 0; i < c->cars.size(); i ++){

        c->cars[i]->chooseJunction(p);
        c->cars[i]->arrive();
        c->cars[i]->stopAtJunction();
        c->cars[i]->update();
    }

    ////////////////  Draw Objects ////////////////

    scene->addEllipse(c->cars[0]->location->x, c->cars[0]->location->y,10,10,redPen);
    scene->addEllipse(c->cars[1]->location->x, c->cars[1]->location->y,10,10,bluePen);
    scene->addEllipse(c->cars[2]->location->x, c->cars[2]->location->y,10,10,yellowPen);
    scene->addEllipse(c->cars[3]->location->x, c->cars[3]->location->y,10,10,blackPen);
    scene->addEllipse(c->cars[4]->location->x, c->cars[4]->location->y,10,10,greenPen);


    ////////////////  Draw Streets ////////////////
    scene->addLine(-200,-200,-200, 200, bluePen);
    scene->addLine(-200, 200, 200, 200, bluePen);
    scene->addLine( 200, 200, 200,-200, bluePen);
    scene->addLine( 200,-200,-200,-200, bluePen);
    scene->addLine(-200,   0, 200,   0, bluePen);
    scene->addLine(   0,-200,   0, 200, bluePen);

    ///////////// Counter Settings ////////////////

    char v=' ';
    QString counter1;
    QString counter2;
    counter1.setNum(c->cars[0]->location->x,v, 1);
    counter2.setNum(c->cars[0]->location->y,v, 1);
    ui->label->setText(counter1);
    ui->label_2->setText(counter2);

    ///////////// Commented Area  /////////////////
    /*
        ps->addParticle();
        ps->applyForce(gravity);
        ps->applyRepeller(repeller);
        ps->run();

        std::vector<Particle*>::iterator i;


        for(i = ps->particles.begin(); i < ps->particles.end(); i++){

            if((*i)->id == 1){
                scene->addEllipse((*i)->location->x, (*i)->location->y,10,10,redPen);
            }else if((*i)->id == 2){
                scene->addEllipse((*i)->location->x, (*i)->location->y,10,10,bluePen);
            }
            scene->addEllipse(repeller->location->x, repeller->location->y,30,30,greenPen);
        }

    */
    // scene->addEllipse(target->x, target->y,40,40,bluePen);
    //target->x+=0.9;
    //target->y+=0.7;
}


void Dialog::on_pushButton_clicked()
{
    if(timer->isActive()) timer->stop();
    else timer->start(1);
}
