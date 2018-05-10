//
// Created by chris on 4/4/18.
//

#include "BoundingVolume.h"
#include "../Shapes/Box.h"


BoundingVolume::BoundingVolume(std::vector<Shape *>& shapes) {
//    root = nullptr;
    constructBVH(shapes, 0, root);
}

BoundingVolume::BVHNode* BoundingVolume::constructBVH(std::vector<Shape*> shapes, int currDim, BoundingVolume::BVHNode*& subroot){
    // Loop over all the shapes to find the bvh's min and max boundaries
    float maxFloat = std::numeric_limits<float>::max();
    float minFloat = -maxFloat;
    vec3 bvhmin(maxFloat, maxFloat, maxFloat);
    vec3 bvhmax(minFloat, minFloat, minFloat);

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
        meanAcrossDimension_n += shapes[i]->middle()[currDim%3];
    }
    meanAcrossDimension_n/=shapes.size();

    // Divide up the objects so that the ones on the left of the mean are to the left and the ones on the
    // right of the mean or in the middle will go on the right.
    std::vector<Shape*> shapesOnLeft;
    std::vector<Shape*> shapesOnRight;
    bool flip = false;
    for (Shape *& shape : shapes) {
        double shapeMiddle = shape->middle()[currDim%3];
        if(shapeMiddle < meanAcrossDimension_n){
            shapesOnLeft.push_back(shape);
        }
        else if (shapeMiddle > meanAcrossDimension_n){
            shapesOnRight.push_back(shape);
        }
        else{
            if(flip){
                shapesOnLeft.push_back(shape);
            }
            else{
                shapesOnRight.push_back(shape);
            }
            flip = !flip;
        }
    }

    if(shapes.size() == 2 && (shapes[0]->middle()[currDim %3] == shapes[1]->middle()[currDim %3])){
        shapesOnLeft = {shapes[0]};
        shapesOnRight = {shapes[1]};
    }

    //
    if (shapes.size() == 0){
        subroot = nullptr;
//        throw; //It's okay if this happens. (It means that the step before had two nodes that were both on the right
    } else if (shapes.size() == 1){
        subroot = new BoundingVolume::BVHNode();
        subroot->shapeInBVH = shapes[0];

        subroot->minboundaries = bvhmin;
        subroot->maxboundaries = bvhmax;
        subroot->bvhbox = Box(bvhmin, bvhmax);
        subroot->numberOfShapes = 1;

        subroot->leftVolume = nullptr;
        subroot->rightVolume = nullptr;
    }
    else{
        subroot = new BoundingVolume::BVHNode();
        subroot->shapeInBVH = nullptr;

        subroot->minboundaries = bvhmin;
        subroot->maxboundaries = bvhmax;
        subroot->bvhbox = Box(bvhmin, bvhmax);
        subroot->numberOfShapes = shapes.size();

        constructBVH(shapesOnLeft,  (currDim+1), subroot->leftVolume);
        constructBVH(shapesOnRight, (currDim+1), subroot->rightVolume);
    }
}

Shape * BoundingVolume::closestIntersectionShape(Ray *myRay) {
    return closestIntersectionShape(root, myRay);
}

Shape * BoundingVolume::closestIntersectionShape(BVHNode* bvhNode, Ray *myRay) {

    if(myRay->Intersection(&bvhNode->bvhbox) < 0){
        return nullptr; //It doesn't intersect the box
    }
    else { //It intersects the box.
        if (bvhNode->shapeInBVH != nullptr) { //If the box has a shape
            if(myRay->Intersection(bvhNode->shapeInBVH) > 0){ //it intersects the shape in the box!
                return bvhNode->shapeInBVH;
            }
            else{ //It doesn't intersect the shape in the box.
                return nullptr;
            }
        }
        else { //The box doesn't have a shape ptr. It must have either a left or a right pointer.
            return closestShape(myRay,
                                closestIntersectionShape(bvhNode->leftVolume, myRay),
                                closestIntersectionShape(bvhNode->rightVolume, myRay));
        }
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
        else if(left_t > right_t){
            return rightShape;
        }
        else {
            //throw;
            return rightShape;
        }
    }
}
