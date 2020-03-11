#ifndef GAMEOBJECT_H	
#define GAMEOBJECT_H

#include <raylib.h>
#include <vector>
#include "texturesprite.h"
#include "level.h"
#include <memory>

class GameObject {
	protected:
		std::vector<TextureSprite> sprites;
		int sprite_num;
		Vector2 pos;
		int z_pos;
		
		float screen_scale;
		
	public:
		GameObject(std::vector<TextureSprite> sprites, int sprite_num, Vector2 pos, float screen_scale);
		GameObject(Vector2 pos, float screen_scale);
		int getSpriteNum() {return sprite_num;}
		Vector2 getPosition() {return pos;}
		int getZPos() {return z_pos;}
		
		void replaceSprites(std::vector<TextureSprite> sprites, int sprite_num);
		void setPos(Vector2 pos) {this->pos = pos;}
		void setZPos(int zpos) {this->z_pos = zpos;}
		
		void setScreenScale(float screen_scale);
		
		virtual std::unique_ptr<Level> update(std::unique_ptr<Level> level, float dt);
		virtual void draw() =0;
		virtual ~GameObject() {sprites.clear();}
};

#endif
