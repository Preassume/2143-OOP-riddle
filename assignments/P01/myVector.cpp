/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: P01
*  Purpose: This program contains a custom implementation of a vector.
*  		It works similarly to an STL vector, and has some of the same
*  		functions/methods as well.
* 
*  @author Austin Riddle
*  @version 1.0 9/14/2018
*/

#include <iostream>
#include "myVector.h"
using namespace std;

//Default capacity constructor
myVector::myVector(){
	theVector = new int[defaultCap];
	curCap = defaultCap;
}

//Specified capacity constructor
myVector::myVector(int cap){
	theVector = new int[cap];
	curCap = cap;
}

//Resizes the vector's capacity to a specified size
void myVector::resize(int newCap){
	if(newCap == curCap)
		return;  //Stops the function if nothing needs to be done
	
	//Makes sure the vector is at least as large as the default capacity
	if(newCap < defaultCap)
		newCap = defaultCap;
	
	//Makes sure that the index isn't larger than the size of the vector
	if(index > newCap)
		index = newCap;
	
	int *tempArray = new int[newCap]; //Temporary array to save our items
	
	//Copies values down to temporary array
	for(int i = 0; (i < curCap) || (i < newCap); i++){
		tempArray[i] = theVector[i];
	}
	delete[] theVector;
	
	theVector = new int[newCap]; //theVector is now the size it needs to be
	
	//Items are placed back onto theVector
	for(int i = 0; (i < curCap) || (i < newCap); i++){
		theVector[i] = tempArray[i];
	}
	
	curCap = newCap; //curCap is updated to hold the new current size
}

//Expands the vector's capacity by 1.5 times.  Works similarly to resize()
void myVector::expand(){
	int *tempArray = new int[curCap];
	int oldSize = curCap;
	
	for(int i = 0; i < curCap; i++){
		tempArray[i] = theVector[i];
	}
	delete[] theVector;
	
	curCap = curCap + (curCap / 2);
	
	theVector = new int[curCap];
	
	for(int i = 0; i < oldSize; i++){
		theVector[i] = tempArray[i];
	}
}

//Shrinks the vector's capacity to half its original size.
//Works similarly to resize()
void myVector::shrink(){
	curCap = curCap / 2;
	
	int *tempArray = new int[curCap];
	
	for(int i = 0; i < curCap; i++){
		tempArray[i] = theVector[i];
	}
	delete[] theVector;
	
	theVector = new int[curCap];
	
	for(int i = 0; i < curCap; i++){
		theVector[i] = tempArray[i];
	}
}

//Checks if the vector is currently full
bool myVector::full(){
	if(index == (curCap - 1))
		return true;
	else
		return false;
}

//Pushes an integer onto the vector, expanding it if needed
void myVector::push_back(int value){
	if(full())
		expand();
		
	theVector[index] = value; //Places value onto vector
	index++; //Increments index for future use
}

//Pops an integer from the vector, shrinking it if needed
int myVector::pop_back(){
	if(index <= 0)
		return 0;
	
	index--;
	
	//The vector will be shrunk if it is only 40% full
	if((percent_full() <= 0.4) && (curCap >= 8)){
		shrink();
	}
	//Ensures that the vector does not become smaller than its default size
	else if(percent_full() <= 0.4 && curCap > defaultCap){
		resize(defaultCap);
	}
	
	return(theVector[index]);
}

//Prints the contents of the vector
void myVector::print(){
	for(int i = 0; i < index; i++)
		cout << theVector[i] << ' ';
	cout << '\n';
}

//Prints values from the entire capacity of the vector
void myVector::print_cap(){
	for(int i = 0; i < curCap; i++)
		cout << theVector[i] << ' ';
	cout << '\n';
}

//Returns the percentage of the vector that is filled
double myVector::percent_full(){
	return((double)index / (double)curCap);
}

//Returns the size of the vector
int myVector::size(){
	return index;
}

//Returns the capacity of the vector
int myVector::capacity(){
	return curCap;
}