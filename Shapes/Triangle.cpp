//
// Created by chris on 5/9/18.
//

#include "Triangle.h"

vec3 triangle::getColor() {
    return color;
}

// Used from the article for https://blogs.msdn.microsoft.com/rezanour/2011/08/07/barycentric-coordinates-and-point-in-triangle-tests/
// Borrowed other ideas from this person who rendered planes :
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
float triangle::Intersection(Ray *ray) {
    // Prepare our barycentric variables

    //Need to compute P, the point at which the ray intersection the triangle plane.

    vec3 u = point_B - point_A;
    vec3 v = point_C - point_A;

    vec3 n = cross(u,v);

    float intersect_t = dot((point_A - ray->p), n) / dot(ray->dir, n);
    vec3 P = ray->p + ray->dir*intersect_t;

    vec3 w = P - point_A;

    vec3 vCrossW = cross(v, w);
    vec3 vCrossU = cross(v, u);


    // Test sign of r

    if (dot(vCrossW, vCrossU) < 0)
        return false;

    vec3 uCrossW = cross(u, w);
    vec3 uCrossV = cross(u, v);

    // Test sign of t

    if (dot(uCrossW, uCrossV) < 0)

        return false;


    // At this point, we know that r and t and both > 0.

    // Therefore, as long as their sum is <= 1, each must be less <= 1

    float denom = uCrossV.length();

    float r = vCrossW.length() / denom;

    float t = uCrossW.length() / denom;


    if(r + t <= 1){
        return t;
    }
    return 0.0;
}

Ray triangle::getReflectionRay(Ray *incomingRay) {
    //get the t value that the ray intersects the sphere at.
    float t = this->Intersection(incomingRay);

    //get the point on the sphere that this intersection is done.
    vec3 intersectionPoint = incomingRay->getpoint() + incomingRay->getdir() * t;

    vec3 planeNormalVector = getNormal(incomingRay);

    //We will create the offset
    vec3 offsetB = planeNormalVector * incomingRay->getdir().length();
    vec3 reflectionDir = incomingRay->getdir() + 2 * offsetB;

    Ray reflectionRay(reflectionDir, intersectionPoint);
    return reflectionRay;
}

vec3 triangle::getNormal(Ray *incomingRay) {
    vec3 u = point_B - point_A;
    vec3 v = point_C - point_A;

    vec3 normal1 = cross(u, v);
    vec3 normal2 = -normal1;
    float dot1 = dot(incomingRay->getdir(), normal1);
    float dot2 = dot(incomingRay->getdir(), normal2);
    vec3 planeNormalVector;

    if(dot1 >= 0 && dot2 <= 0){
        planeNormalVector = normal1;
    }
    else if (dot1 <= 0 && dot2 >= 0){
        planeNormalVector = normal2;
    }
    else{
        planeNormalVector = vec3(0,0,0);
        std::cout<<"The two dot products of the ray with the plane have the same sign: dot1: " <<dot <<" dot2: " <<dot2 <<std::endl;
    }

    //Needs to be a unit vector
    planeNormalVector.make_unit_vector();
    return planeNormalVector;
}

vec3 triangle::middle() {
    vec3 median = (point_A + point_B + point_C) / 3;
    return median;
}

vec3 triangle::minBoundary() {
//    float minx = (float) std::min(std::min(2.0 , 2.2 ), 2.0);
    float minx = std::min(point_C.x(), float(std::min(point_A.x(), point_B.x())));
    float miny = std::min(point_C.y(), float(std::min(point_A.y(), point_B.y())));
    float minz = std::min(point_C.z(), float(std::min(point_A.z(), point_B.z())));

    return vec3(minx, miny, minz);
}

vec3 triangle::maxBoundary() {
    float maxx = std::max(point_C.x(), float(std::max(point_A.x(), point_B.x())));
    float maxy = std::max(point_C.y(), float(std::max(point_A.y(), point_B.y())));
    float maxz = std::max(point_C.z(), float(std::max(point_A.z(), point_B.z())));

    return vec3(maxx, maxy, maxz);
}

triangle::triangle(vec3 a, vec3 b, vec3 c, vec3 color_): point_A(a), point_B(b), point_C(c) {
    color = color_;
}

const vec3 &triangle::getPoint_A() const {
    return point_A;
}

const vec3 &triangle::getPoint_B() const {
    return point_B;
}

const vec3 &triangle::getPoint_C() const {
    return point_C;
}

void triangle::setPoint_A(const vec3 &point_A) {
    triangle::point_A = point_A;
}

void triangle::setPoint_B(const vec3 &point_B) {
    triangle::point_B = point_B;
}

void triangle::setPoint_C(const vec3 &point_C) {
    triangle::point_C = point_C;
}
