//list.h

#ifndef LIST
#define LIST

#include <string>
#include <sstream>

template <class T>
class List 
{
   public:
      List();// default constructor
      List(const List<T>& src);//copy constructor
      ~List();//destructor
      void add(T item);//append new item to the end of list
      int size() const; //return the number of items in the list
      int index(T item) const; //return the index of the item or -1 if not found
      void insert(int index,T item);  // insert item in position index
      void remove(int index);               // delete the item in position index
      std::string toString() const;              // return a string representation of the list
      T& operator[](int index) const;  // indexing operator
      List& operator=(const List& src);     // assignment operator
      List& operator+=(const List& src);    // concatenation operator
   private:
   static const int INITIAL_CAPACITY = 10;
   
   T *data;//array of items in the list
   int capacity;//maximum capacity of the array
   int count; //number of elements in the list
   void deepCopy(const List<T>& src);
   void expandCapacity(int newCapacity);
};
template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list);

class IndexError
{
   

};
#include "list.cpp"

#endif 
