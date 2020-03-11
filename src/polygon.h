#ifndef VECTORFAN_H
#define VECTORFAN_H

#include <raylib.h>
#include <vector>
#include <string>

class VectorFan {
	private:
		std::vector<Vector2> fanpoints;
		Vector2 centrepos;
	public:
		VectorFan();
		VectorFan(Vector2* points, int pointnum);
		VectorFan(Vector2 centre, float radius, int pointnum);	//this creates a circle with a resolution of pointnum
		
		Vector2* getArray() {return fanpoints.data();}
		int getPointNum() {return fanpoints.size();}
		Vector2 getCentre() {return centrepos;}					//gets the "centre"
		int getIndexOfPoint(Vector2 position);					//gets the index of the point closest to the given position
		
		Vector2 getPointPos(int index);							//gets the position of the point at index
		void movePoint(int index, Vector2 newpos);				//moves a point to newpos, and updates the centrepos
		void addPoint(int index, Vector2 newpoint);				//adds a point, and updates the centrepos
		void removePoint(int index);							//removes a poin, and updates the centrepos
		
		float findOverlapAmount(VectorFan b) {return 1;}				//figures out if this VectorFan overlaps with the given VectorFan
		std::vector<Vector2> findOverlapShape(VectorFan b) {return fanpoints;}//finds the shape of the overlap between this vectorfan and the given one
};

#endif
