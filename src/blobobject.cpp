#include "blobobject.h"
#include <iostream>
#include <vector>
#include <memory>

BlobObject::BlobObject(Polygon polygon, std::vector<TexSprite> sprites, int sprite_num, Vector2 pos, float speed, float screen_scale):GameObject(sprites, sprite_num, pos, screen_scale) {
	next_i = 0;
	this->polygon = polygon;
	this->speed = speed;
	this->colour = BLACK;
}

BlobObject::BlobObject(Polygon polygon, float speed, float screen_scale):GameObject((Vector2){0,0}, screen_scale) {
	next_i = 0;
	this->polygon = polygon;
	this->speed = speed;
	this->colour = BLACK;
}

std::unique_ptr<Level>  BlobObject::findHome(std::unique_ptr<Level> level) {
	std::vector<std::unique_ptr<MoldFood>> areas = level->getAreasOfTypes(Bread, Cheese);
	float maxoverlap = 0;
	for (auto&& area : areas) {
		float overlap = area->getPolygon().findVertexCoverage(this->polygon);
		if (overlap > maxoverlap) {
			maxoverlap = overlap;
			this->homefood = std::move(area);
		}
	}
	if (homefood) DebugPrinter::printDebug("BlobObject::findHome", reinterpret_cast<uintptr_t>(homefood.get()),
			" is the blobobject's new home", 2);
	return std::move(level);
}

std::unique_ptr<Level>  BlobObject::update(std::unique_ptr<Level> level, float dt) {
	if (!homefood) {
		level = findHome(std::move(level));
	} else {
		//expand a vertex away from the centre, until it reaches the edge of its food
		int point_num = polygon.getPointNum();
		if (next_i < 0 || next_i >= point_num) next_i = 0;
		Vector2 vertex_pos = polygon.getPointPos(next_i);
		Vector2 centre_pos = polygon.getCentre();
		Vector2 delta_pos = VectorMath::scale(VectorMath::normalise(VectorMath::sub(vertex_pos, centre_pos)), point_num*speed*dt);
		Vector2 new_pos = VectorMath::add(vertex_pos, delta_pos);

		if (homefood->getPolygon().containsPoint(new_pos)) {
			polygon.movePoint(next_i, new_pos);
		} else {
			std::array<Vector2, 2> nearest_edge = polygon.getNearestEdge(vertex_pos);
			polygon.movePoint(next_i, VectorMath::nearestPointOnSegment(nearest_edge[0], nearest_edge[1], new_pos));
		}

		++next_i;
	}
	return std::move(level);
}

void BlobObject::draw() {
	DrawTriangleFan(polygon.getArrayScaled(screen_scale), polygon.getPointNum(), colour);
	for (auto sprite : sprites) {
		sprite.draw(pos);
	}
}
