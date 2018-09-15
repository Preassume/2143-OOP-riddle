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
using namespace std;

class myVector{
private:
	int curCap; //Keeps track of the capacity of the vector
	int index = 0; //Keeps track of where we are in the vector.
				   //Also used to determine the size of the vector.
	
	
/**
*   Expands the vector by 1.5 times. Used by push_back and pop_back as
*	an easy way to grow the vector without having to specify a size.
*/
	void expand();
	
	
/**
*   Shrinks the vector to half its original size. Used by push_back
*	and pop_back as an easy way to grow the vector without having
*	to specify a size.
*/
	void shrink();
	
public:
	int *theVector;
	int defaultCap = 4; //Default vector capacity
	
	
/**
*   Constructor for the vector used when no size is specified upon declaration.
* 	Creates a vector of default size.
*/
	myVector();
	
	
/**
*   Constructor for the vector used when a specific size is desired upon
* 	declaration.  Creates a vector of specified size.
* 
* 	@param {int} cap: The size of the vector's capacity when declared 
*/
	myVector(int cap);
	
	
/**
*   Resizes the vector's capacity to whatever size is specified.  Can be larger
* 	or smaller than its previous capacity.  If the requested size is smaller
* 	than the default capacity of the vector, the default size is used instead.
* 
* 	@param {int} newCap: The size you want to change the vector to. 
*/
	void resize(int newCap);
	
	
/**
*   Checks if the vector is currently full or not.
* 
* 	@return {bool}: Returns true if vector is full, and false if it is not. 
*/
	bool full();
	
	
/**
*   Pushes a new item onto the vector.  If the vector is full,
* 	its capacity will be expanded by 1.5 times.
* 
* 	@param {int} value: The integer being pushed onto the vector. 
*/
	void push_back(int value);
	
	
/**
*   Pops a number from the vector.  If the vector has no more items, it
* 	will return a 0.  If the vector becomes 40% full or less, it will
* 	shrink to half its original capacity.
* 
* 	@return {int}: The integer being popped off of the vector. 
*/
	int pop_back();
	
	
/**
*   Prints the contents of the vector.  This is the standard function
* 	that should be used for printing.
*/
	void print();
	
	
/**
*   Prints every value stored in the vector, including values that have not
* 	been pushed onto the vector, but are stored in the vector due to its
* 	capacity being larger than its current size.
*/
	void print_cap();
	
	
/**
*   Calculates and returns how full the vector is by percentage.
* 	Used by pop_back() to determine when to shrink the vector.
* 
* 	@return {double}: Returns the percentage of the vector that is filled. 
*/
	double percent_full();
	
	
/**
*   Uses the current value for index to indicate what size the vector
*	currently is.
* 
* 	@return {int}: Returns the current size of the vector. 
*/
	int size();
	
	
/**
*   Returns the current capacity of the vector by using the value 
* 	in curCap.
* 
* 	@return {int}: Returns the current capacity of the vector. 
*/
	int capacity();
};