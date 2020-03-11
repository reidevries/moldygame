#ifndef LEVEL_H
#define LEVEL_H

#include "moldfood.h"
#include <vector>
#include <memory>

class Level {
	private:
		int level_id = -1;
		std::vector<MoldFood> food;
		int food_num = 0;
	public:
		Level();
		Level(int levelnum);
		
		std::vector<std::unique_ptr<MoldFood>> getAreasOfTypes(FoodType a_end, FoodType b_end);	//gets a range of food types, inclusive of the ends of the range that were given
		std::vector<std::unique_ptr<MoldFood>> getAreasOfType(FoodType type);
		
		void addFood(Polygon v, FoodType f);
		void clearFood();
		
		void debugRenderFood(float screenscale);
		
		~Level();
};

#endif
