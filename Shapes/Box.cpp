//
// Created by Chris on 3/1/2018.
//

#include <limits>
#include <assert.h>
#include "Box.h"


//Box::Box(vec3 _p, vec3 d1, vec3 d2, vec3 d3, vec3 inputcolor)
//{
//    p = _p;
//    du = d1;
//    dv = d2;
//    dw = d3;
//    color = inputcolor;
//
//
//}

vec3 Box::getColor() { return color; }

float Box::Intersection(Ray *r)
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    if (r->dir.x() >= 0) {
        tmin = (minp.x() - r->p.x()) / r->dir.x();
        tmax = (maxp.x() - r->p.x()) / r->dir.x();
    }
    else {
        tmin = (maxp.x() - r->p.x()) / r->dir.x();
        tmax = (minp.x() - r->p.x()) / r->dir.x();
    }

    if (r->dir.y() >= 0) {
        tymin = (minp.y() - r->p.y()) / r->dir.y();
        tymax = (maxp.y() - r->p.y()) / r->dir.y();
    }
    else {
        tymin = (maxp.y() - r->p.y()) / r->dir.y();
        tymax = (minp.y() - r->p.y()) / r->dir.y();
    }
    if ( (tmin > tymax) || (tymin > tmax) )
        return -1;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    if (r->dir.z() >= 0) {
        tzmin = (minp.z() - r->p.z()) / r->dir.z();
        tzmax = (maxp.z() - r->p.z()) / r->dir.z();
    }
    else {
        tzmin = (maxp.z() - r->p.z()) / r->dir.z();
        tzmax = (minp.z() - r->p.z()) / r->dir.z();
    }
    if ( (tmin > tzmax) || (tzmin > tmax) )
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return ( tmin);
}


Ray Box::getReflectionRay(Ray *incomingRay) {
//    for(Plane& plane: planes){
//        if(plane.Intersection(incomingRay) > 0){                //Bug here!!!!!!!!! But idc because reflection rays are un needed.
//            return plane.getReflectionRay(incomingRay);         // Actually I do care because i do lighting stuffs.
//        }                                                       // Actually I don't because I'm not every drawing cubes, just using
//    }
    return Ray(vec3(0,0,0), vec3(0,0,0));
}

vec3 Box::getNormal(Ray *incomingRay) {
//    for(Plane& plane: planes){
//        if(plane.Intersection(incomingRay) > 0){
//            return plane.getNormal(incomingRay);
//        }
//    }
    return vec3(0,0,0);
}

vec3 Box::middle() {
    double u = maxp.x() - minp.x();
    double v = maxp.y() - minp.y();
    double w = maxp.z() - minp.z();
    vec3 du = vec3(u,0,0);
    vec3 dv = vec3(0,v,0);
    vec3 dw = vec3(0,0,w);
    return minp + du/2 + dw/2 + dv/2;
}

vec3 Box::minBoundary() {
    vec3 min(0, 0, 0);
        for(int i = 0; i < 3; i++){
            min[i] = std::min(minp[i], maxp[i]);

    }
    return min;
}

vec3 Box::maxBoundary() {
    vec3 max(0, 0, 0);
    for(int i = 0; i < 3; i++){
        max[i] = std::max(minp[i], maxp[i]);

    }
    return max;
}

/**
 * Construct a Box given two points.
 * @param p1
 * @param p2
 */
Box::Box(vec3 p1, vec3 p2) {
    if(p1.x() < p2.x()){
        minp[0] = p1.x();
        maxp[0] = p2.x();
    }
    else{
        maxp[0] = p1.x();
        minp[0] = p2.x();
    }
    if(p1.y() < p2.y()){
        minp[1] = p1.y();
        maxp[1] = p2.y();
    }
    else{
        maxp[1] = p1.y();
        minp[1] = p2.y();
    }
    if(p1.z() < p2.z()){
        minp[2] = p1.z();
        maxp[2] = p2.z();
    }
    else{
        maxp[2] = p1.z();
        minp[2] = p2.z();
    }
    assert(minp <= maxp);

}

//Box::Box(): Box(vec3(0,0,0), vec3(0,0,0), vec3(255,255,255)) {}

Box::Box(vec3 p1, vec3 p2, vec3 color) : Box(p1,p2) {
    this->color = color;
}
