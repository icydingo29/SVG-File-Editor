#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include "myString.h"
using namespace std;
class Shape {
protected:
	Point startingPoint;
	myString fill;
public:
	//constructors
	Shape(int x, int y, myString fillParam) :startingPoint(x, y), fill(fillParam) {};
	virtual Shape* clone() = 0;

	//input&output
	virtual void loadValuesFromFile(myString str) = 0;
	virtual void loadValues(myString str, bool &validValues) = 0;
	virtual std::ostream& writeValuesToFile(std::ostream& o) { return o << ""; };
	
	//other
	virtual bool isWithinRectangle(int xP, int yP, int widthP, int heightP) = 0;
	virtual bool isWithinCircle(int xP, int yP, int radiusP) = 0;
	virtual void translate(int x, int y) = 0;

	bool isValidColour(myString colour) {
		if (colour.toInt() != -1) 
			return false;

		if (!(colour == "red" || colour == "blue" || colour == "green" || colour == "yellow")) 
			return false;

		return true;
	}

	virtual void print() = 0;
};
#endif // !_SHAPE_H_
