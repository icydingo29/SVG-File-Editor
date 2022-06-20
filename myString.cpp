#include "myString.h"
#include <cstring>

myString::myString() {
    str = new char[1];
    str[0] = '\0';
    length = 0;
}

myString::myString(const char* strParam) {
    str = new char[strlen(strParam) + 1];
    strcpy_s(str, strlen(strParam) + 1, strParam);
    length = strlen(str);
}

myString::myString(myString const& myStringParam) {
    char* tempString = new char[myStringParam.length + 2];
    for (size_t i = 0; i < myStringParam.length + 1; i++) {
        tempString[i] = myStringParam.str[i];
    }
    tempString[myStringParam.length + 1] = '\0';

    str = tempString;
    length = myStringParam.length;
}

myString::myString(unsigned short size) {
    char* tempString = new char[size + 1];
    for (size_t i = 0; i < size + 1; i++) {
        tempString[i] = ' ';
    }
    str = tempString;
    length = size;
}

myString& myString::operator=(myString const& myStringParam) {
    if (this != &myStringParam) {
        char* tempString = new char[myStringParam.length + 2];
        for (size_t i = 0; i < myStringParam.length + 1; i++) {
            tempString[i] = myStringParam.str[i];
        }
        tempString[myStringParam.length + 1] = '\0';

        delete[] str;
        str = tempString;
        length = myStringParam.length;
    }

    return *this;
}

myString& myString::operator=(const char* strParam) {
    if (strcmp(this->str, strParam) != 0) {
        myString temp{ strParam };
        this->operator=(temp);
    }
    return *this;
}

myString::~myString() {
    delete[] str;
}


void myString::pushBack(const char& letter) {
    char* tempString = new char[length + 2];
    for (size_t i = 0; i < length; i++) {
        tempString[i] = str[i];
    }
    tempString[length] = letter;
    tempString[length + 1] = '\0';

    delete[] str;
    str = tempString;
    length++;
}

void myString::popBack() {
    char* tempString = new char[length];
    for (size_t i = 0; i < length - 1; i++)
    {
        tempString[i] = str[i];
    }
    tempString[length - 1] = '\0';
    delete[] str;
    str = tempString;
    length--;
}

void myString::concat(const char* strParam) {
    char* tempString = new char[length + strlen(strParam) + 1];
    for (size_t i = 0; i < length; i++)
    {
        tempString[i] = str[i];
    }
    int j = 0;
    for (size_t i = length; i < strlen(tempString); i++)
    {
        tempString[i] = strParam[j++];
    }
    tempString[strlen(tempString)] = '\0';

    delete[] str;
    str = tempString;
    length = strlen(tempString);
}

void myString::concat(myString const& strParam) {
    this->concat(strParam.str);
}

void myString::concat(int numParam) {
    int numParamCopy = numParam;
    int counter = 0;
    while (numParamCopy > 0) {
        numParamCopy /= 10;
        counter++;
    }

    int* arrInt = new int[counter];
    int j = 0;
    while (numParam > 0) {
        arrInt[j] = numParam % 10;
        numParam /= 10;
        j++;
    }

    char* arrChar = new char[counter + 1];
    for (size_t i = 0; i < counter; i++)
    {
        arrChar[i] = arrInt[counter - i - 1] + 48;

    }
    arrChar[counter] = '\0';

    this->concat(arrChar);
    delete[] arrInt;
    delete[] arrChar;
}

void myString::empty() {
    delete[] str;
    str = new char[1];
    str[0] = '\0';
    length = 0;

}

void myString::print() {
    for (size_t i = 0; i < length; i++)
    {
        std::cout << str[i];
    }
    cout << '\n';
}

int myString::getLength() {
    return length;
}

char* myString::getStr() {
    return str;
}

std::istream& operator>>(std::istream& i, myString& myStringParam) {
    //new code
    myStringParam.extendLengthTo(200);
    //end of new code
    //i >> myStringParam.str;
    i.getline(myStringParam.str, 200);

    if (myStringParam == '\n' || myStringParam=='\0')//
        myStringParam = "";//

    myStringParam.length = strlen(myStringParam.str);


    return i;
}

std::ostream& operator<<(std::ostream& o, myString& myStringParam) {
    return o << myStringParam.str;
}

bool myString::operator==(const char* strParam) {
    if (strcmp(this->str, strParam) == 0)
        return true;

    return false;
}

bool myString::operator==(myString const& myStringParam) {
    if (strcmp(this->str, myStringParam.str) == 0)
        return true;

    return false;
}

myString* myString::operator->() {
    return this;
}

