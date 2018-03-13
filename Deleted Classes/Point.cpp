//
// Created by Chris on 3/1/2018.
//
#pragma once
#include "Point.h"

Point::Point(double inputx, double inputy, double inputz)
{
    x = inputx;
    y = inputy;
    z = inputz;
}

double Point::getx()
{
    return x;
}

double Point::gety()
{
    return y;
}

double Point::getz()
{
    return z;
}

void Point::setx(int _x)
{
    x = _x;
}

void Point::sety(int _y)
{
    y = _y;
}

void Point::setz(int _z)
{
    z = _z;
}

double Point::squaredDistance(Point &p) {
    return static_cast<float>(pow(this->x - p.x, 2) +
                              pow(this->y - p.y, 2) +
                              pow(this->z - p.z, 2));
}

Point Point::operator+(Direction d) {
    return Point(x + d.getx(), y + d.gety(), z = d.getz());
}
