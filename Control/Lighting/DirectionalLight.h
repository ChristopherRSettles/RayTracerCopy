//
// Created by chris on 3/14/18.
//

#ifndef RAYTRACERCOPY_DIRECTIONALLIGHT_H
#define RAYTRACERCOPY_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight: public Light {
    float getRatioOfLightOnShape(Shape *shape, Ray *ray) override;

public:
    DirectionalLight(const vec3 &direction);

private:

    vec3 direction;
};


#endif //RAYTRACERCOPY_DIRECTIONALLIGHT_H
