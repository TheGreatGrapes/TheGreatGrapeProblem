#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
//#include "particlesystem.h"
#include "vehicle.h"
#include "path.h"



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
/////////// System Declearation //////////////
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;

/////////// My Declearation //////////////

    std::vector<Vehicle*> vehicles;
    std::vector<Vehicle*> vehicles1;
    //Particle *p1;
    //Pvector *l;
    //Pvector *v;

    //Pvector *wind;
    //Pvector *gravity;
    //Repeller *repeller;
    //Pvector *friction;
    //Pvector *force;
    //Pvector *repellForce;

    //ParticleSystem *ps;
    //Vehicle *car,*car1;
    //Pvector *target;
    Path *p;
    Path *p1;


private slots:
    void theLoop();
    void on_pushButton_clicked();
    void drawStreets(Path*, QPen);

    void createCars(std::vector<Vehicle*>&, int);
    void drawCars(std::vector<Vehicle*>, QPen, QPen, QPen);


};

#endif // DIALOG_H
