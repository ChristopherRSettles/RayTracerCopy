//
// Created by chris on 5/9/18.
//

#ifndef RAYTRACERCOPY_TRIANGLE_H
#define RAYTRACERCOPY_TRIANGLE_H


#include "Shape.h"

class triangle : public Shape {
private:

    vec3 point_A, point_B, point_C;
public:
    const vec3 &getPoint_A() const;

    const vec3 &getPoint_B() const;

    const vec3 &getPoint_C() const;

    void setPoint_A(const vec3 &point_A);

    void setPoint_B(const vec3 &point_B);

    void setPoint_C(const vec3 &point_C);

    triangle(vec3 a, vec3 b, vec3 c, vec3 color_);

    vec3 getColor() override;

    float Intersection(Ray *ray) override;

    Ray getReflectionRay(Ray *incomingRay) override;

    vec3 getNormal(Ray *incomingRay) override;

    vec3 middle() override;

    vec3 minBoundary() override;

    vec3 maxBoundary() override;
};


#endif //RAYTRACERCOPY_TRIANGLE_H
