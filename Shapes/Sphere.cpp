
#include <algorithm>
#include "Sphere.h"


Sphere::Sphere(int inputx, int inputy, int inputz, float inputr, vec3 inputcolor) //: Shape()
{
    center = vec3(inputx, inputy, inputz);
    radius = inputr;
    color = inputcolor;
}

vec3 Sphere::getColor()
{
    return color;

}

vec3 Sphere::getpoint()
{
    return center;
}
float Sphere::getradius()
{
    return radius;
}


/*
 *
float Plane::Intersection(Ray *ray) {
    //This is the place that I need to figure out if the line and the plane are orthagonal

    double t, u, v;
    double position_difference_x = (p.x() - ray->getpoint().x());
    double position_difference_y = (p.y() - ray->getpoint().y());
    double position_difference_z = (p.z() - ray->getpoint().z());
    vec3 dt = ray->getdir();
    double MatrixADeterminant =
            (
                    dt.x()*(du.y()*dv.z() - dv.y()*du.z()) +
                    dt.y()*(du.x()*dv.z() - dv.x()*du.z()) +
                    dt.z()*(du.x()*dv.y() - dv.x()*du.y())
            );
    if (MatrixADeterminant == 0) {
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
        return t;
    }

    return -1;
}
 */
float Sphere::Intersection(Ray *r) {
    vec3 oc = r->getpoint() - center;
    float a = dot(r->getdir(), r->getdir());
    float b = dot(oc, r->getdir());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if(discriminant < 0){
        return static_cast<float>(-1.0);
    }
    else{
        return static_cast<float>((-b - sqrt(discriminant) ) / (2.0 * a));
        //This could be wrong actually because i'm not taking the
        //min of two things and I think I should be
    }

}

Ray Sphere::getReflectionRay(Ray *incomingRay) {
    //get the t value that the ray intersects the sphere at.
    float t = this->Intersection(incomingRay);

    //get the point on the sphere that this intersection is done.
    vec3 intersectionPoint = incomingRay->getpoint() + incomingRay->getdir()*t;

    vec3 sphereNormalVec = getNormal(incomingRay);

    //We will create the offset
    vec3 offsetB = sphereNormalVec*incomingRay->getdir().length();
    vec3 reflectionDir = incomingRay->getdir() + 2*offsetB;

    Ray reflectionRay(reflectionDir, intersectionPoint);
    return reflectionRay;
}

vec3 Sphere::getNormal(Ray *incomingRay) {
    //get the t value that the ray intersects the sphere at.
    float t = this->Intersection(incomingRay);

    //get the point on the sphere that this intersection is done.
    vec3 intersectionPoint = incomingRay->getpoint() + incomingRay->getdir()*t;

    //The normal vector is (c-p) where p is the intersection point.
    vec3 sphereNormalVec = this->center - intersectionPoint;

    //Needs to be a unit vector
    sphereNormalVec.make_unit_vector();
    return sphereNormalVec;
}

vec3 Sphere::middle() {
    return center;
}

vec3 Sphere::minBoundary() {
    double minx = std::min(center.x() - radius, center.x() + radius);
    double miny = std::min(center.y() - radius, center.y() + radius);
    double minz = std::min(center.z() - radius, center.z() + radius);

    return vec3(minx, miny, minz);
}

vec3 Sphere::maxBoundary() {
    double maxx = std::max(center.x() - radius, center.x() + radius);
    double maxy = std::max(center.y() - radius, center.y() + radius);
    double maxz = std::max(center.z() - radius, center.z() + radius);

    return vec3(maxx, maxy, maxz);
}
//float Sphere::Intersection(Ray *myRay)
//{
//    //If interested in learning where math came from, see math notebook for Calc 3.
//    double a =
//            (double)
//                    pow((myRay->getdir().x()), 2) +
//            pow((myRay->getdir().y()), 2) +
//            pow((myRay->getdir().z()), 2);
//
//    double b =
//            (double)
//                    2 * (myRay->getdir().x())*(myRay->getpoint().x() - this->getpoint().x()) +
//                    2 * (myRay->getdir().y())*(myRay->getpoint().y() - this->getpoint().y()) +
//                    2 * (myRay->getdir().z())*(myRay->getpoint().z() - this->getpoint().z());
//
//    double c =
//            (double)
//                    pow((myRay->getpoint().x() - this->getpoint().x()), 2) +
//            pow((myRay->getpoint().y() - this->getpoint().y()), 2) +
//            pow((myRay->getpoint().z() - this->getpoint().z()), 2);
//
//    double intersectionVecMangnitude_t = (-b) / (2*a);// Not true.
//    double pos_t = ((-1)*b + sqrt(pow(b,2) - 4*a*c)) / (2*a);
//    double neg_t = ((-1)*b + sqrt(pow(b,2) - 4*a*c)) / (2*a);
//
//    myRay->getdir().make_unit_vector();
//
//    vec3 pos_Intersection_Point = vec3(myRay->getpoint()  + myRay->getdir() * pos_t);
//    vec3 neg_Intersection_Point = vec3(myRay->getpoint() + myRay->getdir() * neg_t);
//    if ((-pow(b, 2) + 4 * a * c) / (4 * a) < pow(this->getradius(),2) && -b/(2*a) > 0 )
//    {
//        if(pos_t > neg_t)
//    }
//    else
//    {
//        return FAILED_INTERSECTION;
//    }
//}
