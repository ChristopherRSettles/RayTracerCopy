//
// Created by chris on 3/14/18.
//

#ifndef RAYTRACERCOPY_TRIANGLE_H
#define RAYTRACERCOPY_TRIANGLE_H


#include "Plane.h"

class Triangle : public Plane {
public:
    Triangle(const vec3 &_p, const vec3 &d1, const vec3 &d2, const vec3 &inputcolor);

    float Intersection(Ray *ray) override;

};


#endif //RAYTRACERCOPY_TRIANGLE_H
