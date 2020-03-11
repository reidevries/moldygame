#include "blobobject.h"
#include <iostream>
#include <vector>
#include <memory>

BlobObject::BlobObject(Polygon polygon, std::vector<TextureSprite> sprites, int sprite_num, Vector2 pos, float speed, float screen_scale):GameObject(sprites, sprite_num, pos, screen_scale) {
	next_i = 0;
	this->polygon = polygon;
	this->speed = speed;
	this->colour = BLACK;
}

BlobObject::BlobObject(Polygon polygon, int speed, float screen_scale):GameObject((Vector2){0,0}, screen_scale) {
	next_i = 0;
	this->polygon = polygon;
	this->speed = speed;
	this->colour = BLACK;
}

std::unique_ptr<Level>  BlobObject::findHome(std::unique_ptr<Level> level) {
	std::vector<std::unique_ptr<MoldFood>> areas = level->getAreasOfTypes(Bread, Cheese);
	float maxoverlap = 0;
	for (auto&& area : areas) {
		float overlap = area->getVectorFan().findVertexCoverage(this->polygon);
		if (overlap > maxoverlap) {
			maxoverlap = overlap;
			this->homefood = std::move(area);
		}
	}
	return std::move(level);
}

std::unique_ptr<Level>  BlobObject::update(std::unique_ptr<Level> level, float dt) {
	if (this->homefood == nullptr) {
		level = findHome(std::move(level));
	}
	
	//expand a vertex away from the centre, until it reaches the edge of its food
	int point_num = polygon.getPointNum();
	if (next_i < 0 || next_i >= point_num) next_i = 0;
	Vector2 vertex_pos = polygon.getPointPos(next_i);
	Vector2 centre_pos = polygon.getCentre();
	//the below 4 is a magic number, should be based on amount of food or maybe global game speed variable
	vertex_pos = VectorMath::add(vertex_pos, VectorMath::scale(VectorMath::sub(vertex_pos, centre_pos), (speed*dt)/(4*point_num)));
	polygon.movePoint(next_i, vertex_pos);
	if (!homefood->getVectorFan().containsPoint(vertex_pos)) {
		//find the nearest point on the outside of the polygon?
	}

	return std::move(level);
}

void BlobObject::draw() {
	DrawTriangleFan(polygon.getArrayScaled(screen_scale), polygon.getPointNum(), colour);
	for (auto sprite : sprites) {
		sprite.draw(pos);
	}
}
