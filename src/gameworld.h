#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <raylib.h>
#include <vector>
#include <string>
#include "gameobject.h"
#include "blobobject.h"
#include "levelloader.h"
#include "polygon.h"

class GameWorld {
	private:
		const int WORLD_H = 128;	//world height is fixed to 128 units. world width is scaled depending on aspect ratio
		int screen_w, screen_h;
		float screen_scale;
		float world_w;
		bool debug;
		
		LevelLoader level_loader;
		std::vector<std::unique_ptr<GameObject>> object_buf;
		std::vector<Texture2D> tex_buf;
		std::vector<TextureSprite> ui_buf;
		Font font;
	public:
		GameWorld(int screen_w, int screen_h, bool debug);
		void update(float dt);
		void render(float dt);
		~GameWorld();
};

#endif
