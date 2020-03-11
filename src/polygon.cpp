#include "polygon.h"

#include <cmath>
#include "vectormath.h"
#include <iostream>
#include <sstream>
#include <algorithm>

# define M_PI           3.14159265358979323846

void Polygon::updateBound(Vector2 new_point) {
	if (new_point.x < bounds_min.x) {
		bounds_min.x = new_point.x;
	} else if (new_point.x > bounds_max.x) {
		bounds_max.x = new_point.x;
	}
	
	if (new_point.y < bounds_min.y) {
		bounds_min.y = new_point.y;
	} else if (new_point.y > bounds_max.y) {
		bounds_max.y = new_point.y;
	}
}

void Polygon::recalculateBound() {
	bounds_max = (Vector2){0,0};
	bounds_min = (Vector2){0,0};
	for (auto vertex : vertices) {
		updateBound(vertex);
	}
}

void Polygon::recalculateBound(Vector2 removed_point) {	//if we're removing one point, only need to recalculate if the removed point is on a boundary
	if (   removed_point.x <= bounds_min.x || removed_point.y <= bounds_min.y
		|| removed_point.x >= bounds_max.x || removed_point.y >= bounds_max.y) {
		recalculateBound();
	} 
}

void Polygon::recalculateData() {
	Vector2 centre_accumulator = (Vector2){0,0};
	double denominator;
	for (auto vertex : vertices) {
		centre_accumulator = VectorMath::add(centre_accumulator, vertex);
		denominator += 1.0;
	}
	
	centre_pos = VectorMath::scale(centre_accumulator, 1/denominator);
	
	recalculateBound();
}

Polygon::Polygon() {
}

Polygon::Polygon(std::vector<Vector2> vertices, int pointnum) {
	this->vertices = vertices;
	recalculateData();
}

Polygon::Polygon(Vector2 centre, float radius, int pointnum) {
	centre_pos = centre;
	
	bounds_max = (Vector2){0,0};
	bounds_min = (Vector2){0,0};
	for (int i = 0; i < pointnum; i++) {
		double radians = 2*M_PI*i/pointnum;
		Vector2 edge = (Vector2){ float(centre.x + radius*cos(radians)), float(centre.y - radius*sin(radians)) };
		vertices.push_back(edge);
		updateBound(edge);
	}
}

int Polygon::getNearestIndex(Vector2 position) {
	float mindist = -1;
	int savedmin = 0;
	for (auto it = vertices.begin(); it != vertices.end(); ++it) {
		float sqrdist = VectorMath::sqrdist(position, *it);
		if (mindist == -1 || sqrdist < mindist) {
			mindist = sqrdist;
			savedmin = it-vertices.begin();
		}
	}
	return savedmin;
}

int Polygon::getNearestClockwiseIndex(Vector2 position) {
	int nearestindex = getNearestIndex(position);
	if (nearestindex >= getPointNum()) {
		return nearestindex;
	}
	Vector2 nearest = vertices[nearestindex];
	Vector2 nearestd = VectorMath::sub(nearest, centre_pos);
	Vector2 thisd = VectorMath::sub(position, centre_pos);
	
	bool is_clockwise = false;
	if ((nearestd.x > 0  && thisd.x > 0) 
		|| (nearestd.y > 0 && thisd.y > 0) 
		|| (nearestd.y < 0 && thisd.y < 0)) {
		if (atan2(thisd.y, thisd.x) - atan2(nearestd.y, nearestd.x) > 0) {
			is_clockwise = true;
		}
	} else {
		if (atan2(nearestd.y, nearestd.x) - atan2(thisd.y, thisd.x) > 0) {
			is_clockwise = true;
		}
	}
	int nextindex = (nearestindex+1)%(getPointNum()+1);
	
	if (is_clockwise) return nearestindex;
	else return nextindex;
}

Vector2 Polygon::getPointPos(int index) {
	return vertices[index];
}

void Polygon::movePoint(int index, Vector2 newpos) {
	if (vertices.size() > 0) {
		float scalar = 1/vertices.size();
		centre_pos = VectorMath::sub(centre_pos, VectorMath::scale(vertices[index], scalar));
		vertices[index] = newpos;
		centre_pos = VectorMath::add(centre_pos, VectorMath::scale(newpos, scalar));
		updateBound(newpos);
	}
}

void Polygon::addPoint(int index, Vector2 point) {
	if (vertices.size() == 0) {
		centre_pos = point;
		bounds_max = point;
		bounds_min = point;
	} else {
		float newsize = vertices.size()+1;
		float scalar = vertices.size()/newsize;
		centre_pos = VectorMath::add(VectorMath::scale(centre_pos, scalar), VectorMath::scale(point, 1/newsize));
		updateBound(point);
	}
	vertices.insert(vertices.begin()+index, point);
}

void Polygon::removePoint(int index) {
	if (vertices.size() > 0) {
		if (vertices.size() == 1) {
			centre_pos = (Vector2){0,0};
			bounds_max = (Vector2){0,0};
			bounds_min = (Vector2){0,0};
		} else {
			float oldsize = vertices.size();
			float scalar = (oldsize+1)/oldsize;
			centre_pos = VectorMath::scale(VectorMath::sub(centre_pos, VectorMath::scale(vertices[index], 1/oldsize)), scalar);
		}
		Vector2 removed_point = vertices[index];
		vertices.erase(vertices.begin()+index);
		recalculateBound(removed_point);
	}
}

void Polygon::reverse() {
	std::reverse(vertices.begin(), vertices.end());
}

void Polygon::clear() {
	vertices.clear();
}

bool Polygon::containsPoint(Vector2 point) {
	if (point.x < bounds_min.x || point.x > bounds_max.x || 
		point.y < bounds_min.y || point.y > bounds_max.y) {
		return false;
	} else {
		return VectorMath::checkPointInPolygon(point, vertices);
	}
}

float Polygon::findVertexCoverage(Polygon b) {
	std::vector<Vector2> bv = b.getVertices();
	int bn = b.getPointNum();
	float accumulator = 0;
	for (auto b_vertex : bv) {
		if (containsPoint(b_vertex)) accumulator++;
	}
	return accumulator/bn;
}

std::vector<Vector2> Polygon::findOverlapShape(Polygon b) {
	std::vector<Vector2> b_vertices = b.getVertices();
	std::vector<Vector2>::iterator next_it, next_jt;
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		next_it = std::next(it);
		if (next_it == vertices.end()) {
			next_it = vertices.begin();
		}
		
		for (auto jt = b_vertices.begin(); jt != b_vertices.end(); jt++) {
			next_jt = std::next(jt);
			if (next_jt == b_vertices.end()) {
				next_jt = b_vertices.begin();
			}
			
			Vector2 intersection = VectorMath::intersectLines(*it, *next_it, *jt, *next_jt);
			if (intersection.x >= 0 || intersection.y >= 0) {
				//add the intersectino point to the vectorfan of the overlap shape?
			} else {
				//do something else?
			}
		}
	}
	return b_vertices;
}

Vector2* Polygon::getArrayScaled(float screen_scale) {
	Vector2* return_vec = new Vector2[vertices.size()];
	int i = 0;
	for (auto vertex : vertices) {
		return_vec[i] = VectorMath::scale(vertex, screen_scale);
		i++;
	}
	return return_vec;
}

std::string Polygon::printArray() {
		std::stringstream ss;
		for (std::vector<Vector2>::iterator it = vertices.begin(); it != vertices.end(); it++) {
			ss << it->x << "," << it->y << " ";
		}
		ss << std::endl;
		return ss.str();
}
