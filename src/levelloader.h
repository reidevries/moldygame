#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "level.h"
#include <memory>

class LevelLoader {
	private:
		Level current_level;
	public:
		LevelLoader();
		LevelLoader(int level_num);
		int changeToLevel(int level_num);	//returns the levelnum for success, or -1 for failure
		
		std::unique_ptr<Level> getCurrentLevel() {return std::make_unique<Level>(current_level);}
};

#endif
