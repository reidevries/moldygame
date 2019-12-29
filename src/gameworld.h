#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <raylib.h>
#include <vector>
#include <string>
#include "gameobject.h"
#include "blobobject.h"
#include "vectorfan.h"

class GameWorld {
	private:
		const int WORLDHEIGHT = 128;	//world height is fixed to 128 units. world width is scaled depending on aspect ratio
		int screenwidth, screenheight;
		float screenscale;
		float worldwidth;
		
		std::vector<GameObject*> gameobjectbuffer;
		std::vector<Texture2D> texturebuffer;
		std::vector<TextureSprite> uitexturebuffer;
		Font font;
	public:
		GameWorld(int screenwidth, int screenheight);
		void render();
		~GameWorld();
};

#endif
