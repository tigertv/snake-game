#ifndef SNAKE_H_
#define SNAKE_H_

#include <bits/stdc++.h>
#include <deque>

enum Direction {
    LEFT = 1, RIGHT = -1, UP = 2, DOWN = -2
};

struct Point {
    int x;
    int y;
};

struct Vector {
    int x;
    int y;
};

struct SnakeBodyPart {
    Point point;
    Vector direction;
};

class Snake {
private:
    int length = 1;
    Direction direction;
    std::list<std::pair<int,int>> coords;
    std::deque<SnakeBodyPart> bodyParts;
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
    std::deque<SnakeBodyPart>* getBodyParts();
    void changeDirection(Direction direction);
    Direction getDirection();
};

#endif
