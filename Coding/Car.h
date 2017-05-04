#ifndef CAR_H
#define CAR_H

class Car {
private:
    int indexX;
    int indexY;   

public:


    Car();
    ~Car();
    //// Motion ////
    //void forwardSpeed(int);
    //void backwardSpeed(int, int);

    //// Position Info ////
    int getIndexX();
    int getIndexY();
    int printPosX(int mapX[]);
    int printPosY(int mapY[]);
    
    friend class Map;
};

#endif // CAR_H
