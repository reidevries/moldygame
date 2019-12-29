#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <cmath>
#include <raylib.h>

class VectorMath {
	public:
		static Vector2 add(Vector2 a, Vector2 b);
		static Vector2 sub(Vector2 a, Vector2 b);
		static Vector2 scale(Vector2 a, float b);
		static Vector2 scale(Vector2 a, Vector2 b);
		static float dot(Vector2 a, Vector2 b);
		static float dist(Vector2 a, Vector2 b);
};

#endif
