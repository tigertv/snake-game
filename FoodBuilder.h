#ifndef FOOD_BUILDER_H_
#define FOOD_BUILDER_H_

#include <bits/stdc++.h>
#include "BorderFrame.h"

struct Food {
    int x;
    int y;
    int value;
    Food(int x, int y, int value) : x(x), y(y), value(value) {}
};

class FoodBuilder{
private:
    Food* food = nullptr;
    BorderFrame* border;
    
public:
    FoodBuilder(BorderFrame* border);
    virtual ~FoodBuilder();
    Food* getFood();
};

#endif
