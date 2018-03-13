//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_POINT_H
#define RAYTRACERCOPY_POINT_H

//Christopher Settles
#include <math.h>
#include "Direction.h"

class Point
{

private:
    double x, y, z;

public:

    Point(double, double, double);
    double getx();
    double gety();
    double getz();
    void setx(int);
    void sety(int);
    void setz(int);
    double squaredDistance(Point &p);
    Point operator+(Direction);
};

#endif //RAYTRACERCOPY_POINT_H
