#include "gameobject.h"

GameObject::GameObject(TextureSprite* spritearray, int spritenum, Vector2 position, float screenscale) {
	this->spritearray = spritearray;
	this->spritenum = spritenum;
	this->position = position;
	
	setScreenScale(screenscale);
}

Texture2D** GameObject::getAllTextures() {
	Texture2D** alltextures = new Texture2D*[spritenum];
	for (int i = 0; i < spritenum; i++) {
		alltextures[i] = spritearray[i].getAllTextures();
	}
	return alltextures;
}

std::string* GameObject::getAllNames() {
	std::string* allnames = new std::string[spritenum];
	for (int i = 0; i < spritenum; i++) {
		allnames[i] = spritearray[i].getName();
	}
	return allnames;
}

void GameObject::replaceSpriteArray(TextureSprite* spritearray, int spritenum) {
	this->spritearray = spritearray;
	this->spritenum = spritenum;
}

void GameObject::setScreenScale(float screenscale) {
	this->screenscale = screenscale;
	for (int i = 0; i < spritenum; i++) {
		spritearray[i].setScreenScale(screenscale);
	}
}

void GameObject::update(float dt) {
	
}
