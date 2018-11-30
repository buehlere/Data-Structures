/*
*Eric Buehler
*Dr. Sevkli
*Homework #3
*9-13-2018
*List.h
*====================
* This tests the add all and delete all methods for homework 3. I've added
* two additional test cases to this file that can be used to check the
* various cases of these functions. 
*/

#include <iostream>
#include <string>
#include "List.h" // List class definition
using namespace std;

// display program instructions to user
void instructions() {
   cout << "Enter one of the following:\n"
      << "  1 to insert at beginning of list\n"
      << "  2 to insert at end of list\n"
      << "  3 to delete from beginning of list\n"
      << "  4 to delete from end of list\n"
      << "  5 test addAll method\n"
      << "  6 test removeAll method\n"
      << "  7 try double values/end program\n";
}

// function to test a List
template<typename T>
void testList(List<T>& listObject, List<T>& OtherlistObject, const string& typeName) {
   cout << "Testing a List of " << typeName << " values\n";
   instructions(); // display instructions

   int choice; // store user choice
   T value; // store input value

   do { // perform user-selected actions
      cout << "? ";
      cin >> choice;
      switch (choice) {
      case 1:
      { // insert at beginning
         cout << "Enter " << typeName << ": ";
         cin >> value;
         listObject.insertAtFront(value);
         listObject.print();
         break;
       }
      case 2: // insert at end
      {
         cout << "Enter " << typeName << ": ";
         cin >> value;
         listObject.insertAtBack(value);
         listObject.print();
         break;
       }
      case 3: // remove from beginning
      {
         if (listObject.removeFromFront(value)) {
            cout << value << " removed from list\n";
         }

         listObject.print();
         break;
      }
      case 4: // remove from end
      {
         if (listObject.removeFromBack(value)) {
            cout << value << " removed from list\n";
         }

         listObject.print();
         break;
      }
      case 5:
      {
        //variables for reading in list
        int size;
        int Othersize;
        T element;
        //testing addAll() method
        //emptying out list test
        while(!listObject.isEmpty())
        {
          listObject.destroy();
        }
        //emptying other list for test
        while(!OtherlistObject.isEmpty())
        {
          OtherlistObject.destroy();
        }
        //building list
        cout << "enter size of List Object: ";
        cin >> size;
        for(int i = 0; i < size; i++)
        {
          cout << "enter element of List Object: ";
          cin >> element;
          listObject.insertAtBack(element);
        }
        listObject.print();
        //building other list
        cout << "enter size of Other List Object: ";
        cin >> Othersize;
        for(int i = 0; i < Othersize; i++)
        {
          cout << "enter element of Other List Object: ";
          cin >> element;
          OtherlistObject.insertAtBack(element);
        }
        listObject.print();
        cout << "the other";
        OtherlistObject.print();
        //call to add all
        cout << "adding unique elements" << endl;
        listObject.addAll(OtherlistObject);
        //results
        listObject.print();
        break;
      }
      case 6:
      {
        //variables for reading in list
        int sizeD;
        int OthersizeD;
        T elementD;
        //testing removeAll() method
        //emptying out list test
        while(!listObject.isEmpty())
        {
          listObject.destroy();
        }
        //emptying other list for test
        while(!OtherlistObject.isEmpty())
        {
          OtherlistObject.destroy();
        }
        //building list
        cout << "enter size of List Object: ";
        cin >> sizeD;
        for(int i = 0; i < sizeD; i++)
        {
          cout << "enter element of List Object: ";
          cin >> elementD;
          listObject.insertAtBack(elementD);
        }
        listObject.print();
        //building other list
        cout << "enter size of Other List Object: ";
        cin >> OthersizeD;
        for(int i = 0; i < OthersizeD; i++)
        {
          cout << "enter element of Other List Object: ";
          cin >> elementD;
          OtherlistObject.insertAtBack(elementD);
        }
        cout << "the other";
        OtherlistObject.print();
        //call to remove all
        cout << "removing shared elements" << endl;
        listObject.removeAll(OtherlistObject);
        //results
        listObject.print();
        break;
      }
      }
   } while (choice != 7);

   cout << "End list test\n\n";
}

int main() {
   //test List of int values
   List<int> integerList;
   List<int> OtherintegerList;
   testList(integerList, OtherintegerList, "integer");

   //test List of string values
   List<string> stringList;
   List<string> OtherstringList;
   testList(stringList, OtherstringList, "string");

   return 1;

}
