//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_RAY_H
#define RAYTRACERCOPY_RAY_H

//Christopher Settles
#include "../Shapes/Shape.h"
#include "vec3.h"

class Shape;

class Ray
{

public:
    vec3 dir;
    vec3 p;

public:
    Ray(vec3 inputdir = vec3(0,0,0), vec3 inputp = vec3(0,0,0));
    double distanceto(Shape *sh);

    vec3 getdir();

    vec3 getpoint();

    float Intersection(Shape *pShape);
};

#endif //RAYTRACERCOPY_RAY_H
