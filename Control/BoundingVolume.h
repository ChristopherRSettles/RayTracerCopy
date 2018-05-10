//
// Created by chris on 4/4/18.
//

#ifndef RAYTRACERCOPY_BOUNDINGVOLUME_H
#define RAYTRACERCOPY_BOUNDINGVOLUME_H
#include <vector>
#include <limits>
#include <utility>
#include "../Shapes/Shape.h"
#include "../Shapes/Box.h"


class BoundingVolume {

private:


    struct BVHNode {
        vec3 minboundaries;
        vec3 maxboundaries;
        Box bvhbox = Box(vec3(), vec3());

        Shape *shapeInBVH;
        BVHNode *leftVolume;
        BVHNode *rightVolume;
        int numberOfShapes;
        BVHNode(){
            shapeInBVH = nullptr;
            leftVolume = nullptr;
            rightVolume = nullptr;
            bvhbox = Box(vec3(0,0,0), vec3(0,0,0));
            numberOfShapes = -1;
        }
    };

    BVHNode * root;

    BoundingVolume();
    BVHNode * constructBVH(std::vector<Shape*>, int, BoundingVolume::BVHNode*&);
    Shape * closestIntersectionShape(BVHNode*, Ray *);
    Shape *closestShape(Ray *collisionRay, Shape *leftShape, Shape *rightShape);


public:
    BoundingVolume(std::vector<Shape*>&);

    Shape *closestIntersectionShape(Ray *myRay);
};


#endif //RAYTRACERCOPY_BOUNDINGVOLUME_H
