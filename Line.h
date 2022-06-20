#ifndef LINE_H
#define LINE_H
#include "Shape.h"
#include "myString.h"
#include "Point.h"
class Line : public Shape {
private:
	Point secondPoint;
public:
	Line(int x1, int y1, int x2, int y2, myString fillParam) : Shape(x1, y1, fillParam), secondPoint(x2, y2) {};

	Shape* clone() override {
		return new Line(*this);
	}

	void loadValuesFromFile(myString str) override {
		Vector<myString> inputVector = str.toVector();
		this->startingPoint.setX(inputVector.getAt(3).getIntFromWord());
		this->startingPoint.setY(inputVector.getAt(4).getIntFromWord());
		this->secondPoint.setX(inputVector.getAt(5).getIntFromWord());
		this->secondPoint.setX(inputVector.getAt(6).getIntFromWord());

		myString colour;
		for (size_t i = 0; i < str.getLength(); i++)
		{
			if (str.getStr()[i] == 's' && str.getStr()[i + 1] == 't' && str.getStr()[i + 2] == 'r' && str.getStr()[i + 3] == 'o' && str.getStr()[i + 4] == 'k' && str.getStr()[i + 5] == 'e') {
				i += 8;
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
		if (inputVector.getSize() < 7) {
			cout << "Invalid input!" << '\n' << '\n';
			validValues = false;
			return;
		}

		this->startingPoint.setX(inputVector.getAt(2).toInt());
		this->startingPoint.setY(inputVector.getAt(3).toInt());
		this->secondPoint.setX(inputVector.getAt(4).toInt());
		this->secondPoint.setY(inputVector.getAt(5).toInt());
		this->fill = colour;
		validValues = true;
	}

	std::ostream& writeValuesToFile(std::ostream& o) override {
		return o << "  <line x1=" << char(34) << this->startingPoint.getX() << char(34) << " y1=" << char(34) << this->startingPoint.getY() << char(34) << " x2=" << char(34) << this->secondPoint.getX() << char(34) << " y2=" << char(34) << this->secondPoint.getY() << char(34) << " stroke=" << char(34) << this->fill << char(34) << " />" << '\n';
	}

	void translate(int x, int y) override {
		this->startingPoint.setX(this->startingPoint.getX() + x);
		this->startingPoint.setY(this->startingPoint.getY() + y);
	}

	bool isWithinRectangle(int xP, int yP, int widthP, int heightP) override {
		//Points of the rectangle, that possibly contains this line
		Point tL(xP, yP), tR(xP + widthP, yP), bL(xP, yP + heightP), bR(xP + widthP, yP + heightP);

		if (tL.getX() <= startingPoint.getX() && tL.getY() <= startingPoint.getY() &&
			bR.getX() >= startingPoint.getX() && bR.getY() >= startingPoint.getX() &&
			tL.getX() <= secondPoint.getX() && tL.getY() <= secondPoint.getY() &&
			bR.getX() >= secondPoint.getX() && bR.getY() >= secondPoint.getX())
			return true;

		return false;
	}

	void print() override {
		cout << "line " << startingPoint.getX() << " " << startingPoint.getY() << " " << secondPoint.getX() << " " << secondPoint.getY() << " " << fill << endl;
	}

};
#endif // !LINE_H
