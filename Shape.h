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

	virtual void print() = 0;
	//friend std::ostream& operator<<(std::ostream& o, Shape* shapeParam) { return o<<shapeParam->startingPoint.getX()<< shapeParam->startingPoint.getY() << shapeParam->fill<<'\n'; };
};
#endif // !_SHAPE_H_
