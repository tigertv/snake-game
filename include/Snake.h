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
    Direction direction;
    std::deque<SnakeBodyPart> bodyParts;
    void go();
    void go(Direction direction);
    bool isGrowing = false;

public:
    Snake();
    virtual ~Snake();
    void update();
    void grow();
    int getLength();
    std::deque<SnakeBodyPart>* getBodyParts();
    void changeDirection(Direction direction);
    Direction getDirection();
};

#endif
