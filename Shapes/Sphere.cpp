
#include <algorithm>
#include "Sphere.h"


Sphere::Sphere(int inputx, int inputy, int inputz, float inputr, Color inputcolor) //: Shape()
{
    center = vec3(inputx, inputy, inputz);
    radius = inputr;
    color = inputcolor;
}

Color Sphere::getColor()
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

    //The normal vector is (c-p) where p is the intersection point.
    vec3 sphereNormalVec = this->center - intersectionPoint;

    //Needs to be a unit vector
    sphereNormalVec.make_unit_vector();

    //We will create the offset
    vec3 offsetB = sphereNormalVec*incomingRay->getdir().length();
    vec3 reflectionDir = incomingRay->getdir() + 2*offsetB;

    Ray reflectionRay(reflectionDir, intersectionPoint);
    return reflectionRay;
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
