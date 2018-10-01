#include <iostream>

using namespace std;

class myVector{
private:
  int *vPtr;      // int pointer to array
  int maxSize;    // max size of array
  int minSize;    // min size of array
  int index;      // current location to insert or remove
  int* _resize(int);
  
public:
  myVector(int size);
  myVector();
  void pushBack(int item);
  void pushBack(int *,int size);
  int popBack();
  double percentFull();
  int* resize(double);
  int* resize(int);

  void print();
  int size();
  void size(int);
  int vSize();
  
  int& operator[](int);
  
  myVector operator+(myVector&);
  myVector operator+(int);
  
  myVector operator-(myVector&);
  myVector operator-(int);
  
  myVector operator*(myVector&);
  myVector operator*(int);
  
  myVector operator/(myVector&);
  myVector operator/(int);
  
  bool operator==(myVector&);
  void operator=(myVector);

  friend ostream& operator<<(ostream& os, myVector V){
    for(int i=0;i<V.index;i++){
      os<<V.vPtr[i]<<" ";
    }
    return os;
  }
};