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

bool VectorMath::checkPointInPolygon(Vector2 point, std::vector<Vector2> polygon) {
	int counter = 0;
	std::vector<Vector2>::iterator next_it;
	for (auto it = polygon.begin(); it != polygon.end(); it++) {
		next_it = std::next(it);
		if (next_it == polygon.end()) {
			next_it = polygon.begin();
		}
		
		Vector2 j = *it;
		Vector2 i = *next_it;
		
		if (((i.y > point.y) != (j.y > point.y)) &&						//check if the test point y lies between the test vertices on the y axis
			( point.x < (j.x-i.x)*(point.y-i.y)/(j.y-i.y)+i.x)) {		//calculate the x value of the line at y=point.y, and check if the point is less than it
			counter++;
		}
	}
	
	return (counter%2 == 0);
}

Vector2 VectorMath::intersectLines(Vector2 a_1, Vector2 a_2, Vector2 b_1, Vector2 b_2) {
	//starting from here http://cs.swan.ac.uk/~cssimon/line_intersection.html
	//rearranged it a bit so there were less factors, as some factors were negatives of each other
	
	Vector2 aa_d = (Vector2){a_1.x-a_2.x, a_1.y-a_2.y};
	Vector2 ab_d = (Vector2){a_1.x-b_1.x, a_1.y-b_1.y};
	Vector2 bb_d = (Vector2){b_1.x-b_2.x, b_1.y-b_2.y};
	
	float denominator = aa_d.x*bb_d.y - bb_d.x*aa_d.y;
	if (denominator == 0) {//this case means the lines are coincident, so it requires a different tactic to find if they intersect
		//p = a_1 + t*(a_2-a_1)
		//p = a_1-t*aa_d
		//a_1-p = t*aa_d
		//(a_1.x-p.x)/aa_d.x = t
		//(a_1.y-p.y)/aa_d.y = t
		//if 0 <= t < 1 there is an intersection.
		
		float t_x_1 = (a_1.x - b_1.x)/aa_d.x;
		float t_x_2 = (a_1.x - b_2.x)/aa_d.x;
		
		if (t_x_1 >= 0 && t_x_1 < 1) {			//this case means b_1 is on the line segment between a_1 and a_2
			return b_1;
		} else if (t_x_2 >= 0 && t_x_2 < 1) {	//this case means b_2 is on the line segment between a_1 and a_2
			return b_2;
		} else if (t_x_1 < 0 && t_x_2 >= 1) {	//this case means the line segment b_1,b_2 encapsulates the line segment a_1,a_2
			return a_1;
		} else if (t_x_2 < 0 && t_x_1 >= 1) {	//this case means the same thing, but with b's slope being the inverse of a's
			return a_2;
		} else {								//this case means that although the lines are coincident, the line segments do not intersect
			return (Vector2){-1,-1};
		}
	} else {
		float t_a = (bb_d.y*ab_d.x - bb_d.x*ab_d.y)/denominator;
		float t_b = (aa_d.y*ab_d.x - aa_d.x*ab_d.y)/denominator;
		
		if (t_a >= 0 && t_b >= 0 && t_a < 1 && t_b < 1) {
			return VectorMath::add(a_1, VectorMath::scale(aa_d, -t_a));		//=a1+t_a(a2-a1)  (because aa_d = a1-a2 = -(a2-a1)
		} else {
			return (Vector2){-1,-1};
		}
	}
}

Color VectorMath::hsvToRgb(Color hsv) {
	Color rgb = WHITE;
	if (hsv.g == 0){
		rgb.r = hsv.b;
		rgb.g = hsv.b;
		rgb.b = hsv.b;
		rgb.a = hsv.a;
		return rgb;
	}

	unsigned char region = hsv.r / 43;
	unsigned char remainder = (hsv.r - (region * 43)) * 6; 

	unsigned char p = (hsv.b * (255 - hsv.g)) >> 8;
	unsigned char q = (hsv.b * (255 - ((hsv.g * remainder) >> 8))) >> 8;
	unsigned char t = (hsv.b * (255 - ((hsv.g * (255 - remainder)) >> 8))) >> 8;

	switch (region) {
		case 0:
			rgb.r = hsv.b;
			rgb.g = t;
			rgb.b = p;
			break;
		case 1:
			rgb.r = q;
			rgb.g = hsv.b;
			rgb.b = p;
			break;
		case 2:
			rgb.r = p;
			rgb.g = hsv.b;
			rgb.b = t;
            break;
        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = hsv.b;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = hsv.b;
            break;
        default:
            rgb.r = hsv.b;
            rgb.g = p;
            rgb.b = q;
            break;
    }
	
	rgb.a = hsv.a;
	
    return rgb;
}

Color VectorMath::hsvToRgb(unsigned char h, unsigned char s, unsigned char v, unsigned char a) {
	return hsvToRgb((Color){h,s,v,a});
}

float VectorMath::dot(Vector2 a, Vector2 b) {
	return a.x*b.x+a.y*b.y;
}

float VectorMath::dist(Vector2 a, Vector2 b) {
	return std::sqrt( std::pow(b.x-a.x, 2) + std::pow(b.y-a.y, 2) );
}

float VectorMath::sqrdist(Vector2 a, Vector2 b) {
	return std::pow(b.x-a.x,2) + std::pow(b.y-a.y, 2);
}
