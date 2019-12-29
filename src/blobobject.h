#ifndef BLOBOBJECT_H
#define BLOBOBJECT_H

#include <raylib.h>
#include <vector>
#include <string>
#include "vectorfan.h"
#include "gameobject.h"
#include "texturesprite.h"

class BlobObject: public GameObject {
	private:
		VectorFan vectorfan;	//array of 2D points representing the outside of the blob
		Color colour;			//colour of the triangle fan
		int speed;				//speed of movement
		
	public:
		BlobObject(VectorFan vectorfan, TextureSprite* spritearray, int spritenum, Vector2 position, float speed, float screenscale);
		BlobObject(VectorFan vectorfan, int speed, float screenscale);
		
		void setScreenScale(float screenscale);

		void update(VectorFan** fillable, float dt);
		void draw();
};

#endif
