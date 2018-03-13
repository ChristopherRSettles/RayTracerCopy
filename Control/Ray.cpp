//
// Created by Chris on 3/1/2018.
//

#include "Ray.h"

Ray::Ray(vec3 inputdir, vec3 inputp)
{
    dir = inputdir;
    p = inputp;
}

double Ray::distanceto(Shape * sh)
{
    return 0.0;
}

vec3 Ray::getdir()
{
    return dir;
}
vec3 Ray::getpoint()
{
    return p;
}

float Ray::Intersection(Shape *pShape) {
    return pShape->Intersection(this);
}
