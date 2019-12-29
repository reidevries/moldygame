#include "vectormath.h"
#include <cmath>

Vector2 VectorMath::add(Vector2 a, Vector2 b) {
	return (Vector2){a.x+b.x, a.y+b.y};
}

Vector2 VectorMath::sub(Vector2 a, Vector2 b) {
	return (Vector2){a.x-b.x, a.y-b.y};
}

Vector2 VectorMath::scale(Vector2 a, Vector2 b) {
	return (Vector2){a.x*b.x, a.y*b.y};
}

Vector2 VectorMath::scale(Vector2 a, float b) {
	return (Vector2){a.x*b, a.y*b};
}

float VectorMath::dot(Vector2 a, Vector2 b) {
	return a.x*b.x+a.y*b.y;
}

float VectorMath::dist(Vector2 a, Vector2 b) {
	return std::sqrt( std::pow(b.x-a.x, 2) + std::pow(b.y-a.y, 2) );
}
