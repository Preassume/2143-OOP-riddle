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

int main(){
	myVector vec(10);
	
	cout << vec.pop_back() << "\n\n";
	
	vec.push_back(13);
	vec.push_back(31);
	vec.push_back(73);
	vec.print();
	
	for(int i = 0; i < 10000; i++){
		vec.push_back(i);
	}
	cout << '\n' << vec.size() << ", " << vec.capacity() << '\n';
	
	
	for(int i = 0; i < 9998; i++){
		vec.pop_back();
	}
	cout << '\n' << vec.size() << ", " << vec.capacity() << "\n\n";
	vec.print();
}
