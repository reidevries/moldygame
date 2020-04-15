#ifndef BLOBOBJECT_H
#define BLOBOBJECT_H

#include <raylib.h>
#include <vector>
#include <string>
#include "gameobject.h"
#include "polygon.h"
#include <memory>
#include "texsprite.h"

class BlobObject: public GameObject {
	private:
		Polygon polygon;		//array of 2D points representing the outside of the blob
		Color colour;			//colour of the triangle fan
		float speed;			//speed of movement
		int next_i;				//used for updating each vertex over multiple update frames	
		std::unique_ptr<MoldFood> homefood = nullptr;		//address of the vectorfan that this mold is home to
	public:
		BlobObject(Polygon polygon, std::vector<TexSprite> sprite_arr, int sprite_num, Vector2 pos, float speed, float screen_scale);
		BlobObject(Polygon polygon, float speed, float screen_scale);
		
		void setScreenScale(float screen_scale);

		std::unique_ptr<Level> findHome(std::unique_ptr<Level> level);
		
		std::unique_ptr<Level> update(std::unique_ptr<Level>, float dt);
		void draw();
};

#endif
