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

/////////// Commented Declearation ///////////

    //std::vector<Particle*> particles;
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
    //Pvector *target;
///////////// My Declearation //////////////

    Vehicle *c;

    Path *p;

    std::vector<Path*> paths;


private slots:
    void theLoop();
    void on_pushButton_clicked();
};

#endif // DIALOG_H
