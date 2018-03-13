#include "Plane.h"


Plane::Plane(vec3 _p, vec3 d1, vec3 d2, Color inputcolor)//: Shape()
{
    p = _p;
    du = d1;
    dv = d2;
    color = inputcolor;
}

Color Plane::getColor(){ return color; }

vec3 Plane::Intersection(Ray *myRay)
{
    //This is the place that I need to figure out if the line and the plane are orthagonal

    double t, u, v;
    double position_difference_x = (p.x() - myRay->getpoint().x());
    double position_difference_y = (p.y() - myRay->getpoint().y());
    double position_difference_z = (p.z() - myRay->getpoint().z());
    vec3 dt = myRay->getdir();
    double MatrixADeterminant =
            (
                    dt.x()*(du.y()*dv.z() - dv.y()*du.z()) +
                    dt.y()*(du.x()*dv.z() - dv.x()*du.z()) +
                    dt.z()*(du.x()*dv.y() - dv.x()*du.y())
            );
    if (MatrixADeterminant == 0) {
        return false;
    }

    t = (
                (position_difference_x)*(du.y()*dv.z() - dv.y()*du.z()) +
                (position_difference_y)*(du.x()*dv.z() - dv.x()*du.z()) +
                (position_difference_z)*(du.x()*dv.y() - dv.x()*du.y())
        )
        / MatrixADeterminant;

    u = (
                dt.x()*((position_difference_y)*(-dv.z()) + (dv.y())*(position_difference_z)) +
                dt.y()*((position_difference_x)*(-dv.z()) + (dv.x())*(position_difference_z)) +
                dt.z()*((position_difference_x)*(-dv.y()) + (dv.x())*(position_difference_y))
        )
        / MatrixADeterminant;

    v = (
                dt.x()*((-du.y())* (position_difference_z) + (du.z())*(position_difference_y)) +
                dt.y()*((-du.x())* (position_difference_z) + (du.z())*(position_difference_x)) +
                dt.z()*((-du.x())* (position_difference_y) + (du.y())*(position_difference_x))
        )
        / MatrixADeterminant;

    if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1))
    {
        return true;
    }

    return false;
}
