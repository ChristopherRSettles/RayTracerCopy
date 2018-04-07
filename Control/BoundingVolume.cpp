//
// Created by chris on 4/4/18.
//

#include "BoundingVolume.h"
#include "../Shapes/Box.h"

#include <utility>


BoundingVolume::BoundingVolume(std::vector<Shape *> shapes) {
    constructBVH(std::move(shapes), 0, root);
}

BoundingVolume::BVHNode* BoundingVolume::constructBVH(std::vector<Shape*> shapes, int n, BoundingVolume::BVHNode* subroot){

    // Loop over all the shapes to find the bvh's min and max boundaries
    vec3 bvhmin(INT64_MAX, INT64_MAX, INT64_MAX);
    vec3 bvhmax(INT64_MIN, INT64_MIN, INT64_MIN);
    for(auto shape : shapes){
        for(int d = 0; d < 3; d++){
            if(shape->minBoundary()[d] < bvhmin[d]){
                bvhmin[d] = shape->minBoundary()[d];
            }
            if(shape->maxBoundary()[d] > bvhmax[d]){
                bvhmax[d] = shape->maxBoundary()[d];
            }
        }
    }


    // loop through all the shapes to find the mean in the nth dimension
    double meanAcrossDimension_n = 0;
    for(int i = 0; i < shapes.size(); i++){
        meanAcrossDimension_n += shapes[i]->middle()[n];
    }
    meanAcrossDimension_n/=shapes.size();

    // Divide up the objects so that the ones on the left of the mean are to the left and the ones on the
    // right of the mean or in the middle will go on the right.
    std::vector<Shape*> shapesOnLeft;
    std::vector<Shape*> shapesOnRight;
    for (Shape *& shape : shapes) {
        double shapeMiddle = shape->middle()[n];
        if(shapeMiddle < meanAcrossDimension_n){
            shapesOnLeft.push_back(shape);
        }
        else{
            shapesOnRight.push_back(shape);
        }
    }

    if(shapes.size() == 2 && (shapes[0]->middle()[n] == shapes[1]->middle()[n])){
        shapesOnLeft = {shapes[0]};
        shapesOnRight = {shapes[1]};
    }

    //
    if (shapes.size() <= 0){
        subroot = nullptr;
        throw; //It's okay if this happens. (It means that the step before had two nodes that were both on the right
    } else if (shapes.size() == 1){
        subroot = new BoundingVolume::BVHNode();
        subroot->shapeInBVH = shapes[0];
        subroot->minboundaries = bvhmin;
        subroot->maxboundaries = bvhmax;
        subroot->leftVolume = nullptr;
        subroot->rightVolume = nullptr;
    }
    else{
        subroot = new BoundingVolume::BVHNode();
        subroot->shapeInBVH = nullptr;
        subroot->minboundaries = bvhmin;
        subroot->maxboundaries = bvhmax;
        constructBVH(shapesOnLeft,  (n+1) %3, subroot->leftVolume);
        constructBVH(shapesOnRight, (n+1) %3, subroot->rightVolume);

    }
}

Shape * BoundingVolume::closestIntersectionShape(Ray *myRay) {
    return closestIntersectionShape(root, myRay);
}

Shape * BoundingVolume::closestIntersectionShape(BVHNode* bvhNode, Ray *myRay) {
    Box bvhbox = Box(bvhNode->minboundaries, bvhNode->maxboundaries);
    if(myRay->Intersection(&bvhbox) < 0){
        return nullptr;
    }
    else{
        return closestShape(myRay,
                            closestIntersectionShape(bvhNode->leftVolume, myRay),
                            closestIntersectionShape(bvhNode->rightVolume, myRay));
    }
    return nullptr;
}

BoundingVolume::BoundingVolume() {}

Shape *BoundingVolume::closestShape(Ray* collisionRay, Shape *leftShape, Shape *rightShape) {
    bool badLeftShape = (leftShape == nullptr) || (leftShape->Intersection(collisionRay) < 0 );
    bool badRightShape = (rightShape == nullptr) || (rightShape->Intersection(collisionRay) < 0);
    if (badLeftShape && badRightShape){
        return nullptr;
    }
    else if(badLeftShape && !badRightShape){
        return rightShape;
    }
    else if(!badLeftShape && badRightShape){
        return leftShape;
    }
    else{
        double left_t = leftShape->Intersection(collisionRay);
        double right_t = rightShape->Intersection(collisionRay);
        if(left_t < right_t){
            return leftShape;
        }
        else if(right_t>left_t){
            return rightShape;
        }
        else {
            int arr[] = {3};
            throw;
            arr[-1]; //Purposefully segfault.
            return nullptr;
        }
    }
}
