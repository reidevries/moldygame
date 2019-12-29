#ifndef TEXTURESPRITE_H
#define TEXTURESPRITE_H

#include <raylib.h>
#include <string>
#include "vectormath.h"

class TextureSprite {
	private:
		std::string name;
		Texture2D* texture;
		int numtex;				//the number of textures in the texture array
		int texindex;			//the index of the texture that is currently being drawn
		Vector2 pos;
		float scale = 1;
		float rotation = 0;
		
		float screenscale = 1;
		Vector2 pixpos;
		float pixscale = 1;
		
	public:
		TextureSprite(std::string name, Texture2D* texture, int numtex, Vector2 pos, float screenscale);
		
		Texture2D getCurrentTexture();
		Texture2D* getAllTextures() {return texture;}
		std::string getName() {return name;}
		
		void setTexIndex(int texindex);
		int getTexIndex() {return texindex;}
		void setPos(Vector2 pos);
		Vector2 getPos() {return pos;}
		void setScale(float scale);
		float getScale() {return scale;}
		void setRotation(float rotation) {this->rotation = rotation;}
		float getRotation() {return rotation;}
		
		void setScreenScale(float screenscale);
		
		void draw(Color color);
		void draw(Vector2 position);
		void draw();
		
		~TextureSprite();
};

#endif