void myString::toLowerCase() {
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

void myString::toUpperCase() {
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void myString::extendLengthTo(unsigned short size) {
    if (length >= size)
        return;

    char* tempStr = new char[size + 1];
    for (size_t i = 0; i < length; i++)
    {
        tempStr[i] = str[i];
    }
    for (size_t i = length; i < size; i++)
    {
        tempStr[i] = ' ';
    }
    tempStr[size] = '\0';
    delete[] str;
    str = tempStr;
    length = size;
}

void myString::removeSpacesAtBeginning() {
    char* temp = new char[this->length + 1];
    strcpy_s(temp, this->length + 1, str);

    short int counterOfSpaces = 0;
    for (size_t i = 0; i < length; i++) {
        if (temp[i] == ' ') {
            if (temp[i + 1] == ' ')
                counterOfSpaces++;
            else if (temp[i + 1] != ' ')
                break;
        }
        else
            break;

    }
    //
    counterOfSpaces++;

    if (counterOfSpaces == 1 && temp[0] != ' ') {
        delete[] temp;
        return;
    }

    char* resultTemp = new char[this->length - counterOfSpaces + 1];
    int j = 0;
    for (size_t i = counterOfSpaces; i < this->length; i++)
    {
        resultTemp[j] = temp[i];
        j++;
    }

    delete[] temp;
    resultTemp[this->length - counterOfSpaces] = '\0';
    this->str = resultTemp;
    this->length -= counterOfSpaces;

}

bool myString::contains(myString const& strParam) {

    if (this->length < strParam.length)
        return false;

    short int strParamIndex = 0;
    for (size_t i = 0; i < this->length - strParam.length + 1; i++)
    {
        if (this->str[i] == strParam.str[strParamIndex]) {
            for (size_t j = 1; j < strParam.length; j++)
            {

                if (this->str[i + j] != strParam.str[strParamIndex + j])
                    break;

                if (j == strParam.length - 1 && this->str[i + j] == strParam.str[strParamIndex + j])
                    return true;
            }
        }
        strParamIndex = 0;
    }

    return false;
}

Vector<myString> myString::toVector() {
    Vector<myString> result;
    myString word;
    for (size_t i = 0; i < this->length; i++)
    {
        if (str[i + 1] == '\0') {
            word.pushBack(str[i]);
            result.pushBack(word);
            word.empty();
            break;
        }
        else if (str[i] != ' ') {
            word.pushBack(str[i]);
        }
        else {
            result.pushBack(word);
            word.empty();
        }
    }
    return result;
}

myString myString::getFirstWord() {
    myString result;
    for (size_t i = 0; i < length; i++)
    {
        if (!(this->str[i] == '\0' || this->str[i] == ' ')) {
            result.pushBack(this->str[i]);
        }
        else
            break;
    }

    return result;
}

int myString::toInt() {
    for (size_t i = 0; i < length; i++)
    {
        if (!(str[i] > 47 && str[i] < 58))
            return -1;        
    }

    int result = 0;
    for (size_t i = 0; i < length; i++)
    {
        result += ((int)str[i] - 48) * pow(10, length-i-1);
    }
    
    return result;
}


myString myString::getLastWord() {
    myString result;
    bool isChanged = false;
    for (size_t i = this->length - 1; i > 0; i--)
    {
        if (this->str[i] == ' ') {
            break;
        }
        else {
            result.pushBack(str[i]);
            isChanged = true;
        }
    }

    result.reverse();
    if (isChanged == false)
        result = "-1";

    return result;
}

void myString::reverse() {
    int j = length - 1;
    for (size_t i = 0; i < length/2; i++)
    {
        swap(str[i], str[j]);
        j--;
    }
}

int myString::getIntFromWord() {
    int num = 0;
    myString numToBe;

    for (size_t i = 0; i < length; i++) {

        if (str[i] > 47 && str[i] < 58) {
            numToBe.pushBack(str[i]);

            i++;
            while (true) {
                if (!(str[i] > 47 && str[i] < 58)) {//
                    break;
                }
                else {
                    if (str[i] == '\0')
                        break;

                    numToBe.pushBack(str[i]);//
                    i++;//
                }
            }

            num = numToBe.toInt();
            return num;
        }

        //return num;

    }
}

void myString::removeConsecutiveSpaces() {
    myString result;
    for (size_t i = 0; i < length; i++)
    {
        if (this->str[i] != ' ')
            result.pushBack(this->str[i]);
        else {
            if (this->str[i + 1] != ' ')
                result.pushBack(this->str[i]);
        }
    }

    *this = result;
}