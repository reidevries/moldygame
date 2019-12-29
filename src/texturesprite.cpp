#include "texturesprite.h"
#include <iostream>

TextureSprite::TextureSprite(std::string name, Texture2D* texture, int numtex, Vector2 pos, float screenscale) {
	this->name = name;
	this->texture = texture;
	this->numtex = numtex;
	this->pos = pos;
	texindex = 0;
	
	setScreenScale(screenscale);
}

void TextureSprite::setTexIndex(int texindex) {
	if (texindex < numtex && texindex >= 0) this->texindex = texindex;
	else std::cerr << "Tried to set TextureSprite '" << name << "' to invalid texindex " << texindex << std::endl;
}

Texture2D TextureSprite::getCurrentTexture() {
	return texture[texindex];
}

void TextureSprite::setPos(Vector2 pos) {
	this->pos = pos;
	pixpos = VectorMath::scale(pos, screenscale);
}

void TextureSprite::setScale(float scale) {
	this->scale = scale;
	this->pixscale = scale*screenscale;
}

void TextureSprite::setScreenScale(float screenscale) {
	this->screenscale = screenscale;
	pixpos = VectorMath::scale(pos, screenscale);
	pixscale = scale*screenscale;
}

void TextureSprite::draw(Color color) {
	DrawTextureEx(getCurrentTexture(), pixpos, rotation, pixscale, color);
}

void TextureSprite::draw(Vector2 position) {
	DrawTextureEx(getCurrentTexture(), VectorMath::add(pixpos, VectorMath::scale(position, screenscale)), 0, pixscale, WHITE);
}

void TextureSprite::draw() {
	draw(WHITE);
}

TextureSprite::~TextureSprite() {
	//maybe should do this externally so that the memory can be freed at the same time
	for (int i = 0; i < numtex; i++) {
		UnloadTexture(texture[i]);
	}
}
