#include "blobobject.h"
#include <iostream>

BlobObject::BlobObject(VectorFan vectorfan, TextureSprite* spritearray, int spritenum, Vector2 position, float speed, float screenscale):GameObject(spritearray, spritenum, position, screenscale) {
	this->vectorfan = vectorfan;
	this->speed = speed;
	this->colour = BLACK;
}

BlobObject::BlobObject(VectorFan vectorfan, int speed, float screenscale):GameObject(nullptr, 0, (Vector2){0,0}, screenscale) {
	this->vectorfan = vectorfan;
	this->speed = speed;
	this->colour = BLACK;
}

void BlobObject::update(VectorFan** fillable, float dt) {
	
}

void BlobObject::draw() {
	int pnum = vectorfan.getPointNum();
	Vector2* v = new Vector2[pnum];
	for (int i = 0; i < vectorfan.getPointNum(); i++) {
		v[i] = VectorMath::scale(vectorfan.getPointPos(i), screenscale);
	}
	DrawTriangleFan(v, vectorfan.getPointNum(), colour);
	delete v;
	for (int i = 0; i < spritenum; i++) {
		spritearray[i].draw(position);
	}
}
