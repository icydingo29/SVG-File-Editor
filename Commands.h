#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "myString.h"
#include "Point.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Vector.h"

void writeSVGBeginning(ofstream &fileWrite) {
	fileWrite << "<?xml version=" << char(34) << "1.0" << char(34) << " standalone=" << char(34) << "no" << char(34) << "?>" << endl <<
		"<!DOCTYPE svg PUBLIC " << char(34) << "-//W3C//DTD SVG 1.1//EN" << char(34) << endl
		<< "  " << char(34) << "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd" << char(34) << ">" << endl << "<svg>" << endl;
}

void writeSVGEnd(ofstream& fileWrite) {
	fileWrite << "</svg>" << endl; 
}

void checkIfOpenedCorrectly(std::ofstream& o) {
	if (!o.is_open()) {
		cout << "File was not opened successfully";
		throw;
	}
}

void checkIfOpenedCorrectly(std::ifstream& i) {
	if (!i.is_open()) {
		cout << "File was not opened successfully";
		throw;
	}
}

void validateInput(myString& input) {
	input.removeConsecutiveSpaces();
	input.pushBack(' ');
	if (input.getLength() > 1) {
		input.popBack();
	}
	if (input.getLength() != 1 && input.getStr()[input.getLength() - 1] == ' ') {
		input.popBack();
	}
}

void openFile(myString fileName, Vector<Shape*> &shapeVector) {
	ifstream fileRead(fileName.getStr(), ios::app);
	checkIfOpenedCorrectly(fileRead);
	fileRead.seekg(0, ios::end);


	if (fileRead.tellg() == 0) {
		cout << "No file with such name found, new one created!" << '\n' << '\n';
		fileRead.close();

		ofstream fileWrite(fileName.getStr(), ios::app);
		checkIfOpenedCorrectly(fileWrite);

		writeSVGBeginning(fileWrite);
		writeSVGEnd(fileWrite);

		fileWrite.close();
		return;
	}
	else {
		fileRead.seekg(0, ios::beg);
		cout << "File "<<char(34) << fileName.getStr() << char(34) << " opened!" << '\n' << '\n';

		myString readString;
		char line[120];

		Rectangle rect{ 1,1,1,1,"red" };
		Circle circle(1, 1, 1, "red");
		Line lineObj(1, 1, 1, 1, "red");

		for (size_t i = 0;; i++){	
			fileRead.getline(line, 120);
			readString = line;

			if (readString.contains("</svg>"))
				break;
			else if (readString.contains("<rect")) {
				rect.loadValuesFromFile(readString);
				shapeVector.pushBack(rect.clone());
			}
			else if (readString.contains("<circle")) {
				circle.loadValuesFromFile(readString);
				shapeVector.pushBack(circle.clone());
			}
			else if (readString.contains("<line")) {
				lineObj.loadValuesFromFile(readString);
				shapeVector.pushBack(lineObj.clone());
			}
		}

		fileRead.close();
	}

}

void closeFile(Vector<Shape*>& shapeVector) {
	shapeVector.empty();
}

void saveFile(myString fileName, Vector<Shape*>& shapeVector) {
	ofstream fileWrite(fileName.getStr());
	checkIfOpenedCorrectly(fileWrite);

	writeSVGBeginning(fileWrite);
	for (size_t i = 0; i < shapeVector.getSize(); i++){
		//fileWrite<<shapeVector.getAt(i);
		//shapeVector.getAt(i)->writeValuesToFile(fileWrite);//kogato beshe ostream a ne ofstream
		shapeVector.getAt(i)->writeValuesToFile(fileWrite);
	}
	writeSVGEnd(fileWrite);
	fileWrite.close();

	shapeVector.empty();
}

void printHelp() {
	cout << "The following commands are supported:" << '\n';
	cout << "open <file>	     opens <file>" << '\n';
	cout << "close                closes currently opened file" << '\n';
	cout << "save                 saves the currently open file" << '\n';
	cout << "saveas <file>        saves the currently open file in <file>" << '\n';
	cout << "help                 prints this information" << '\n';
	cout << "exit                 exits the program" << '\n' << '\n';
}

void createShape(myString input, Vector<Shape*>& shapeVector, bool changesMade) {
	//list of possible shapes
	Rectangle rec{ 1, 1, 1, 1, "validation" };
	Circle circle{ 1, 1, 1, "validation" };
	Line line{ 1, 1, 1, 1, "validation" };

	if (input.contains("rectangle")) {
		bool validValues = true;
		rec.loadValues(input, validValues);

		if (validValues) {
			shapeVector.pushBack(rec.clone());
			changesMade = true;

			cout << "Rectangle added!" << '\n' << '\n';
		}
	}

	else if (input.contains("circle")) {
		bool validValues = true;
		circle.loadValues(input, validValues);
		if (validValues) {
			shapeVector.pushBack(circle.clone());
			changesMade = true;

			cout << "Circle added!" << '\n' << '\n';
		}
	}

	else if (input.contains("line")) {
		bool validValues = true;
		line.loadValues(input, validValues);
		if (validValues) {
			shapeVector.pushBack(line.clone());
			changesMade = true;

			cout << "Line added!" << '\n' << '\n';
		}
	}
}

