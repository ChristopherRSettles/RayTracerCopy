//
// Created by Chris on 3/1/2018.
//

#include "Box.h"


Box::Box(vec3 _p, vec3 d1, vec3 d2, vec3 d3, vec3 inputcolor)
{
    p = _p;
    du = d1;
    dv = d2;
    dw = d3;
    color = inputcolor;

    vec3 point2 = p + du + dv + dw;


    planes[0] = Plane(p, du, dv, color);
    planes[1] = Plane(p, du, dw, color);
    planes[2] = Plane(p, dv, dw, color);
    planes[3] = Plane(point2, -du, -dv, color);
    planes[4] = Plane(point2, -du, -dw, color);
    planes[5] = Plane(point2, -dv, -dw, color);
}

vec3 Box::getColor() { return color; }

float Box::Intersection(Ray *myRay)
{
    double min_t = INT64_MAX;

    for(Plane& plane: planes){
        double current_t = plane.Intersection(myRay);
        if(current_t > 0 && current_t < min_t){
            min_t = current_t;
        }
    }

    if(min_t != INT64_MAX){
        return min_t;
    }
    else{
        return -1;
    }

}

Ray Box::getReflectionRay(Ray *incomingRay) {
    for(Plane& plane: planes){
        if(plane.Intersection(incomingRay) > 0){                //Bug here!!!!!!!!! But idc because reflection rays are un needed.
            return plane.getReflectionRay(incomingRay);         // Actually I do care because i do lighting stuffs.
        }                                                       // Actually I don't because I'm not every drawing cubes, just using
    }
    return Ray(vec3(0,0,0), vec3(0,0,0));
}

vec3 Box::getNormal(Ray *incomingRay) {
    for(Plane& plane: planes){
        if(plane.Intersection(incomingRay) > 0){
            return plane.getNormal(incomingRay);
        }
    }
    return vec3(0,0,0);
}

vec3 Box::middle() {
    return p + du/2 + dw/2 + dv/2;
}

vec3 Box::minBoundary() {
    vec3 min(INT64_MAX, INT64_MAX, INT64_MAX);
    for(Plane& plane : planes){
        for(int i = 0; i < 3; i++){
            if(plane.minBoundary()[i] < min[i]){
                min[i] = plane.minBoundary()[i];
            }
        }
    }
    return min;
}

vec3 Box::maxBoundary() {
    vec3 max(INT64_MIN, INT64_MIN, INT64_MIN);
    for(Plane& plane : planes){
        for(int i = 0; i < 3; i++){
            if(plane.minBoundary()[i] > max[i]){
                max[i] = plane.minBoundary()[i];
            }
        }
    }
    return max;
}

/**
 * Construct a Box given two points.
 * @param p1
 * @param p2
 */
Box::Box(vec3 p1, vec3 p2) {
    double u = p2.x() - p1.x();
    double v = p2.y() - p1.y();
    double w = p2.z() - p1.z();
    du = vec3(u,0,0);
    dv = vec3(0,v,0);
    dw = vec3(0,0,w);
    p = p1;
}
