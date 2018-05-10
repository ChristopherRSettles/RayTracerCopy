//
// Created by Chris on 3/1/2018.
//

#include "Capsule.h"


Capsule::Capsule(vec3 inputstartpoint, vec3 inputendpoint, int inputr, vec3 inputcolor) //: Shape()
{
    startpoint = inputstartpoint;
    endpoint = inputendpoint;
    r = inputr;
    color = inputcolor;
}
vec3 Capsule::getColor()
{
    return color;
}

vec3 Capsule::getdir()
{
    return vec3(
            endpoint.x() - startpoint.x(),
            endpoint.y() - startpoint.y(),
            endpoint.z() - startpoint.z());
}

vec3 Capsule::getpoint()
{
    return startpoint;
}

int Capsule::getradius()
{
    return r;
}

vec3 Capsule::getendpoint()
{
    return endpoint;
}

float Capsule::Intersection(Ray *ray)
{
    //If interested in math, see Calc 3 notebook.
    Capsule *cap = this;

    double g1 =
            pow(ray->getdir().x(), 2) + pow(ray->getdir().y(), 2) + pow(ray->getdir().z(), 2);

    double h1 =
            ray->getdir().x() * (-1) * cap->getdir().x() +
            ray->getdir().y() * (-1) * cap->getdir().y() +
            ray->getdir().z() * (-1) * cap->getdir().z();

    double c1 =
            ray->getdir().x() * (cap->getpoint().x() - ray->getpoint().x()) +
            ray->getdir().y() * (cap->getpoint().y() - ray->getpoint().y()) +
            ray->getdir().z() * (cap->getpoint().z() - ray->getpoint().z());

    double g2 =
            -1 * ray->getdir().x() * cap->getdir().x() +
            -1 * ray->getdir().y() * cap->getdir().y() +
            -1 * ray->getdir().z() * cap->getdir().z();

    double h2 =
            pow(cap->getdir().x(), 2) + pow(cap->getdir().y(), 2) + pow(cap->getdir().z(), 2);

    double c2 =
            (-1)*cap->getdir().x() * (cap->getpoint().x() - ray->getpoint().x()) +
            (-1)*cap->getdir().y() * (cap->getpoint().y() - ray->getpoint().y()) +
            (-1)*cap->getdir().z() * (cap->getpoint().z() - ray->getpoint().z());


    double a = (c1 * h2 - c2 * h1) / (g1 * h2 - g2 * h1);
    double b = (c1 * g2 - c2 * g1) / (h1 * g2 - h2 * g1);

    if (b >= 0 && b <= 1)
    {
        double distancesquared =
                pow(ray->getdir().x() * a - cap->getdir().x() * b - cap->getpoint().x() + ray->getpoint().x(), 2) +
                pow(ray->getdir().y() * a - cap->getdir().y() * b - cap->getpoint().y() + ray->getpoint().y(), 2) +
                pow(ray->getdir().z() * a - cap->getdir().z() * b - cap->getpoint().z() + ray->getpoint().z(), 2);

        if (distancesquared < pow(cap->getradius(), 2))
        {
            return static_cast<float>(b);
        }
    }

    else if (b < 0) // this is not true because the capsule can be oriented any way it wants to be and start point will no
        //Actually I may be wrong because b is a time that tells you when you are closest to the start point. (wrong, thats a)
        //b is the time (spot) on the line segment you are at. So < 0 means you are away from the startpoint and the line
    {
        //Find distance to startpoint
        Sphere *startsphere = new Sphere(vec3(
                cap->getpoint().x(),
                cap->getpoint().y(),
                cap->getpoint().z()),
                cap->getradius(),
                cap->getColor());

        return ray->Intersection(startsphere);
    }
    else if (b > 1)
    {
        // Find distance to endpoint
        Sphere *endsphere = new Sphere(vec3(
                cap->getendpoint().x(),
                cap->getendpoint().y(),
                cap->getendpoint().z()),
                cap->getradius(),
                cap->getColor());
        return ray->Intersection(endsphere);
    }

    return 0;
}

Ray Capsule::getReflectionRay(Ray *incomingRay) {
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

vec3 Capsule::getNormal(Ray *incomingRay) {
    //get the t value that the ray intersects the sphere at.
    float t = this->Intersection(incomingRay);

    //get the point on the sphere that this intersection is done.
    vec3 intersectionPoint = incomingRay->getpoint() + incomingRay->getdir()*t;

    //The normal vector is (c-p) where p is the intersection point.
    vec3 sphereNormalVec = this->startpoint - intersectionPoint;

    //Needs to be a unit vector
    sphereNormalVec.make_unit_vector();
    return sphereNormalVec;
}

vec3 Capsule::middle() {
    return (startpoint + endpoint)/2.0;
}

vec3 Capsule::minBoundary() {
    return vec3(
            min(startpoint.x() - r, endpoint.x() - r),
            min(startpoint.y() - r, endpoint.y() - r),
            min(startpoint.z() - r, endpoint.z() - r)
    );
}

vec3 Capsule::maxBoundary() {
    return vec3(
            max(startpoint.x() - r, endpoint.x() - r),
            max(startpoint.y() - r, endpoint.y() - r),
            max(startpoint.z() - r, endpoint.z() - r)
    );
}

