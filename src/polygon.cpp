#include <cmath>
#include "vectorfan.h"
#include "vectormath.h"

# define M_PI           3.14159265358979323846

VectorFan::VectorFan() {
}

VectorFan::VectorFan(Vector2* points, int pointnum) {
  fanpoints.assign(points, points + pointnum);
}

VectorFan::VectorFan(Vector2 centre, float radius, int pointnum) {
  for (int i = 0; i < pointnum; i++) {
    double radians = 2*M_PI*i/pointnum;
    Vector2 edge = (Vector2){ float(centre.x + radius*cos(radians)), float(centre.y - radius*sin(radians)) };
    fanpoints.push_back(edge);
  }
}

Vector2 VectorFan::getPointPos(int index) {
  return fanpoints[index];
}

void VectorFan::movePoint(int index, Vector2 newpos) {
  float scalar = 1/fanpoints.size();
  centrepos = VectorMath::sub(centrepos, VectorMath::scale(fanpoints[index], scalar));
  fanpoints[index] = newpos;
  centrepos = VectorMath::add(centrepos, VectorMath::scale(newpos, scalar));
}

void VectorFan::addPoint(int index, Vector2 point) {
  float newsize = fanpoints.size()+1;
  float scalar = fanpoints.size()/newsize;
  centrepos = VectorMath::add(VectorMath::scale(centrepos, scalar), VectorMath::scale(point, 1/newsize));
  fanpoints.insert(fanpoints.begin()+index, point);
}

void VectorFan::removePoint(int index) {
  float oldsize = fanpoints.size();
  float scalar = (oldsize+1)/oldsize;
  centrepos = VectorMath::scale(VectorMath::sub(centrepos, VectorMath::scale(fanpoints[index], 1/oldsize)), scalar);
  fanpoints.erase(fanpoints.begin()+index);
}
