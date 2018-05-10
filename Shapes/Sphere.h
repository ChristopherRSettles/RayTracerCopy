//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_SPHERE_H
#define RAYTRACERCOPY_SPHERE_H

//Christopher Settles
#include "../Control/vec3.h"
#include "Shape.h"
#include "../Control/Ray.h"
#include "../Control/Color.h"

using namespace std;

class Shape;

class Sphere : public Shape
{

private:
	float radius;
	vec3 center;

public:
	Sphere(vec3 p, float r, vec3 inputcolor);
	vec3 getColor();
	vec3 getpoint();
	float getradius();
	float Intersection(Ray *);

    Ray getReflectionRay(Ray *incomingRay) override;

	vec3 getNormal(Ray *incomingRay) override;

	vec3 middle() override;

	vec3 minBoundary() override;

	vec3 maxBoundary() override;
};

#endif //RAYTRACERCOPY_SPHERE_H
