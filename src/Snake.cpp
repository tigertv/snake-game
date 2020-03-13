#include "Snake.h"

Snake::Snake() {
    direction = Direction::RIGHT;
    // the head of the snake

    SnakeBodyPart part;
    part.direction.x = 1;
    part.direction.y = 0;
    part.point.x = 5;
    part.point.y = 5;
    bodyParts.push_back(part);

    this->grow();
}

Snake::~Snake() {

}

void Snake::go(Direction direction) {
    this->changeDirection(direction);
    this->go();
}

void Snake::go() {
    SnakeBodyPart head;
    head.direction.x = 0;
    head.direction.y = 0;

    switch(this->direction) {
        case Direction::UP:
            head.direction.y = -1;
            break;
        case Direction::DOWN:
            head.direction.y = 1;
            break;
        case Direction::LEFT:
            head.direction.x = -1;
            break;
        case Direction::RIGHT:
            head.direction.x = 1;
            break;
    }

    head.point.x = bodyParts[0].point.x + head.direction.x;
    head.point.y = bodyParts[0].point.y + head.direction.y;
    
    // change direction of the part following the head if
    // the part is in a corner
    if ((head.direction.x != bodyParts[0].direction.x) && 
        (head.direction.y != bodyParts[0].direction.y)) {
        
        bodyParts[0].direction.x -= head.direction.x;
        bodyParts[0].direction.y -= head.direction.y;
    }
    
    bodyParts.push_front(head);

    if (this->isGrowing) {
        this->isGrowing = false;
    } else {
        int x = bodyParts.back().direction.x;
        int y = bodyParts.back().direction.y;
        bodyParts.pop_back();

        // change direction of the tail if it is on a corner
        SnakeBodyPart& part = bodyParts.back();
        if ((part.direction.x != 0) && (part.direction.y != 0)) {
            part.direction.x = x - part.direction.x;
            part.direction.y = y - part.direction.y;
        }
        
    }

}

void Snake::grow() {
    this->isGrowing = true;
}

void Snake::update() {
    this->go();
}

void Snake::changeDirection(Direction direction) {
    // forbid to go in the opposite way
    if (direction == - this->direction) return;

    this->direction = direction;
}

Direction Snake::getDirection() {
    return this->direction;
}

std::deque<SnakeBodyPart>* Snake::getBodyParts() {
    return &bodyParts;
}