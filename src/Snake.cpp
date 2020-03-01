#include "Snake.h"

Snake::Snake() {
    direction = Direction::RIGHT;
    // the head of the snake
    std::pair<int,int> p = {5,5};
    coords.push_front(p);
    this->grow();

    SnakeBodyPart part;
    part.direction.x = 1;
    part.direction.y = 0;
    part.point.x = 5;
    part.point.y = 5;
    bodyParts.push_back(part);


}

Snake::~Snake() {

}

void Snake::go(Direction direction) {
    this->changeDirection(direction);
    this->go();
}

void Snake::go() {
    std::pair<int,int> head = this->getHead();
    int x = head.first;
    int y = head.second;

    SnakeBodyPart addHead;
    addHead.direction.x = 0;
    addHead.direction.y = 0;

    switch(this->direction) {
        case Direction::UP:
            y--;
            addHead.direction.y = -1;
            break;
        case Direction::DOWN:
            y++;
            addHead.direction.y = 1;
            break;
        case Direction::LEFT:
            x--;
            addHead.direction.x = -1;
            break;
        case Direction::RIGHT:
            x++;
            addHead.direction.x = 1;
            break;
    }

    if ((addHead.direction.x != bodyParts[0].direction.x) && 
        (addHead.direction.y != bodyParts[0].direction.y)) {
        
        bodyParts[0].direction.x -= addHead.direction.x;
        bodyParts[0].direction.y -= addHead.direction.y;
    }
    
    head = {x, y};
    coords.push_front(head);
    
    addHead.point.x = x;
    addHead.point.y = y;
    bodyParts.push_front(addHead);

    if (this->isGrowing) {
        this->length++;
        this->isGrowing = false;
    } else {
        coords.pop_back();
        
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

std::pair<int, int> Snake::getHead() {
    return coords.front();
}

void Snake::grow() {
    this->isGrowing = true;
}

int Snake::getLength() {
    return this->length;
}

std::list<std::pair<int,int>>* Snake::getCoordinates() {
    return &(this->coords);
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