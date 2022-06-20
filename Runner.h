#ifndef RUNNER_H
#define RUNNER_H
#include <iostream>
#include "myString.h"
#include "Commands.h"
#include "Shape.h"
class Runner {
public:
	void run() {
		myString input{ 100 };
	
		Vector<myString> inputVector;
		Vector<Shape*> shapeVector;

		bool openedFile = false;
		myString openedFileName;
		bool changesMade = false;

		printHelp();

		while (true) {
			cout << "> ";
			cin >> input;
			validateInput(input);

			inputVector = input.toVector();

			if (inputVector.getFirst() == "open") {
				if (openedFile) 
					cout << "File "<<char(34)<<openedFileName.getStr()<< char(34) <<" is currently opened!" << '\n'  << '\n';
				 
				else {
					if (inputVector.getSize() < 2) 
						cout << "No filename entered!" << '\n' << '\n';
					
					else {
						openFile(inputVector.getAt(1), shapeVector);

						openedFile = true;
						openedFileName = inputVector.getAt(1);
					}
				}
			}

			else if (inputVector.getFirst() == "close") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					closeFile(shapeVector);
					
					cout << "Successfully closed " << char(34) << openedFileName.getStr() << char(34) << "!" << '\n' << '\n';
					
					openedFile = false;
					openedFileName = "";

					changesMade = false;
				}
			}

			else if (inputVector.getFirst() == "save") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					saveFile(openedFileName, shapeVector);

					cout << "Successfully saved " << char(34) << openedFileName.getStr() << char(34) << "!" << '\n' << '\n';
					
					openedFile = false;
					openedFileName = "";

					changesMade = false;
				}
			}

			else if (inputVector.getFirst() == "saveas") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					saveFile(inputVector.getAt(1), shapeVector);
					
					cout << "Successfully saved as " << char(34) << inputVector.getAt(1).getStr() << char(34) << "!" << '\n' << '\n';
					
					openedFile = false;
					openedFileName = "";

					changesMade = false;
				}
			}

			else if (inputVector.getFirst() == "help") 
				printHelp();
			

			else if (inputVector.getFirst() == "exit") {
				if (changesMade) 
					cout << "You have unsaved changes! Either save them or close the file to exit the app!" << '\n' << '\n';				
				else if (openedFile) 
					cout << "File " << char(34) << openedFileName.getStr() << char(34) << " is currently opened! You must either save or close it before exiting!" << '\n' << '\n';			
				else
					break;
			}

			else if (inputVector.getFirst() == "print") {
				if (!openedFile)
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					if (!shapeVector.isEmpty())
						shapeVector.printWithIndexes();
					else
						cout << "There are no figures!" << '\n' << '\n';
				}
			}

			else if (inputVector.getFirst() == "create") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					createShape(input, shapeVector, changesMade);
					changesMade = true;
				}
			}

			else if (inputVector.getFirst() == "erase") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					erase(inputVector, shapeVector);
					changesMade = true;
				}
			}

			else if (inputVector.getFirst() == "translate") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					translate(inputVector, shapeVector);
					changesMade = true;
				}
			}

			else if (inputVector.getFirst() == "within") {
				if (!openedFile) 
					cout << "There isn't an opened file!" << '\n' << '\n';
				
				else {
					if (inputVector.getSize() < 5) 
						cout << "Invalid input!" << '\n' << '\n';

					else if (input.contains("rectangle")) 
						withinRectangle(inputVector, shapeVector);					
					else if (input.contains("circle")) 
						withinCircle(inputVector, shapeVector);					
				}
			}

			input.empty();
			inputVector.empty();
			
		}


		cout << "Exiting program..."<<'\n';

	}
};
#endif // !RUNNER_H
