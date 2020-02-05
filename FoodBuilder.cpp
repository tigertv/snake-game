#include "FoodBuilder.h"

FoodBuilder::FoodBuilder(BorderFrame* border) {
    this->border = border;
}

Food* FoodBuilder::getFood() {
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int x = border->x + std::rand() % border->width;
    int y = border->y + std::rand() % border->height;
    if (x == border->x) x++;
    if (y == border->y) y++;

    if (this->food == nullptr) {
        this->food = new Food(x, y, 10);
    } else {
        this->food->x = x;
        this->food->y = y;
    }
    
    return this->food;
}

FoodBuilder::~FoodBuilder() {
    if (this->food != nullptr) {
        delete this->food;
    }
}
