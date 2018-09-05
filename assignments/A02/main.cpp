    /**
    *  Course: CMPS 2143 - Object Oriented Programming
    *  Assignment: A02
    *  Purpose: Add comments to code
    * 
    *  @author Austin Riddle
    *  @version 1.1 9/5/2018
    */

#include <iostream>
#include <string>

using namespace std;

int A[100];

struct Node
{
    int x;
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

class List
{
  private:
    Node *Head;
    Node *Tail;
    int Size;

  public:
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
	
	
	
	/**
	*  Pushes a value onto the linked list
	*
	*  @param {int} val The value to be pushed onto the linked list.
	*/
	
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
    
    
    
	/**
	*  Inserts a value into the linked list
	*
	*  @param {int} val The value to be inserted into the linked list.
	*/
	
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }



	/**
	*  Prints the value in the tail of the list
	*/
	
    void PrintTail()
    {
        cout << Tail->x << endl;
    }
    
    
    
	/**
	*  Allows us to easily print the linked list.  Returns the list
	*  as a string with arrows separating values.
	*
	*  @return {string} Returns the entire linked list as a string
	*/
	
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented 
    int Pop()
    {
        Size--;
        return 0; //
    }



	/**
	*  Overloads the + operator to allow us to combine two
	*  linked lists together as one.
	*
	*  @param {const List} An existing List is passed by reference to be combined.
	*  @return {List} Returns the newly created linked list which contains all
	* 			values from two other linked lists.
	*/
	
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }



	/**
	*  Overloads the [] operator.  This allows us to access a linked list
	*  in the same way that an array could be accessed using an index.
	*
	*  @param {int} index is the location in the list that you want
	* 		  to get the value from.
	*  @return {int} Returns the value in the list in the position of index
	*/
	
    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }



	/**
	*  Overloads the << operator for use with cout
	* 
	*  @param {ostream} an ostream is passed by reference
	*  @param {List} a linked list is passed in to be printed
	*  @return {ostream} Returns our ostream
	*/
	
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1;
    List L2;

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
