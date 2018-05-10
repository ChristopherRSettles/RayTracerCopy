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

    vec3 minp, maxp;
//    vec3 du, dv, dw;
//    Plane planes[6];

public:
//    Box();
    Box(vec3 p1, vec3 p2);

    Box(vec3 p1, vec3 p2, vec3 color);

//    Box(vec3 _p, vec3 d1, vec3 d2, vec3 d3, vec3 inputcolor);
    vec3 getColor() override;
    float Intersection(Ray *) override;

    Ray getReflectionRay(Ray *incomingRay) override;

    vec3 getNormal(Ray *incomingRay) override;

    vec3 middle() override;

    vec3 minBoundary() override;

    vec3 maxBoundary() override;


    bool intersect(Ray &r);
};
#endif //RAYTRACERCOPY_BOX_H
