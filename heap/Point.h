/*
Author: Eric Buehler
Date: 11/11/2018
filename: Job.h
The Point class is used to represent Point numbers, which
are defined to be the quotient of two integers.
*/

#ifndef _Point_h
#define _Point_h

#include <iostream>
using namespace std;
template<typename T>
class Point {

public:


   // constructor
   Point();
   Point(T a, T b);
   string toString();
   bool operator>(const Point p2);
   bool operator<(Point p2);
   bool operator==(Point p2);
   void assign(T x1, T y1);
   friend ostream& operator<<(ostream& os, Point point)
   {
     os << "(" + to_string(point.x) + ", " + to_string(point.y) + ")" << " ";
     return os;
   }





private:
  T x;
  T y;


};


template<typename T>
Point<T>::Point()
{
  //empty constructor
}

template<typename T>
Point<T>::Point(T a, T b)
{

  x = a;
  y = b;
}


template<typename T>
bool Point<T>::operator<(Point<T> p2)
{
   if(x == p2.x)
   {
     if(y < p2.y)
     {
       return true;
     } else return false;
   }
   else if(x < p2.x)
   {
     return true;
   } else return false;
}


template<typename T>
bool Point<T>::operator>(Point<T> p2)
{
   if(x == p2.x)
   {
     if(y > p2.y)
     {
       return true;
     } else return false;
   }
   else if(x > p2.x)
   {
     return true;
   } else return false;
}




template<typename T>
bool Point<T>::operator==(Point<T> p2)
{
   if(x == p2.x && y == p2.y)
   {
     return true;
   } else return false;
}

template<typename T>
void Point<T>::assign(T x1, T y1)
{
  x = x1;
  y = y1;
}


#endif