void erase(Vector<myString> inputVector, Vector<Shape*>& shapeVector) {
	if (inputVector.getSize() < 2) {
		cout << "No index entered!" << '\n' << '\n';
	}
	else if (shapeVector.isEmpty()) {
		cout << "There are no shapes to be erased! " << '\n' << '\n';
	}
	else if (inputVector.getAt(1).toInt() < 1 || inputVector.getAt(1).toInt() > shapeVector.getSize()) {
		cout << "There is no figure number " << inputVector.getAt(1).getStr() << "!" << '\n' << '\n';
	}
	else {
		shapeVector.removeAt(inputVector.getAt(1).toInt() - 1);
		cout << "Figure number " << inputVector.getAt(1).toInt() << " erased!" << '\n' << '\n';
	}
}

void translate(Vector<myString> inputVector, Vector<Shape*>& shapeVector) {
	int indexOfShapeToBeTranslated = 0;
	bool translateAll = true;

	if (inputVector.getSize() < 3) {
		cout << "Invalid input!" << '\n' << '\n';
		return;
	}

	if (inputVector.getAt(1).toInt() != -1) {
		indexOfShapeToBeTranslated = inputVector.getAt(1).toInt();
		translateAll = false;
	}

	if (translateAll == false && (indexOfShapeToBeTranslated<1 || indexOfShapeToBeTranslated > shapeVector.getSize())) {
		cout << "There is no figure number " << indexOfShapeToBeTranslated << "!" << '\n' << '\n';
	}
	else {
		int verticalTr = 0, horizontalTr = 0;

		for (size_t i = 0; i < inputVector.getSize(); i++) {
			if (inputVector.getAt(i).contains("vertical")) {
				verticalTr = inputVector.getAt(i).getIntFromWord();
			}

			if (inputVector.getAt(i).contains("horizontal")) {
				horizontalTr = inputVector.getAt(i).getIntFromWord();
			}
		}

		if (translateAll == true) {
			for (size_t i = 0; i < shapeVector.getSize(); i++) {
				shapeVector.getAt(i)->translate(horizontalTr, verticalTr);
			}
			cout << "All figures translated!" << '\n' << '\n';
		}
		else {
			shapeVector.getAt(indexOfShapeToBeTranslated - 1)->translate(horizontalTr, verticalTr);
			cout << "Figure number " << indexOfShapeToBeTranslated << " translated!" << '\n' << '\n';
		}
	}
}

void withinRectangle(Vector<myString> inputVector, Vector<Shape*>& shapeVector) {
	if (inputVector.getSize()<6) {
		cout << "Invalid input!" << '\n' << '\n';
		return;
	}

	int numbers[] = { 0, 0, 0, 0 };

	for (size_t i = 2; i < 6; i++) {
		numbers[i - 2] = inputVector.getAt(i).toInt();
	}

	int counter = 1;
	bool noFiguresWithin = true;

	for (size_t i = 0; i < shapeVector.getSize(); i++) {
		if (shapeVector.getAt(i)->isWithinRectangle(numbers[0], numbers[1], numbers[2], numbers[3])) {
			noFiguresWithin = false;
			cout << counter << ". ";
			shapeVector.getAt(i)->print();
			counter++;
		}

	}

	if (noFiguresWithin) {
		cout << "No figures are located within rectangle ";
		for (size_t i = 0; i < 4; i++) {
			cout << numbers[i] << " ";
		}
	}
	cout << '\n' << '\n';
}

void withinCircle(Vector<myString> inputVector, Vector<Shape*>& shapeVector) {
	if (inputVector.getSize() < 5) {
		cout << "Invalid input!" << '\n' << '\n';
		return;
	}

	int numbers[] = { 0, 0, 0 };

	for (size_t i = 2; i < 5; i++) {
		numbers[i - 2] = inputVector.getAt(i).toInt();
	}

	int counter = 1;
	bool noFiguresWithin = true;

	for (size_t i = 0; i < shapeVector.getSize(); i++) {
		if (shapeVector.getAt(i)->isWithinCircle(numbers[0], numbers[1], numbers[2])) {
			noFiguresWithin = false;
			cout << counter << ". ";
			shapeVector.getAt(i)->print();
			counter++;
		}

	}

	if (noFiguresWithin) {
		cout << "No figures are located within circle ";
		for (size_t i = 0; i < 3; i++) {
			cout << numbers[i] << " ";
		}
	}
	cout << '\n' << '\n';
}