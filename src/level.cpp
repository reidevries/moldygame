#include "level.h"
#include "vectormath.h"

Level::Level() {
}

Level::Level(int level_num) {
	this->level_id = level_num;
}

void Level::addFood(Polygon v, FoodType f) {
	food.emplace_back(v, f);
	food_num++;
}

void Level::clearFood() {
	if (food_num > 0) {
		food.clear();
		food_num = 0;
	}
}

std::vector<std::unique_ptr<MoldFood>> Level::getAreasOfTypes(FoodType a_end, FoodType b_end) {
	FoodType max = (a_end>b_end)?a_end:b_end;
	FoodType min = (a_end<b_end)?a_end:b_end;
	
	std::vector<std::unique_ptr<MoldFood>> areas;
	for (auto it = food.begin(); it != food.end(); it++) {
		if (it->getFoodType() >= min && it->getFoodType() <= max) {
			areas.push_back(std::make_unique<MoldFood>(*it));
		}
	}
	return areas;
}

std::vector<std::unique_ptr<MoldFood>> Level::getAreasOfType(FoodType type) {
	return getAreasOfTypes(type,type);
}

void Level::debugRenderFood(float screenscale) { //call between BeginDrawing() and EndDrawing()
	for (int i = 0; i < food_num; i++) {
		unsigned char hue = 255*i/food_num;
		Color c = VectorMath::hsvToRgb(hue, 222, 222, 128);
		int pnum = food[i].getPolygon().getPointNum();
		Vector2* v = food[i].getPolygon().getArrayScaled(screenscale);
		DrawTriangleFan(v, pnum, c);
	}
}

Level::~Level() {
	food.clear();
}
