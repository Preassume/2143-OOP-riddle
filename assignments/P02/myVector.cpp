#include <iostream>
#include "myVector.h"
using namespace std;

/**
* Function constructor
*   Sets up the vector
* @param {int} size : initial size of vector 
* @return void
*/
myVector::myVector(int size){
  maxSize = size;
  minSize = size;
  // create the array of vSize
  vPtr = new int[maxSize];
  index = 0;
}

/**
* Function constructor
*   Sets up the vector at default size
* @return void
*/
myVector::myVector(){
  maxSize = 8;
  minSize = 4;
  // create the array of vSize
  vPtr = new int[maxSize];
  index = 0;
}

/**
* Function print
*   Prints the current values in the vector
* @param void  
* @return void
*/
void myVector::print(){
  for(int i=0;i<index;i++){
    cout<<vPtr[i]<<" ";
  }
  cout<<endl;
}

/**
* Function pushBack
*   Adds value to vector
* @param {int} item : integer value  
* @return void
*/
void myVector::pushBack(int item){
  if(index >= maxSize){
    vPtr = resize(1.5);
  }
  vPtr[index++] = item;
}

/**
* Function popBack
*   Returns value from vector
* @param none 
* @return {int} : last item on vector
*/
int myVector::popBack(){

  index--;

  if(index < 0){
    //dammit
  }

  if(percentFull() <= .4){
    vPtr = resize(.5);
  }

  return vPtr[index];
}

/**
* Function resize
*   Resizes our vector based on passed in ratio
* @param {double} ratio : new array size 
* @return {int*} : pointer to new array
*/
int* myVector::resize(double ratio){
  // figure out what our new size is, bigger or smaller
  int newSize = maxSize * ratio;

  return _resize(newSize);
}

int* myVector::resize(int size){

  return _resize(size);
  
}

int* myVector::_resize(int newSize){
  // Lets keep our vector above some minimum size
  if(newSize < minSize){
    newSize = minSize;
  }

  // allocate new bigger vector
  int* vBigger = new int[newSize];

  //copy everything over
  for(int i=0;i<index;i++){
    vBigger[i] = vPtr[i];
  }

  // update new max size
  maxSize = newSize;

  // delete old memory
  delete [] vPtr;

  //return ptr to new memory
  return vBigger;
}

