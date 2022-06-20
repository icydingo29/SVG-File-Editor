#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "myString.h"
class Rectangle : public Shape {
private:
	int width, height;
public:
	Rectangle(int x, int y, int widthParam, int heightParam, myString fillParam) : 
		Shape(x, y, fillParam), width(widthParam), height(heightParam) {};

	Shape* clone() override {
		return new Rectangle(*this);
	}

	void loadValuesFromFile(myString str) override {
		myString colour;
		int numbers[] = { 0, 0, 0, 0 };
		int numbersIndex = 0;

		int num = 0;
		myString numToBe;

		for (size_t i = 0; i < str.getLength(); i++) {

			if (str.getStr()[i] > 47 && str.getStr()[i] < 58) {
				numToBe.pushBack(str.getStr()[i]);
				
				i++;
				while (true) {
					if (!(str.getStr()[i] > 47 && str.getStr()[i] < 58)) {
						break;
					}
					else {
						numToBe.pushBack(str.getStr()[i]);
						i++;
					}
				}

				num = numToBe.toInt();
				numToBe.empty();

				numbers[numbersIndex] = num;
				numbersIndex++;
			}
			else if (str.getStr()[i] == 'f' && str.getStr()[i + 1] == 'i' && str.getStr()[i+2] == 'l' && str.getStr()[i + 3] == 'l') {
				i += 6;
				while (true) {
					if (str.getStr()[i] != char(34)) {
						colour.pushBack(str.getStr()[i]);
						i++;
					}
					else {
						break;
					}
				}

			}

		}

		this->startingPoint.setX(numbers[0]);
		this->startingPoint.setY(numbers[1]);
		this->width = numbers[2];
		this->height = numbers[3];
		this->fill = colour;
	}

	void loadValues(myString str, bool &validValues) override {
		//here we change all minuses to empty spaces
		for (size_t i = 0; i < str.getLength(); i++){
			if (str.getStr()[i] == '-')
				str.getStr()[i] = ' ';
		}

		//removing consecutive spaces
		str.removeConsecutiveSpaces();

		//we enter the colour first for validation purposes//blue red green yellow purple
		myString colour;
		colour = str.getLastWord();
		if (colour.toInt() != -1) {
			cout << "Invalid or no fill entered!" << '\n' << '\n';
			validValues = false;
			return;
		}

		if (!(colour == "red" || colour == "blue" || colour == "green" || colour == "yellow")) {
			cout << "Invalid fill entered!" << '\n' << '\n';
			validValues = false;
			return;
		}

		Vector<myString> inputVector = str.toVector();
		if (inputVector.getSize() < 7) {
			cout<<"Invalid input!" << '\n' << '\n';
			validValues = false;
			return;
		}

		this->startingPoint.setX(inputVector.getAt(2).toInt());
		this->startingPoint.setY(inputVector.getAt(3).toInt());
		this->width = inputVector.getAt(4).toInt();
		this->height = inputVector.getAt(5).toInt();
		this->fill = colour;
		validValues = true;
	}

	std::ostream& writeValuesToFile(std::ostream& o) override {
		 return o << "  <rect x=" << char(34) << this->startingPoint.getX() <<char(34)
			 << " y=" << char(34) << this->startingPoint.getY() <<char(34)<< " width=" << char(34) 
			 << this->width << char(34) << " height=" << char(34) << this->height << char(34) 
			 << " fill=" << char(34) << this->fill<<char(34) << " />"<<'\n';
	}

	void translate(int x, int y) override {
		this->startingPoint.setX(this->startingPoint.getX() + x);
		this->startingPoint.setY(this->startingPoint.getY() + y);
	}

	bool isWithinRectangle(int xP, int yP, int widthP, int heightP) override {
		//Points of this rectangle
		Point topLeft(this->startingPoint.getX(), this->startingPoint.getY());
		Point topRight(this->startingPoint.getX() + width, this->startingPoint.getY());
		Point bottomLeft(this->startingPoint.getX(), this->startingPoint.getY() + height);
		Point bottomRight(this->startingPoint.getX() + width, this->startingPoint.getY() + height);

		//Points of the rectangle, that possibly contains this one
		Point tL(xP, yP), tR(xP + widthP, yP), bL(xP, yP + heightP), bR(xP + widthP, yP + heightP);

		if (tL.getX() <= topLeft.getX() && tL.getY() <= topLeft.getY() &&
			tR.getX() >= topRight.getX() && tR.getY() <= topRight.getY() &&
			bL.getX() <= bottomLeft.getX() && bL.getY() >= bottomLeft.getY() &&
			bR.getX() >= bottomRight.getX() && bR.getY() >= bottomRight.getX())
			return true;

		return false;
	}

	bool isWithinCircle(int xP, int yP, int radiusP) override {
		//Points of this rectangle
		Point topLeft(this->startingPoint.getX(), this->startingPoint.getY());
		Point topRight(this->startingPoint.getX() + width, this->startingPoint.getY());
		Point bottomLeft(this->startingPoint.getX(), this->startingPoint.getY() + height);
		Point bottomRight(this->startingPoint.getX() + width, this->startingPoint.getY() + height);

		//checking for each individual point
		if (!((topLeft.getX() - xP) * (topLeft.getX() - xP) + ((topLeft.getY() - yP) * (topLeft.getY() - yP))
			<= radiusP * radiusP))
			return false;

		if (!((topRight.getX() - xP) * (topRight.getX() - xP) + ((topRight.getY() - yP) * (topRight.getY() - yP))
			<= radiusP * radiusP))
			return false;

		if (!((bottomLeft.getX() - xP) * (bottomLeft.getX() - xP) + ((bottomLeft.getY() - yP) * (bottomLeft.getY() - yP))
			<= radiusP * radiusP))
			return false;

		if (!((bottomRight.getX() - xP) * (bottomRight.getX() - xP) + ((bottomRight.getY() - yP) * (bottomRight.getY() - yP))
			<= radiusP * radiusP))
			return false;

		return true;
	}

	void print() override {
		cout << "rectangle " << startingPoint.getX() << " " << startingPoint.getY() 
			 << " " << width << " " << height << " " << fill << endl;
	}
};

#endif // !RECTANGLE_H
