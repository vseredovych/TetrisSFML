#pragma once
class Point
{
private:
	int x;
	int y;
public:
	Point();
	Point(int x, int y);
	Point(const Point & point);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	bool operator==(Point &other)
	{
		if ((this->x) == (other.getX()) && (this->y) == (other.getY()))
		{
			return true;
		}
		return false;
	}
	void Print();
};