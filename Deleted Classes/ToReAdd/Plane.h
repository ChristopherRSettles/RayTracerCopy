//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_PLANE_H
#define RAYTRACERCOPY_PLANE_H

//Christopher Settles
#include "Shape.h"
#include "../Control/Ray.h"
#include "../Control/Color.h"

using namespace std;

class Shape;

class Plane : public Shape
{

private:
    vec3 p;
    vec3 du, dv;

public:
    Plane(vec3 _p, vec3 d1, vec3 d2, Color inputcolor);
    Color getColor();
    vec3 Intersection(Ray *);

};

#endif //RAYTRACERCOPY_PLANE_H
