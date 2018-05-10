//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_CAPSULE_H
#define RAYTRACERCOPY_CAPSULE_H

//Christopher Settles
#include "Shape.h"
#include "Sphere.h"
using namespace std;

class Shape;
//Instance of Polymorphism here (and Inheritance)
//Capsule IS A Shape. (Polymorphism)
//Capsule inherits all the attributes of shape. (Inheritance)
class Capsule: public Shape
{

private:

    vec3 startpoint, endpoint;
    int r;

public:
    Capsule(vec3 inputstartpoint, vec3 inputendpoint, int inputr, vec3 inputcolor);

    Ray getReflectionRay(Ray *incomingRay) override;

    vec3 getNormal(Ray *incomingRay) override;

    vec3 middle() override;

    vec3 minBoundary() override;

    vec3 maxBoundary() override;


    vec3 getColor();
    float Intersection(Ray *);
    vec3 getdir();
    vec3 getpoint();
    int getradius();
    vec3 getendpoint();
};

#endif //RAYTRACERCOPY_CAPSULE_H
