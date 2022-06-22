#ifndef PACMANANDFRUITANDGHOST_H_INCLUDED
#define PACMANANDFRUITANDGHOST_H_INCLUDED

#include "StackAndQueue.cpp"
#include <vector>
#define MAX_ROWS 24
#define MAX_COLUMNS 24
int game[MAX_ROWS][MAX_COLUMNS];
int gameTime = 600;



class Fruit{
public:
    int x;
    int y;
    static Queue<Fruit> q;
    Fruit(int, int);
    void set(int newx, int newy);
};

class Pacman{
public:
    int x;
    int y;
    int tookdisk = 0;
    int life = 3;
    Queue<Fruit> fruitQueue;
    bool isEatFruit = false;
    Pacman(int, int);
    void set(int newx, int newy) {  x = newx;  y = newy; }
    bool continueGame();
    bool istooktendisk();
    bool EatFruit();
    void buildFruit();
    void pacmanMove();
    void helpingMove1();
    void helpingMove2();
    void moving(int newx, int newy);

};

class Ghost{
public:
    int x;
    int y;
    int moveType;
    int tmpMoveType;
    int lastValue = 1;
    int waitTime = 0;
    Ghost(int, int, int);
    void set(int newmoveType, int newx, int newy);
    void ghostMove();
    void ghostMove1();
    void moveRightLeft();
    void moveTopDown();
    void moveLeftRight();
    void moveDownTop();
};




#endif // PACMANANDFRUITANDGHOST_H_INCLUDED
