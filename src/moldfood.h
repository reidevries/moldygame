#ifndef MOLDFOOD_H
#define MOLDFOOD_H

#include "polygon.h"
#include <memory>

enum FoodType {Bread=0, Cheese=1};										//these are ordered with more similar foods (by nutrition/source) grouped together

enum Contents {Protein=1, Fibre=2, Iron=4, Cellulose=8, 				//unimplemented so far, in future could be used as a more fine-grained way of defining
				Fat=16, Salt=32, Sugar=64, Carbohydrate=128, Water=256};//what kind of foods a mold can eat
				
class MoldFood {
	private:
		Polygon polygon;
		FoodType food;
	public:
		MoldFood(Polygon polygon, FoodType food);
		MoldFood(std::vector<Vector2> polygon, int pointnum, FoodType food);
		Polygon getPolygon() {return polygon;}
		FoodType getFoodType() {return food;}
		~MoldFood();
};

#endif
