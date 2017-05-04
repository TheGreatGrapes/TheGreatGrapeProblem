#ifndef CAR_H
#define CAR_H

class Car {
public:
    Car(int x);
    ~Car();

    void moveForward(int step);
    void moveBackward(int step);
    void printPos(int map[]);
    int returnPos();

private:
    int positionX;
};

#endif // CAR_H
