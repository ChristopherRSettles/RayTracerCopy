//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_BOX_H
#define RAYTRACERCOPY_BOX_H

#include "Plane.h"
#include "Shape.h"
using namespace std;

class Shape;

class Box : public Shape
{

private:
    vec3 p;
    vec3 du, dv, dw;

public:
    Box(vec3 _p, vec3 d1, vec3 d2, vec3 d3, Color inputcolor);
    Color getColor();
    vec3 Intersection(Ray *);

};
#endif //RAYTRACERCOPY_BOX_H
