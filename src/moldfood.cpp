#include "moldfood.h"

MoldFood::MoldFood(Polygon polygon, FoodType food_type) {
	this->polygon = polygon;
	this->food = food_type;
}

MoldFood::MoldFood(std::vector<Vector2> polygon, int point_num, FoodType food_type) {
	this->polygon = Polygon(polygon, point_num);
	this->food = food_type;
}

MoldFood::~MoldFood() {
	//nothing to delete
}
