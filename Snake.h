#ifndef SNAKE_H_
#define SNAKE_H_

#include <bits/stdc++.h>

enum Direction {
    LEFT = 1, RIGHT = -1, UP = 2, DOWN = -2
};

class Snake {
private:
    int length = 1;
    Direction direction;
    std::list<std::pair<int,int>> coords;
    void go();
    void go(Direction direction);
    bool isGrowing = false;

public:
    Snake();
    virtual ~Snake();
    void update();
    std::pair<int, int>getHead();
    void grow();
    int getLength();
    std::list<std::pair<int,int>>* getCoordinates();
    void changeDirection(Direction direction);
};

#endif
