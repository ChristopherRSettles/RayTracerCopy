//
// Created by chris on 3/14/18.
//

#ifndef RAYTRACERCOPY_LIGHT_H
#define RAYTRACERCOPY_LIGHT_H

#include "../../Shapes/Shape.h"

class Light {
public:
    virtual float getRatioOfLightOnShape(Shape *shape, Ray *ray) = 0;
};

#endif //RAYTRACERCOPY_LIGHT_H
