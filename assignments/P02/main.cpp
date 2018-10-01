/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: P02
*  Purpose: This program contains a custom implementation of a vector.
*  		It works similarly to an STL vector, and even has several
* 		overloaded operators to make it more familiar and versatile.
* 
*  @author Austin Riddle
*  @version 1.0 10/1/2018
*  @github repo: https://github.com/Preassume/2143-OOP-riddle
*/
#include <iostream>
#include "myVector.h"
using namespace std;

int main() {
	myVector v1;
	myVector v2;

	v1.pushBack(8);
	// v1 contains: [8]

	v2.pushBack(10);
	v2.pushBack(20);
	v2.pushBack(30);
	// v2 contains: [10,20,30]

	// Declare some int array
	int A[] = {1,2,3,4,5};


	v1.pushBack(A,5);
	// v1 contains: [8,1,2,3,4,5]

	v1 = v1 + v2;
	// v1 contains: [18,21,32,3,4,5]

	cout<<v1<<endl;
	// would print: [18,21,32,3,4,5] to standard out.

	cout<<v1[2]<<endl;
	// would print: 32 to standard out.


	v2 = v2 * 3;
	// v2 contains: [30,60,90]

	v2 = v2 * v1;
	// v2 contains: [540,1260,2880]

	v2[2] = 100;
	// v2 contains: [540,1260,100]
}
