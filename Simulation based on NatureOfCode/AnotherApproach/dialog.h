#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "drunkdriver.h"
#include "normaldriver.h"
#include "roamingdriver.h"
#include "path.h"
#include "junction.h"



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


///////////// My Declearation //////////////

    std::vector<Vehicle*> vehicles;    // A group of cars

    Path *p;                           // A path (map) contains 9 junctions, each junction contains 8 junctions points


private slots:
    void theLoop();
    void run(std::vector<Vehicle *> &, Path* );
    void addExperiDriver(unsigned long);
    void drawMap(QPen,QPen);
    void drawCars(std::vector<Vehicle*> & , QPen , QPen , QPen , QPen , QPen);
    void drawDest(Path*, QPen, QPen);
    void showJunctions(Path*, QPen, QPen);

    void on_pushButton_clicked();
    void on_verticalSlider_valueChanged(int value);
};

#endif // DIALOG_H
