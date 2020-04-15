#include "texturesprite.h"
#include <iostream>

TextureSprite::TextureSprite(std::string name, std::vector<std::shared_ptr<Texture2D>> textures, Vector2 pos, float screenscale) {
	this->name = name;
	this->textures = textures;
	this->pos = pos;
	draw_index = 0;
	
	setScreenScale(screenscale);
}

void TextureSprite::setDrawingIndex(int texindex) {
	if (texindex < textures.size() && texindex >= 0) this->draw_index = texindex;
	else std::cerr << "Tried to set TextureSprite '" << name << "' to invalid texindex " << texindex << std::endl;
}

void TextureSprite::setPos(Vector2 pos) {
	this->pos = pos;
	pos_pixels = VectorMath::scale(pos, screen_scale);
}

void TextureSprite::setScale(float scale) {
	this->scale = scale;
	this->scale_pixels = scale*screen_scale;
}

void TextureSprite::setScreenScale(float screenscale) {
	this->screen_scale = screenscale;
	pos_pixels = VectorMath::scale(pos, screenscale);
	scale_pixels = scale*screenscale;
}

Texture2D TextureSprite::getCurrentTexture() {
	return *textures[draw_index];
}

void TextureSprite::draw(Color color) {
	DrawTextureEx(getCurrentTexture(), pos_pixels, rotation, scale_pixels, color);
}

void TextureSprite::draw(Vector2 pos) {
	DrawTextureEx(getCurrentTexture(), VectorMath::add(pos_pixels, VectorMath::scale(pos, screen_scale)), 0, scale_pixels, WHITE);
}

void TextureSprite::draw() {
	draw(WHITE);
}
