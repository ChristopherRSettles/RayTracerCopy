//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_SHAPE_H
#define RAYTRACERCOPY_SHAPE_H
//Christopher Settles
#include <cmath>
#include "../Control/Ray.h"
#include "../Control/Color.h"
#include "../Control/vec3.h"

class Ray;

class Shape
{
    //Use of an Abstract base class (A class that has virtual functions in it)
protected:
    vec3 color;

    //Use of pure virtual functions here (A virtual function is one that
    //must be overridden by a class that inherits from this class)
public:
    virtual vec3 getColor() =0;

    virtual float Intersection(Ray *ray) = 0;

    virtual Ray getReflectionRay(Ray *incomingRay) = 0;

    virtual vec3 getNormal(Ray *incomingRay) = 0;

    virtual vec3 middle() = 0;

    virtual vec3 minBoundary() = 0;

    virtual vec3 maxBoundary() = 0;

};

#endif //RAYTRACERCOPY_SHAPE_H
