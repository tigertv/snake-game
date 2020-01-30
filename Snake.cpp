#include "Snake.h"

Snake::Snake() {
	direction = Direction::RIGHT;
	// the beginning point of the snake
	//auto p = std::make_pair(5,5);
	std::pair<int,int> p = {5,5};
	coords.push_front(p);
}

Snake::~Snake() {

}

void Snake::go(Direction direction) {
	this->direction = direction;
	this->go();
}

void Snake::go() {
	std::pair<int,int> head = this->getHead();
	int x = head.first;
	int y = head.second;

	switch(this->direction) {
		case Direction::UP:
			y--;
			break;
		case Direction::DOWN:
			y++;
			break;
		case Direction::LEFT:
			x--;
			break;
		case Direction::RIGHT:
			x++;
			break;
	}
	//head = std::make_pair(x, y);
	head = {x, y};
	coords.push_front(head);

	if (this->isGrowing) {
		this->length++;
		this->isGrowing = false;
	} else {
		coords.pop_back();
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