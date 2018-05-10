//
// Created by chris on 3/14/18.
//

#include "Triangle.h"

Triangle::Triangle(const vec3 &_p, const vec3 &d1, const vec3 &d2, const vec3 &inputcolor) : Plane(_p, d1, d2,
                                                                                                   inputcolor) {}

float Triangle::Intersection(Ray *ray) {
    double t, u, v;
    double position_difference_x = (p.x() - ray->getpoint().x());
    double position_difference_y = (p.y() - ray->getpoint().y());
    double position_difference_z = (p.z() - ray->getpoint().z());
    vec3 dt = ray->getdir();
//    cout << "t: "<<dt <<", u: " <<du <<", v: " << dv <<endl;
    double MatrixADeterminant =
            (
                    dt.x()*(du.y()*dv.z() - dv.y()*du.z()) +
                    dt.y()*(du.x()*dv.z() - dv.x()*du.z()) +
                    dt.z()*(du.x()*dv.y() - dv.x()*du.y())
            );
    if (MatrixADeterminant == 0) {
//        std::cout <<"Ray did not hit! MatrixADeterminant value: " <<MatrixADeterminant <<std::endl;
        return -1;
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
        float y = u;
        float x = v;
        if (abs(y/x < 1)) {
            return (float) t;
        }
    }
//    cout <<"Ray did not hit! t value: " <<t <<endl;



    return -1;
}
