#include <iostream>
#include "Point.h"
using namespace std;

Point::Point() : Point(0, 0) {};
Point::Point(int x, int y)
{
	setX(x);
	setY(y);
}
Point::Point(const Point & point) : Point(point.x, point.y) {};

int Point::getX()
{
	return x;
}
int Point::getY()
{
	return y;
}
void Point::setX(int x)
{
	this->x = x;
}
void Point::setY(int y)
{
	this->y = y;
}
void Point::Print()
{
	cout << "(" << x << ",  " << y << ")";
}