/**
* Function percentFull
*   helper function to calculate how full vector is
* @param none
* @return {double} : how full vector is
*/
double myVector::percentFull(){
  return double(index) / double(maxSize);
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
int myVector::size(){
  return index;
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
void myVector::size(int newSize){
  vPtr = _resize(newSize);
}

/**
* Function vSize
*    Returns actual size of allocated memory
* @param none
* @return {int} : mem size
*/
int myVector::vSize(){
  return maxSize;
}

/**
* Function pushBack
*   Adds an array to vector
* @param {int} *A : array of values
* @param {int} size : size of array
* @return void
*/
void myVector::pushBack(int *A, int size){
	for(int i = 0; i < size; i++){
		if(index >= maxSize){
			vPtr = resize(1.5);
		}
		vPtr[index++] = A[i];
	}
}

/**
* Operator []
*   Overloads the [] operator
* @param {int} i : desired index of the vector
* @return int&
*/
int& myVector::operator[](int i){
      if (i >= maxSize) 
      { 
          cout << "Array index out of bound, exiting\n"; 
          exit(0); 
      }else if(i >= index){
          cout << "Warning: vector["<<i<<"] is undefined ...\n";
      }
      return vPtr[i]; 
}

/**
* Operator +
*   Overloads the + operator
* @param {myVector&} rhs : vector on the right of the operator
* @return myVector
*/
myVector myVector::operator+(myVector& rhs){
    //rhs = vector on the right of the + sign
    //lhs = THIS vector (the one were in)
    int rhsSize = rhs.index;
    int lhsSize = index;
    int max = 0;

    // which vector is bigger?
    if(rhsSize > lhsSize){
		max = rhsSize;
	}
    else{
		max = lhsSize;
	}
	
	myVector newVector(max);
	
    if(rhsSize > lhsSize){
		for(int i = 0; i < max; i++){
			if(i < index)
				newVector.pushBack(vPtr[i] + rhs[i]);
			else
				newVector.pushBack(rhs[i]);
		}
	}
    else{
		for(int i = 0; i < max; i++){
			if(i < rhs.index)
				newVector.pushBack(vPtr[i] + rhs[i]);
			else
				newVector.pushBack(vPtr[i]);
		}
	}
	return newVector;
}

/**
* Operator +
*   Overloads the + operator
* @param {int} add : integer to add to the values in the vector
* @return myVector
*/
myVector myVector::operator+(int add){
  
	myVector newVector(index);

	for(int i = 0; i < index; i++){
		newVector.pushBack(vPtr[i] + add);
	}
	return newVector;
}

/**
* Operator -
*   Overloads the - operator
* @param {myVector&} rhs : vector on the right of the operator
* @return myVector
*/
myVector myVector::operator-(myVector& rhs){
    //rhs = vector on the right of the - sign
    //lhs = THIS vector (the one were in)
    int rhsSize = rhs.index;
    int lhsSize = index;
    int max = 0;

    // which vector is smaller?
    if(rhsSize > lhsSize){
		max = rhsSize;
	}
    else{
		max = lhsSize;
	}
	
	myVector newVector(max);
	
    if(rhsSize > lhsSize){
		for(int i = 0; i < max; i++){
			if(i < index)
				newVector.pushBack(vPtr[i] - rhs[i]);
			else
				newVector.pushBack(rhs[i]);
		}
	}
    else{
		for(int i = 0; i < max; i++){
			if(i < rhs.index)
				newVector.pushBack(vPtr[i] - rhs[i]);
			else
				newVector.pushBack(vPtr[i]);
		}
	}
	return newVector;
}

/**
* Operator -
*   Overloads the - operator
* @param {int} subtract : integer to subtract from the values in the vector
* @return myVector
*/
myVector myVector::operator-(int subtract){
	  
	myVector newVector(index);
	
	for(int i = 0; i < index; i++){
		newVector.pushBack(vPtr[i] - subtract);
	}
	
	return newVector;
}

/**
* Operator *
*   Overloads the * operator
* @param {myVector&} rhs : vector on the right of the operator
* @return myVector
*/
myVector myVector::operator*(myVector& rhs){
    //rhs = vector on the right of the * sign
    //lhs = THIS vector (the one were in)
    int rhsSize = rhs.index;
    int lhsSize = index;
    int max = 0;
	
    // which vector is smaller?
    if(rhsSize > lhsSize){
		max = rhsSize;
	}
    else{
		max = lhsSize;
	}
	
	myVector newVector(max);
	
    if(rhsSize > lhsSize){
		for(int i = 0; i < lhsSize; i++){
			newVector.pushBack(vPtr[i] * rhs[i]);
		}
	}
    else{
		for(int i = 0; i < rhsSize; i++){
			newVector.pushBack(vPtr[i] * rhs[i]);
		}
	}
	return newVector;
}
  
/**
* Operator *
*   Overloads the * operator
* @param {int} multiplier : integer to multiply the values in the vector by
* @return myVector
*/
myVector myVector::operator*(int multiplier){
	  
	myVector newVector(index);
	
	for(int i = 0; i < index; i++){
		newVector.pushBack(vPtr[i] * multiplier);
	}
	return newVector;
}

/**
* Operator /
*   Overloads the / operator
* @param {myVector&} rhs : vector on the right of the operator
* @return myVector
*/
myVector myVector::operator/(myVector& rhs){
    //rhs = vector on the right of the / sign
    //lhs = THIS vector (the one were in)
    int rhsSize = rhs.index;
    int lhsSize = index;
    int max = 0;

    // which vector is smaller?
    if(rhsSize > lhsSize){
		max = rhsSize;
	}
    else{
		max = lhsSize;
	}
	
	myVector newVector(max);
	
    if(rhsSize > lhsSize){
		for(int i = 0; i < max; i++){
			if(i < index)
				newVector.pushBack(vPtr[i] / rhs[i]);
			else
				newVector.pushBack(rhs[i]);
		}
	}
    else{
		for(int i = 0; i < max; i++){
			if(i < rhs.index)
				newVector.pushBack(vPtr[i] / rhs[i]);
			else
				newVector.pushBack(vPtr[i]);
		}
	}
	return newVector;
}

/**
* Operator /
*   Overloads the / operator
* @param {int} denominator : integer to divide the values in the vector by
* @return myVector
*/
myVector myVector::operator/(int denominator){
	  
	myVector newVector(index);
	
	for(int i = 0; i < index; i++){
		newVector.pushBack(vPtr[i] / denominator);
	}
	return newVector;
}

/**
* Operator ==
*   Overloads the == operator
* @param {myVector&} rhs : vector on the right of the operator
* @return bool
*/
bool myVector::operator==(myVector& rhs){
	//rhs = vector on the right of the == sign
	//lhs = THIS vector (the one were in)
	int rhsSize = rhs.index;
	int lhsSize = index;


	//If the vectors are not the same size, then they cannot be equal
	if(rhsSize != lhsSize){
		return false;
	}

	//Checks all values in the vectors and makes sure they are euqal
	for(int i = 0; i < index; i++){
		if(vPtr[i] != rhs[i])
			return false;
	}
	return true; //If we've made it this far, then they must be equal
}

/**
* Operator =
*   Overloads the = operator
* @param {myVector&} rhs : vector on the right of the operator
* @return void
*/
void myVector::operator=(myVector rhs){

	int newSize = rhs.index;

	index = 0; //Lets us insert at the beginning, overwriting old values

	resize(newSize); //Resizes the vector to be no larger than needed

	for(int i = 0; i < newSize; i++){
		pushBack(rhs[i]);
	}
}