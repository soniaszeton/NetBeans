/* 
 * File:   terrible_dynamic_size_array_unsorted.h
 * Author: Sonia
 *
 * Created on February 5, 2015, 11:14 AM
 */

#include <iostream>
#ifndef TERRIBLE_DYNAMIC_SIZE_ARRAY_UNSORTED_H
#define	TERRIBLE_DYNAMIC_SIZE_ARRAY_UNSORTED_H
struct int_array {
	int* data;
	unsigned int count;
	unsigned int capacity;
	static const unsigned int DEFAULT_CAPACITY = 20;
};

void init(int_array& arr);

void destr(int_array& arr);

void resize(int_array& arr);

void clear(int_array& arr);

void add(int_array& arr, const int& payload);

bool contains(const int_array& arr, const int& target);

bool remove(int_array& arr, const int& target);

void print(const int_array& arr);




#endif	/* TERRIBLE_DYNAMIC_SIZE_ARRAY_UNSORTED_H */

