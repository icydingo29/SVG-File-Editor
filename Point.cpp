#include <iostream>
#include "Point.h"

Point::Point() { x = y = 0; }

Point::Point(int xParam, int yParam) : x(xParam), y(yParam) {}

void Point::setX(int xParam) { x = xParam; }

void Point::setY(int yParam) { y = yParam; }

int Point::getX() { return x; }

int Point::getY() { return y; }

Point& Point::operator=(Point const& pointParam) {
	if (this!=&pointParam) {
		this->x = pointParam.x;
		this->y = pointParam.y;
	}
	return *this;
}

bool Point::operator==(Point const& pointParam) {
	return (this->x == pointParam.x && this->y == pointParam.y);
}

bool Point::operator>=(Point const& pointParam) {
	return (this->x >= pointParam.x && this->y >= pointParam.y); //&&
}

bool Point::operator<=(Point const& pointParam) {
	return (this->x <= pointParam.x && this->y <= pointParam.y); //&&
}

void Point::print() {
	std::cout << "X is " << this->getX() << " and Y is " << this->getY() << '\n' << '\n';
}