//
// Created by chris on 4/4/18.
//

#ifndef RAYTRACERCOPY_BOUNDINGVOLUME_H
#define RAYTRACERCOPY_BOUNDINGVOLUME_H
#include <vector>
#include "../Shapes/Shape.h"


class BoundingVolume {

private:


    struct BVHNode {
        vec3 minboundaries;
        vec3 maxboundaries;

        Shape *shapeInBVH;
        BVHNode *leftVolume;
        BVHNode *rightVolume;
    };

    BVHNode * root;

    BoundingVolume();
    BVHNode * constructBVH(std::vector<Shape*>, int, BoundingVolume::BVHNode*);
    Shape * closestIntersectionShape(BVHNode*, Ray *);
    Shape *closestShape(Ray *collisionRay, Shape *leftShape, Shape *rightShape);


public:
    BoundingVolume(std::vector<Shape*>);

    Shape *closestIntersectionShape(Ray *myRay);
};


#endif //RAYTRACERCOPY_BOUNDINGVOLUME_H
