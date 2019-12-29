#ifndef GAMEOBJECT_H	
#define GAMEOBJECT_H

#include <raylib.h>
#include <vector>
#include "texturesprite.h"

class GameObject {
	protected:
		TextureSprite* spritearray;
		int spritenum;
		Vector2 position;
		int zpos;
		
		float screenscale;
		
	public:
		GameObject(TextureSprite* spritearray, int spritenum, Vector2 position, float screenscale);

		TextureSprite* getSpriteArray() {return spritearray;}
		Texture2D** getAllTextures();
		std::string* getAllNames();
		int getSpriteNum() {return spritenum;}
		Vector2 getPosition() {return position;}
		int getZPos() {return zpos;}
		
		void replaceSpriteArray(TextureSprite* spritearray, int spritenum);
		void setPosition(Vector2 position) {this->position = position;}
		void setZPos(int zpos) {this->zpos = zpos;}
		
		void setScreenScale(float screenscale);
		
		virtual void update(float dt);
		virtual void draw() =0;
};

#endif
