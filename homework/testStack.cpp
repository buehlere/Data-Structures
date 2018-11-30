/*
   * Eric Buehler
   * Date: 9/3/18
   * File: testStack.cpp
   * ---------------------
   * This file creates a template function for adding and popping
   * elements onto a stack.
*/

#include <iostream>
#include <string>
#include "Stack.h" // Stack class template definition
using namespace std;



template <typename T> //declaring template type T
void testStack(Stack<T> &stack, T value, T increment, int size, string name)
{
/*
  Summary: This function pushes multiple template type items onto a stack
  and then pops them off. The actions of the functions are printed.
  * ---------------------
  Input:
  -stack: a stack of some predetermined type.
  -value: initial value to be pushed onto stack.
  -increment: amount by which initial value is incremented.
  -size: size of stack.
  -name: name of stack to be printed.
*/
  cout << "Pushing elements onto " << name << endl;


  // push 5 doubles onto stack
  for (size_t i{0}; i < size; ++i)
  {
     stack.push(value);
     cout << value << ' ';
     value += increment;
  }

  cout << "\n\nPopping elements from " << name << endl;

  // pop elements from stack
  while (!stack.isEmpty())
  { // loop while Stack is not empty
     cout << stack.top() << ' '; // display top element
     stack.pop(); // remove top element
  }

  cout << name << " is empty, cannot pop.\n";

}

int main()
{
   Stack<double> stack1; // create a Stack of double
   testStack(stack1, 1.1, 1.1, 5, "Double Stack");

   cout << "\n\n" << endl; //break between outputs.

   Stack<int> stack2; // create a Stack of int
   testStack(stack2, 1, 1, 10, "Int Stack");
 }
