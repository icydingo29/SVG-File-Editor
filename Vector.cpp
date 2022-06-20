#include "Vector.h"
#include <iostream>

//template <typename T>
//Vector<T>::Vector()
//{
//	size = 0;
//	capacity = 1;
//	vector = new T[capacity];
//}
//
//template <typename T>
//Vector<T>::Vector(Vector const& vectorParam) {
//	this->Vector();
//	for (size_t i = 0; i < vectorParam.size; i++)
//	{
//		this->pushBack(vectorParam.vector[i]);
//	}
//}
//
//template <typename T>
//Vector<T>::~Vector()
//{
//	delete[] vector;
//}
//
//template <typename T>
//Vector<T>& Vector<T>::operator=(Vector const& vectorParam) {
//	if (this != &vectorParam) {
//		for (size_t i = 0; i < size; i++)
//		{
//			this->popBack();
//		}
//
//		for (size_t i = 0; i < vectorParam.size; i++)
//		{
//			this->pushBack(vectorParam.vector[i]);
//		}
//	}
//
//	return *this;
//}
//
//
//
//template <typename T>
//int Vector<T>::getCapacity()
//{
//	return capacity;
//}
//
//template <typename T>
//int Vector<T>::getSize()
//{
//	return size;
//}
//
//template <typename T>
//bool Vector<T>::isEmpty()
//{
//	return (size == 0);
//	/*if (size == 0)
//		return true;
//
//	return false;*/
//}
//
//template <typename T>
//T Vector<T>::getAt(int pos)
//{
//	if (pos > -1 && pos < size && size>0)
//		return vector[pos];
//
//	else
//		return 0;
//}
//
//template <typename T>
//T Vector<T>::getFirst()
//{
//	if (size > 0)
//		return vector[0];
//
//	else
//		return 0;
//}
//
//template <typename T>
//T Vector<T>::getLast()
//{
//	if (size > 0)
//		return vector[size - 1];
//
//	else
//		return 0;
//}
//
//template <typename T>
//void Vector<T>::assign(int n, T x)
//{
//	delete[] vector;
//
//	size = 0;
//	capacity = 1;
//	vector = new int[capacity];
//
//	for (size_t i = 0; i < n; i++)
//	{
//		pushBack(x);
//	}
//}
//
//template <typename T>
//void Vector<T>::pushBack(T x)
//{
//	vector[size] = x;
//	size++;
//
//	if (size == capacity)
//	{
//		capacity *= 2;
//		int* newVector = new int[capacity];
//		for (size_t i = 0; i < size; i++)
//		{
//			newVector[i] = vector[i];
//		}
//
//		delete[] vector;
//		vector = newVector;
//	}
//}
//
//template <typename T>
//void Vector<T>::popBack()
//{
//	if (isEmpty())
//		return;
//
//	size--;
//
//	if (size < capacity / 2)
//	{
//		capacity /= 2;
//		int* newVector = new int[capacity];
//		for (size_t i = 0; i < size; i++)
//		{
//			newVector[i] = vector[i];
//		}
//
//		delete[] vector;
//		vector = newVector;
//	}
//}
//
//template <typename T>
//void Vector<T>::removeAt(int pos)
//{
//	if (pos == this->size - 1) {
//		this->popBack();
//	}
//
//	else if (pos > -1 && pos < size && size>0) {
//		for (size_t i = pos; i < size - 1; i++)
//		{
//			vector[i] = vector[i + 1];
//		}
//
//		size--;
//	}
//
//	if (size < capacity / 2)
//	{
//		capacity /= 2;
//		int* newVector = new int[capacity];
//		for (size_t i = 0; i < size; i++)
//		{
//			newVector[i] = vector[i];
//		}
//
//		delete[] vector;
//		vector = newVector;
//	}
//}
//
//template <typename T>
//void Vector<T>::print()
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		std::cout << vector[i] << " ";
//	}
//	std::cout << std::endl;
//}
