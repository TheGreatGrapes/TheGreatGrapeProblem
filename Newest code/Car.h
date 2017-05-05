#ifndef CAR_H
#define CAR_H

class Car {


public:
    Car();
    Car(int, int);
    ~Car();

    //////////// Members ////////////
    int indexX;
    int indexY;


    ////////// Position Info //////////
    int getIndexX();
    int getIndexY();
    
    
    ////////// Member functions ///////
    int check(int, int);

    
    /////////// Please Ignore //////////
    // void forwardSpeed(int, int);
    // void backwardSpeed(int, int);
    //int printPosX(int mapX[]);
    //int printPosY(int mapY[]);


    // For Map class to be able to access index in Car class
    friend class Map;
};

#endif // CAR_H
