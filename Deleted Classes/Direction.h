//
// Created by Chris on 3/1/2018.
//

#ifndef RAYTRACERCOPY_DIRECTION_H
#define RAYTRACERCOPY_DIRECTION_H

class Direction
{

private:
	double x, y, z;

public:
	Direction(double, double, double);
	Direction operator+(Direction);
	Direction operator-(Direction);
	Direction operator-();
	Direction operator*(double scale);
	double getx();
	double gety();
	double getz();

	Direction normalize();
};


#endif //RAYTRACERCOPY_DIRECTION_H
