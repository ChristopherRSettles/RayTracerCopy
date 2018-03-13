//
// Created by Chris on 3/1/2018.
//

#include <cmath>
#include "Direction.h"

Direction::Direction(double inputx, double inputy, double inputz)
{
    x = inputx;
    y = inputy;
    z = inputz;
}
Direction Direction::operator+(Direction d2)
// Calls the + function using the instance of the left operand
// Which is why I can just use getx() and not d1.getx() or left.getx()
{
    Direction newdirection(getx() + d2.getx(), gety() + d2.gety(), getz() + d2.getz());
    return newdirection;
}

/**
 * Calls the + function using the instance of the left operand
 * Which is why I can just use getx() and not d1.getx() or left.getx()
 * @param d2 The second direction that we are subtracting
 * @return
 */
Direction Direction::operator-(Direction d2)
{
    Direction newdirection(getx() - d2.getx(), gety() - d2.gety(), getz() - d2.getz());
    return newdirection;
}
Direction Direction::operator-()
// Calls the + function using the instance of the left operand
// Which is why I can just use getx() and not d1.getx() or left.getx()
{
    Direction newdirection(-getx(),-gety(), -getz());
    return newdirection;
}

double Direction::getx()
{
    return x;
}
double Direction::gety()
{
    return y;
}
double Direction::getz()
{
    return z;
}

Direction Direction::normalize() {
    double magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    return Direction(x/magnitude, y/magnitude, z/magnitude);
}

Direction Direction::operator*(double scale) {
    return Direction(x*scale, y*scale, z*scale);
}
