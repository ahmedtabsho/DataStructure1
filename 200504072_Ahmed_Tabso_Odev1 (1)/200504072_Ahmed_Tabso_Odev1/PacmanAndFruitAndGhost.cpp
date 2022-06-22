#include "PacmanAndFruitAndGhost.h"

Fruit::Fruit(int newx = 0, int newy = 0) : x(newx), y(newy) {   }

void Fruit::set(int newx, int newy){ x = newx;  y = newy; }

Pacman::Pacman(int x = 0, int y = 0) : x(x), y(y){  }

bool Pacman::continueGame(){ return ((gameTime > 0) && (life > 0)) ? true : false; }

bool Pacman::istooktendisk(){  return (tookdisk % 10 == 0) ?  true :  false;  }

bool Pacman::EatFruit() { return isEatFruit;  }

void Pacman::buildFruit(){
    if(istooktendisk() && fruitQueue.size()){
        game[fruitQueue.getFront().x][fruitQueue.getFront().y] = 2;
    }
}

void Pacman::pacmanMove(){
    isEatFruit = false;
    helpingMove1();
}

void Pacman::helpingMove1(){
    if(game[x-1][y] > 0){
        moving(x-1,y);
    }
    else if(game[x][y+1] > 0){
        moving(x,y+1);
    }
    else if(game[x+1][y] > 0){
        moving(x+1,y);
    }
    else if(game[x][y - 1] > 0){
        moving(x,y-1);
    }
    else{
        helpingMove2();
    }
}

void Pacman::helpingMove2(){
    if(game[x][y - 1] == -1){
        moving(x,y-1);
    }
    else if(game[x+1][y] == -1){
        moving(x+1,y);
    }
    else if(game[x][y+1] == -1){
        moving(x,y+1);
    }
    else if(game[x-1][y] == -1){
        moving(x-1,y);
    }
    else{
        throw "ERORR....";
    }
}

void Pacman::moving(int newx, int newy){
        if(game[newx][newy] == 1 || game[newx][newy] == -1){
            game[x][y] = -1;
            if(game[newx][newy] == 1){
                tookdisk++; //disks--;
            }
            x = newx;
            y = newy;
            game[newx][newy] = 9;
            gameTime--;
        }
        else if(game[newx][newy] == 2){
            isEatFruit = true;
            Fruit f(newx, newy);
            fruitQueue.enqueue(f);
            game[x][y] = -1;
            x = newx;
            y = newy;
            game[newx][newy] = 9;
            gameTime += 5;
        }
        else if(game[newx][newy] > 2){
            life--;
            game[x][y] = -1;
            x = newx;
            y = newy;
            game[newx][newy] = 9;
            gameTime -= 10;
        }
        else
            throw "Error...." ;
}

Ghost::Ghost(int moveType = 0, int x = 0, int y = 0) : x(x), y(y), moveType(moveType){  }

void Ghost::set(int newmoveType, int newx, int newy) {
    moveType = newmoveType;
    tmpMoveType = newmoveType;
    x = newx;
    y = newy;
}

void Ghost::ghostMove(){
    if(waitTime == 0)
        ghostMove1();
    else{
        game[x][y] = lastValue;
        waitTime--;
    }

}

void Ghost::ghostMove1(){

    if(tmpMoveType == 3)
        moveRightLeft();
    else if(tmpMoveType == 4)
        moveTopDown();
    else if(tmpMoveType == 5)
        moveLeftRight();
    else if(tmpMoveType == 6)
        moveDownTop();
}

void Ghost::moveRightLeft(){
    if(game[x][y + 1] == 0){
        tmpMoveType = 5;
        ghostMove();
    }
    else if(game[x][y + 1] > 0 || game[x][y + 1] == -1){
        if(lastValue < 3)
            game[x][y] = lastValue;
        lastValue = game[x][y + 1];
        game[x][y + 1] = moveType;
        y = y + 1;
    }
}

void Ghost::moveTopDown(){
    if(game[x - 1][y] == 0){
        tmpMoveType = 6;
        ghostMove();
    }
    else if(game[x - 1][y] > 0 || game[x - 1][y] == -1){
        if(lastValue < 3)
            game[x][y] = lastValue;
        lastValue = game[x - 1][y];
        game[x - 1][y] = moveType;
        x = x - 1;
    }
}

void Ghost::moveLeftRight(){
    if(game[x][y - 1] == 0){
        tmpMoveType = 3;
        ghostMove();
    }
    else if(game[x][y - 1] > 0 || game[x][y - 1] == -1){
        if(lastValue < 3)
            game[x][y] = lastValue;
        lastValue = game[x][y - 1];
        game[x][y - 1] = moveType;
        y = y - 1;
    }
}

void Ghost::moveDownTop(){
    if(game[x + 1][y] == 0){
        tmpMoveType = 4;
        ghostMove();
    }
    else if(game[x + 1][y] > 0 || game[x + 1][y] == -1){
        if(lastValue < 3)
            game[x][y] = lastValue;
        lastValue = game[x + 1][y];
        game[x + 1][y] = moveType;
        x = x + 1;
    }
}
