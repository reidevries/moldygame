#include "levelloader.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

LevelLoader::LevelLoader() {
}

LevelLoader::LevelLoader(int level_num) {
	changeToLevel(level_num);
}

int LevelLoader::changeToLevel(int level_num) {
	current_level = Level(level_num);
	if (level_num < 0) {
		return level_num;
	}
	
	std::stringstream ss;
	ss << "levels/" << level_num << ".coords";
	std::ifstream infile;
	infile.open(ss.str(), std::ifstream::in);
	
	std::cout << "Loading level " << level_num << "..." << std::endl;
	
	if (infile.is_open()) {
		current_level.clearFood();
		char c;
		int currentline;
		int currentcoord;
		Vector2 currentvec = (Vector2){0,0};
		std::stringstream currentfoodtype;
		bool startedline = false;
		bool currentlyx = true;
		bool endedline = false;
		Polygon currentv;
		
		while ((c=infile.get()) != EOF) {
			
			if (!startedline) {
				if (c == ' ') startedline = true;
				else currentfoodtype << c;
			} else if (!endedline) {
				if (isdigit(c)) {
					if (currentlyx) currentvec.x = currentvec.x*10 + int(c) - int('0');
					else currentvec.y = currentvec.y*10 + int(c) - int('0');
				} else {
					if (currentlyx && c == ',') currentlyx = false;
					else if (!currentlyx && (c == ' ' || c == ';')) {
						currentv.addPoint(currentv.getNearestClockwiseIndex(currentvec), currentvec);
						currentvec = (Vector2){0,0};
						currentlyx = true;
						currentcoord++;
						if (c == ';') {
							endedline = true;
						}
					}
				}
			} else {
				if (c == '\n') {
					startedline = false;
					currentlyx = true;
					endedline = false;
					currentcoord = 0;
					if (currentfoodtype.str().compare("Bread") == 0) {
						current_level.addFood(currentv, Bread);
						std::cout << "\tcreated a bread:";
					} else if (currentfoodtype.str().compare("Cheese") == 0) {
						current_level.addFood(currentv, Cheese);
						std::cout << "\tcreated a cheese:";
					}
					std::cout << "\tcentrepos=" << currentv.getCentre().x << "," << currentv.getCentre().y << "\t" << currentv.printArray();
					currentvec = (Vector2){0,0};
					currentfoodtype.str("");
					currentv.clear();
					currentline++;
				}
			}
		}
		infile.close();
		return level_num;
	}
	return -1;
}
