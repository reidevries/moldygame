#ifndef TEXTURESPRITE_H
#define TEXTURESPRITE_H

#include <raylib.h>
#include <string>
#include "vectormath.h"
#include <memory>
#include <vector>

class TextureSprite {
	private:
		std::string name;
		std::vector<std::shared_ptr<Texture2D>> textures;
		int draw_index;					//the index of the texture that is currently being drawn
		Vector2 pos;
		float scale = 1;
		float rotation = 0;
		
		float screen_scale = 1;
		Vector2 pos_pixels;
		float scale_pixels = 1;
		
		Texture2D getCurrentTexture();
	public:
		TextureSprite(std::string name, std::vector<std::shared_ptr<Texture2D>> textures, Vector2 pos, float screen_scale);

		std::vector<std::shared_ptr<Texture2D>> getAllTextures() {return textures;}
		std::string getName() {return name;}
		
		void setDrawingIndex(int draw_index);
		int getDrawingIndex() {return draw_index;}
		void setPos(Vector2 pos);
		Vector2 getPos() {return pos;}
		void setScale(float scale);
		float getScale() {return scale;}
		void setRotation(float rotation) {this->rotation = rotation;}
		float getRotation() {return rotation;}
		
		void setScreenScale(float screenscale);
		
		void draw(Color color);
		void draw(Vector2 pos);
		void draw();
};

#endif
