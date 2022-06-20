#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include "Vector.h"
using namespace std;

class myString {
private:
    int length;
    char* str;

public:
    //big 3 (4)
    myString();
    myString(myString const& myStringParam);
    myString& operator=(myString const& myStringParam);
    ~myString();

    //additional constructors
    myString(const char* strParam);
    myString(unsigned short size);

    //overloaded operators
    friend std::istream& operator>>(std::istream& i, myString& myStringParam);
    friend std::ostream& operator<<(std::ostream& o, myString& myStringParam);//
    myString& operator=(const char* strParam);
    bool operator==(myString const& myStringParam);
    bool operator==(const char* strParam);
    myString* operator->();

    //getters
    int getLength();
    char* getStr();
    myString getFirstWord();
    myString getLastWord();
    int getIntFromWord();

    //toDatatype functions
    Vector<myString> toVector();
    int toInt();

    //other functions
    void concat(const char* strParam);
    void concat(myString const& strParam);
    void concat(int numParam);

    void pushBack(const char& letter);
    void popBack();

    void toLowerCase();
    void toUpperCase();

    void extendLengthTo(unsigned short size);
    void removeSpacesAtBeginning();
    void removeConsecutiveSpaces();
    void reverse();
    bool contains(myString const& strParam);
    void empty();
    void print();
};

#endif // !1