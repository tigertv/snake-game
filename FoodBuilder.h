#ifndef FOOD_BUILDER_H_
#define FOOD_BUILDER_H_

#include <bits/stdc++.h>
#include "BorderFrame.h"

struct Food {
	int x;
	int y;
	Food(int x, int y) : x(x), y(y) {}
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
