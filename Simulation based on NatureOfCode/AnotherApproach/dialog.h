#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "vehicle.h"
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
    void drawMap(QPen,QPen);
    void drawCars(std::vector<Vehicle*> & , QPen , QPen , QPen , QPen , QPen);
    void showJunctions(Path*, QPen, QPen);

    void on_pushButton_clicked();
};

#endif // DIALOG_H
