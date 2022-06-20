#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "myString.h"
#include <cmath>
class Circle : public Shape {
private:
	int radius;
public:
	Circle(int x, int y, int radiusParam, myString fillParam) : 
		Shape(x, y, fillParam), radius(radiusParam) {};

	Shape* clone() override {
		return new Circle(*this);
	}

	void loadValuesFromFile(myString str) override {
		Vector<myString> inputVector = str.toVector();
		this->startingPoint.setX(inputVector.getAt(3).getIntFromWord());
		this->startingPoint.setY(inputVector.getAt(4).getIntFromWord());
		this->radius = inputVector.getAt(5).getIntFromWord();

		myString colour;
		for (size_t i = 0; i < str.getLength(); i++) {
			if (str.getStr()[i] == 'f' && str.getStr()[i + 1] == 'i' && str.getStr()[i + 2] == 'l' && str.getStr()[i + 3] == 'l') {
				i += 6;
				while (true) {
					if (str.getStr()[i] != char(34)) {
						colour.pushBack(str.getStr()[i]);
						i++;
					}
					else 
						break;
				}
			}

		}
		this->fill = colour;
	}

	void loadValues(myString str, bool& validValues) override {
		//here we change all minuses to empty spaces
		for (size_t i = 0; i < str.getLength(); i++) {
			if (str.getStr()[i] == '-')
				str.getStr()[i] = ' ';
		}

		str.removeConsecutiveSpaces();

		//we enter the colour first for validation purposes//blue red green yellow purple
		myString colour;
		colour = str.getLastWord();
		if (colour.toInt() != -1) {
			cout << "Invalid or no fill entered!" << '\n' << '\n';
			validValues = false;
			return;
		}

		Vector<myString> inputVector = str.toVector();
		if (inputVector.getSize() < 6) {
			cout << "Invalid input!" << '\n' << '\n';
			validValues = false;
			return;
		}

		this->startingPoint.setX(inputVector.getAt(2).toInt());
		this->startingPoint.setY(inputVector.getAt(3).toInt());
		this->radius = inputVector.getAt(4).toInt();
		this->fill = colour;
		validValues = true;
	}

	std::ostream& writeValuesToFile(std::ostream& o) override {
		return o << "  <circle cx=" << char(34) << this->startingPoint.getX() << char(34) 
			<<" cy=" << char(34) << this->startingPoint.getY() << char(34) << " r=" << char(34)
			<<this->radius << char(34) << " fill=" << char(34) << this->fill << char(34) << " />" << '\n';
	}

	void translate(int x, int y) override {
		this->startingPoint.setX(this->startingPoint.getX() + x);
		this->startingPoint.setY(this->startingPoint.getY() + y);
	}

	bool isWithinRectangle(int xP, int yP, int widthP, int heightP) override {
		//Points of the rectangle, that possibly contains this cirlce
		Point tL(xP, yP), tR(xP + widthP, yP), bL(xP, yP + heightP), bR(xP + widthP, yP + heightP);

		//centre of this circle
		Point centre(this->startingPoint.getX(), this->startingPoint.getY());
		return (centre.getX() <= bR.getX() - radius && centre.getY() <= bR.getY() - radius &&
			    centre.getX() >= tL.getX() - radius && centre.getY() >= tL.getY() - radius);
	}

	bool isWithinCircle(int xP, int yP, int radiusP) override {
		int distance = sqrt(((xP - this->startingPoint.getX()) * (xP - this->startingPoint.getX())) + ((yP - this->startingPoint.getY()) * (yP - this->startingPoint.getY())));

		if (distance + this->radius <= radiusP)
			return true;

		return false;
	}

	void print() override {
		cout << "circle " << startingPoint.getX() << " " << startingPoint.getY() << " " << radius << " " << fill << endl;
	}
};

#endif // !CIRCLE_H