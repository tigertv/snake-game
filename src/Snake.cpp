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
    SnakeBodyPart addHead;
    addHead.direction.x = 0;
    addHead.direction.y = 0;

    switch(this->direction) {
        case Direction::UP:
            addHead.direction.y = -1;
            break;
        case Direction::DOWN:
            addHead.direction.y = 1;
            break;
        case Direction::LEFT:
            addHead.direction.x = -1;
            break;
        case Direction::RIGHT:
            addHead.direction.x = 1;
            break;
    }

    addHead.point.x = bodyParts[0].point.x + addHead.direction.x;
    addHead.point.y = bodyParts[0].point.y + addHead.direction.y;
    
    if ((addHead.direction.x != bodyParts[0].direction.x) && 
        (addHead.direction.y != bodyParts[0].direction.y)) {
        
        bodyParts[0].direction.x -= addHead.direction.x;
        bodyParts[0].direction.y -= addHead.direction.y;
    }
    
    bodyParts.push_front(addHead);

    if (this->isGrowing) {
        this->isGrowing = false;
    } else {
        int x = bodyParts.back().direction.x;
        int y = bodyParts.back().direction.y;
        bodyParts.pop_back();

        // change direction of the tail if it is on a corner
        if ((bodyParts.back().direction.x != 0) && (bodyParts.back().direction.y != 0)) {
            bodyParts.back().direction.x = x - bodyParts.back().direction.x;
            bodyParts.back().direction.y = y - bodyParts.back().direction.y;
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