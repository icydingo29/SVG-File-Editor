#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <exception>
using namespace std;

template <typename T>
class Vector {
private:
    int size;
    int capacity;
    T* vector;

public:
	//big 3(4)
    Vector();//
    Vector(Vector const& vectorParam);//
    ~Vector();//
    Vector& operator=(Vector const& vectorParam);//

	//getters
    bool isEmpty();//
    int getCapacity();//
    int getSize();//
    T getAt(int index);//
    T getFirst();//
    T getLast();//
	T* getArr();

    void assign(int n, T x);//
	void empty();
    void pushBack(T x);//
    void popBack();//
    void removeAt(int i);//
    void print();//
	void printWithIndexes();
};




template <typename T>
Vector<T>::Vector()
{
	size = 0;
	capacity = 1;
	vector = new T[capacity];
}

template <typename T>
Vector<T>::Vector(Vector<T> const& vectorParam) {
	size = 0;
	capacity = 1;
	vector = new T[capacity];

	for (size_t i = 0; i < vectorParam.size; i++)
		this->pushBack(vectorParam.vector[i]);
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] vector;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector const& vectorParam) {
	if (this != &vectorParam) {
		for (size_t i = 0; i < size; i++)
			this->popBack();

		for (size_t i = 0; i < vectorParam.size; i++)
			this->pushBack(vectorParam.vector[i]);
	}

	return *this;
}



template <typename T>
int Vector<T>::getCapacity()
{
	return capacity;
}

template <typename T>
int Vector<T>::getSize()
{
	return size;
}

template <typename T>
bool Vector<T>::isEmpty()
{
	return (size == 0);
}

template <typename T>
T Vector<T>::getAt(int pos)
{
	if (pos > -1 && pos < size && size>0)
		return vector[pos];
	else
		throw;
}

template <typename T>
T Vector<T>::getFirst()
{
	if (size > 0)
		return vector[0];
	else
		throw;
}

template <typename T>
T Vector<T>::getLast()
{
	if (size > 0)
		return vector[size - 1];
	else
		throw;
}

template <typename T>
T* Vector<T>::getArr() {
	return vector;
}

template <typename T>
void Vector<T>::assign(int n, T x)
{
	delete[] vector;

	size = 0;
	capacity = 1;
	vector = new T[capacity];

	for (size_t i = 0; i < n; i++)
		pushBack(x);
}

template <typename T>
void Vector<T>::empty() {
	for (size_t i = 0; i < this->size+5; i++)
		this->popBack();
}

template <typename T>
void Vector<T>::pushBack(T x)
{
	vector[size] = x;
	size++;

	if (size == capacity) {
		capacity *= 2;
		T* newVector = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			newVector[i] = vector[i];
		}

		delete[] vector;
		vector = newVector;
	}
}

template <typename T>
void Vector<T>::popBack()
{
	if (isEmpty())
		return;

	size--;

	if (size < capacity / 2) {
		capacity /= 2;
		T* newVector = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			newVector[i] = vector[i];
		}

		delete[] vector;
		vector = newVector;
	}
}

template <typename T>
void Vector<T>::removeAt(int pos)
{
	if (pos == this->size - 1) 
		this->popBack();

	else if (pos > -1 && pos < size && size>0) {
		for (size_t i = pos; i < size - 1; i++)
			vector[i] = vector[i + 1];

		size--;
	}

	if (size < capacity / 2) {
		capacity /= 2;
		T* newVector = new T[capacity];

		for (size_t i = 0; i < size; i++)
			newVector[i] = vector[i];
		
		delete[] vector;
		vector = newVector;
	}
}

template <typename T>
void Vector<T>::print()
{
	for (size_t i = 0; i < size; i++)
		vector[i]->print();
	cout << endl;
}

template <typename T>
void Vector<T>::printWithIndexes()
{
	for (size_t i = 0; i < size; i++) {
		cout << i + 1 << ". ";
		vector[i]->print();
	}
	cout << endl;
}


#endif