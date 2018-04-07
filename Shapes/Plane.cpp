#include "Plane.h"


Plane::Plane(vec3 _p, vec3 d1, vec3 d2, vec3 inputcolor)//: Shape()
{
    p = _p;
    du = d1;
    dv = d2;
    color = inputcolor;
}

vec3 Plane::getColor(){ return color; }

float Plane::Intersection(Ray *myRay)
{
    //This is the place that I need to figure out if the line and the plane are orthagonal

    double t, u, v;
    double position_difference_x = (p.x() - myRay->getpoint().x());
    double position_difference_y = (p.y() - myRay->getpoint().y());
    double position_difference_z = (p.z() - myRay->getpoint().z());
    vec3 dt = myRay->getdir();
//    cout << "t: "<<dt <<", u: " <<du <<", v: " << dv <<endl;
    double MatrixADeterminant =
            (
                    dt.x()*(du.y()*dv.z() - dv.y()*du.z()) +
                    dt.y()*(du.x()*dv.z() - dv.x()*du.z()) +
                    dt.z()*(du.x()*dv.y() - dv.x()*du.y())
            );
    if (MatrixADeterminant == 0) {
//        std::cout <<"Ray did not hit! MatrixADeterminant value: " <<MatrixADeterminant <<std::endl;

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
//        cout <<"Ray hit!" <<endl;
        return (float)t;
    }
//    cout <<"Ray did not hit! t value: " <<t <<endl;



    return -1;
}

Ray Plane::getReflectionRay(Ray *incomingRay) {
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

vec3 Plane::getNormal(Ray *incomingRay) {
    //The normal vector du x dv
    vec3 normal1 = cross(this->du, this->dv);
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

vec3 Plane::middle() {
    return p + du/2 + dv/2;
}

vec3 Plane::minBoundary() {

    float minx = std::min(float(std::min(p.x(), p.x() + du.x())), float(std::min(p.x() + dv.x(), p.x() + du.x() + dv.x())));
    float miny = std::min(float(std::min(p.y(), p.y() + du.y())), float(std::min(p.y() + dv.y(), p.y() + du.y() + dv.y())));
    float minz = std::min(float(std::min(p.z(), p.z() + du.z())), float(std::min(p.z() + dv.z(), p.z() + du.z() + dv.z())));

    return vec3(minx, miny, minz);
}

vec3 Plane::maxBoundary() {
    float maxx = std::max(float(std::max(p.x(), p.x() + du.x())), float(std::max(p.x() + dv.x(), p.x() + du.x() + dv.x())));
    float maxy = std::max(float(std::max(p.y(), p.y() + du.y())), float(std::max(p.y() + dv.y(), p.y() + du.y() + dv.y())));
    float maxz = std::max(float(std::max(p.z(), p.z() + du.z())), float(std::max(p.z() + dv.z(), p.z() + du.z() + dv.z())));

    return vec3(maxx, maxy, maxz);
}

Plane::Plane() {

}
