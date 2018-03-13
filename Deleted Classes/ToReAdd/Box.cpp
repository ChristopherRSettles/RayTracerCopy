//
// Created by Chris on 3/1/2018.
//

#include "Box.h"


Box::Box(vec3 _p, vec3 d1, vec3 d2, vec3 d3, Color inputcolor)//: Shape()
{
    p = _p;
    du = d1;
    dv = d2;
    dw = d3;
    color = inputcolor;
}

Color Box::getColor() { return color; }

vec3 Box::Intersection(Ray *myRay)
{
    vec3 point2(
            p.x() + du.x() + dv.() + dw.x(),
            p.y() + du.y() + dv.y() + dw.y(),
            p.z() + du.z() + dv.z() + dw.z()
    );

    return (new Plane(p, du, dv, color))->Intersection(myRay) ||
            (new Plane(p, du, dw, color))->Intersection(myRay) ||
            (new Plane(p, dv, dw, color))->Intersection(myRay) ||
            (new Plane(point2, -du, -dv, color))->Intersection(myRay) ||
            (new Plane(point2, -du, -dw, color))->Intersection(myRay) ||
            (new Plane(point2, -dv, -dw, color))->Intersection(myRay);

}
