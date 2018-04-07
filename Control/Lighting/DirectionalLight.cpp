//
// Created by chris on 3/14/18.
//

#include "DirectionalLight.h"

float DirectionalLight::getRatioOfLightOnShape(Shape *shape, Ray *ray) {
    //return the max of 0 and the dot product between the normal vector on the shape and the light direction.
    vec3 shapeNormalVector = shape->getNormal(ray);
    direction.make_unit_vector();
    const double test = std::max(0.2, 0.3);
    const double max = std::max(0.0, (double) dot(direction, shapeNormalVector));
    return (float) max;
}

DirectionalLight::DirectionalLight(const vec3 &direction) : direction(direction) {}
