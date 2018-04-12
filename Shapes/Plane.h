//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_PLANE_H
#define RAYTRACERCOPY_PLANE_H

//Christopher Settles
#include "Shape.h"
#include "../Control/Ray.h"
#include "../Control/Color.h"

class Shape;

class Plane : public Shape
{

protected:
    vec3 p;
    vec3 du, dv;

public:
    Plane();
    Plane(vec3 _p, vec3 d1, vec3 d2, vec3 inputcolor);
    vec3 getColor() override;
    float Intersection(Ray *) override;

    Ray getReflectionRay(Ray *incomingRay) override;

    vec3 getNormal(Ray *incomingRay) override;

    vec3 middle() override;

    vec3 minBoundary() override;

    vec3 maxBoundary() override;
};

#endif //RAYTRACERCOPY_PLANE_H
