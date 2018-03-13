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
	Sphere(int x, int y, int z, float r, Color inputcolor);
	Color getColor();
	vec3 getpoint();
	float getradius();
	float Intersection(Ray *);

    Ray getReflectionRay(Ray *incomingRay) override;
};

#endif //RAYTRACERCOPY_SPHERE_H
