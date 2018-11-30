/*
Author: Eric Buehler
Date: 11/29/2018
filename: SeperateChain.h
This header file defines two different hash tables.
*/

#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

// SeparateChaining Hash table class
/**
 * This .h file implements two classes HashTable1 and HashTable2.
 * HashTable1 uses my own hash function, while HashTable2 uses std's
 * hash function.
 8*/

//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

class HashTable1
{
  public:
    HashTable1( int size = 101)
    {

      currentSize = 0;
      initialSize = size;
      theLists.resize(nextPrime( size ));

    }


    bool contains( const string & x ) const
    {
      /**
      * Takes a string and returns true if that string appears in the
      * hash table, false otherwise.
      */
      bool contains = false;
      //find buckets
      list<string> bucket;
      bucket = theLists[myhash(x)];
      //elements in buckets
      for (auto const& i : bucket)
      {
          if(i == x)
            contains = true;
      }
      return contains;
    }

    void makeEmpty( )
    {
      for(int i = 0; i < theLists.size(); i++)
      {
        theLists[i].clear();
      }
      currentSize = 0;
    }


    bool insert( const string & x)
    {
      /**
      * Takes a string and inserts it into the hash table.
      */
      //declaring index
      size_t hashIndex;

      //no repeats
      if(contains(x))
        return false;

      //hash

      hashIndex = myhash(x);


      //grab bucket and insert
      theLists[hashIndex].push_back(x);
      //checks
      currentSize += 1;

      //load factor
      float loadFactor = (float) (currentSize) / (float) (theLists.size());

      //if load factor is greater than 4 rehash variable
      if(loadFactor > 4.0)
      {
        rehashCount += 1;
        rehash( );
      }
      return true;
    }

    void printSummary()
    {
      /**
      * prints summary statistics for the hash table.
      */
      cout << "Initial hash table size: " << initialSize << endl;
      cout << "Max Load factor: " << "4.0" << endl;
      cout << rehashCount << " times rehashing was done" << endl;
      cout << "Final hash table size is: " << theLists.size() << endl;
      cout << "Current load factor= " << (float) (currentSize) / (float) (theLists.size()) << endl;
      cout << "Max chain length " << MaxChainLength() << endl;
      cout << "Avg. chain length " << averageChainLength() << endl;
      cout << "Number of zero-length chains: " << numberOfNonZero() << endl;
    }

    void printTable()
    {
      /**
      * prints the contents of the hash table
      */
      for(int i = 0; i < theLists.size(); i++)
      {
        list<string> bucket = theLists[i];

        //elements in buckets
        for (auto const& i : bucket)
        {
          cout << i << endl;
        }
      }
    }


  private:
    vector<list<string>> theLists;;   // The array of Lists
    int currentSize = 0;

    //variables for summary statistics
    int initialSize = 0;
    int rehashCount = 0;

    void rehash( )
    {
      /**
      * if the load factor is greater than four the rehash functions
      * finds the closes prime that is double the size of the table
      * and rehashes all elements.
      */
      vector<list<string>> oldLists = theLists;

      // Create new double-sized, empty table
      theLists.resize( nextPrime( 2 * oldLists.size( ) ) );

      //empty list
      makeEmpty();

      // Copy table over
      currentSize = 0;

      //insert elements
      for(int i = 0; i < oldLists.size(); i++)
      {
        list<string> bucket = oldLists[i];
        //elements in buckets
        for (auto const& i : bucket)
        {
            insert(i);
            currentSize += 1;
        }
      }

    }

    size_t myhash( const string & x ) const
    {
      /**
      * My hash fucntion
      */
       int index = 0;

       for(int i = 0; i<x.length();  i++)
       //adding characters ASCI and multiplying by a prime value
         index = 37*index+x[i];

       //mod by table size
       index %= theLists.size();

       return index;

    }
    bool isPrime( int n )
    {
      /**
      * returns a boolean value if the number is prime or not
      */
        if( n == 2 || n == 3 )
            return true;

        if( n == 1 || n % 2 == 0 )
            return false;

        for( int i = 3; i * i <= n; i += 2 )
            if( n % i == 0 )
                return false;

        return true;
    }

    int nextPrime( int n )
    {
      /**
      * finds the nearest prime number
      */
        if( n % 2 == 0 )
            ++n;

        for( ; !isPrime( n ); n += 2 ) ;

        return n;
    }

    int numberOfNonZero()
    {
      /**
      * returns the number of nonzero buckets in the hash table
      */
      int counter = 0;
      for(int i = 0; i < theLists.size();i++)
      {
        if(theLists[i].size() == 0)
        {
          counter += 1;
        }
      }
      return counter;
    }

    int MaxChainLength()
    {
      /**
      * finds the longest chain in the hash table
      */
      int max = 0;
      for(int i = 0; i < theLists.size();i++)
      {
        if(theLists[i].size() != 0 && theLists[i].size() > max )
        {
          max = theLists[i].size();
        }
      }
      return max;
    }

    int averageChainLength()
    {
      /**
      * computes the average chain length
      */
      float sum = 0;
      float count = 0;
      float average = 0;
      for(int i = 0; i < theLists.size();i++)
      {
        if(theLists[i].size() != 0)
        {
          count += 1;
          sum += theLists[i].size();
        }
      }
      average = sum / count;
      return average;
    }



};


class HashTable2
{
  /**
  * This class is the clone of the one defined above. However, It
  * uses std's hash function instead of my own.
  */
  public:
    HashTable2( int size = 101)
    {
      /**
      * constructs a hash table by a default size of 101, or by the
      * user's specification.
      */
      currentSize = 0;
      initialSize = size;
      theLists.resize(nextPrime( size ));

    }

    /**
    * Takes a string and returns true if that string appears in the
    * hash table, false otherwise.
    */
    bool contains( const string & x ) const
    {
      bool contains = false;
      //buckets
      list<string> bucket;
      bucket = theLists[theirhash(x)];
        //elements in buckets
      for (auto const& i : bucket)
      {
          if(i == x)
            contains = true;
      }
      return contains;
    }

    void makeEmpty( )
    {
      /**
      * This functions empties the hash table. 
      */
      for(int i = 0; i < theLists.size(); i++)
      {
        theLists[i].clear();
      }
      currentSize = 0;
    }

    bool insert( const string & x)
    {
      //setting hash style

      //declaring index
      size_t hashIndex;

      //no repeats
      if(contains(x))
        return false;

      //hash

      hashIndex = theirhash(x);


      //grab bucket and insert
      theLists[hashIndex].push_back(x);
      //checks
      currentSize += 1;
      float loadFactor = (float) (currentSize) / (float) (theLists.size());
      if(loadFactor > 4.0)
      {
        rehashCount += 1;
        rehash( );
      }
      return true;
    }

    void printSummary()
    {
      cout << "Initial hash table size: " << initialSize << endl;
      cout << "Max Load factor: " << "4.0" << endl;
      cout << rehashCount << " times rehashing was done" << endl;
      cout << "Final hash table size is: " << theLists.size() << endl;
      cout << "Current load factor= " << (float) (currentSize) / (float) (theLists.size()) << endl;
      cout << "Max chain length " << MaxChainLength() << endl;
      cout << "Avg. chain length " << averageChainLength() << endl;
      cout << "Number of zero-length chains: " << numberOfNonZero() << endl;

      //printTable();
    }

    void printTable()
    {
      for(int i = 0; i < theLists.size(); i++)
      {
        list<string> bucket = theLists[i];
        //elements in buckets
        for (auto const& i : bucket)
        {
          cout << i << endl;
        }
      }
    }


  private:
    vector<list<string>> theLists;;   // The array of Lists
    int currentSize = 0;
    int initialSize = 0;
    int rehashCount = 0;

    void rehash( )
    {
      vector<list<string>> oldLists = theLists;

      // Create new double-sized, empty table
      theLists.resize( nextPrime( 2 * oldLists.size( ) ) );

      //empty list
      makeEmpty();

      // Copy table over
      currentSize = 0;

      //insert elements
      for(int i = 0; i < oldLists.size(); i++)
      {
        list<string> bucket = oldLists[i];
        //elements in buckets
        for (auto const& i : bucket)
        {
            insert(i);
            currentSize += 1;
        }
      }

    }


    size_t theirhash( const string & x ) const
    {
      /**
      * using std hash function
      */
      hash<string> hash_fn;
      size_t index = hash_fn(x);
      index = index % theLists.size();
      return index;
    }

    bool isPrime( int n )
    {
        if( n == 2 || n == 3 )
            return true;

        if( n == 1 || n % 2 == 0 )
            return false;

        for( int i = 3; i * i <= n; i += 2 )
            if( n % i == 0 )
                return false;

        return true;
    }

    int nextPrime( int n )
    {
        if( n % 2 == 0 )
            ++n;

        for( ; !isPrime( n ); n += 2 ) ;

        return n;
    }

    int numberOfNonZero()
    {
      int counter = 0;
      for(int i = 0; i < theLists.size();i++)
      {
        if(theLists[i].size() == 0)
        {
          counter += 1;
        }
      }
      return counter;
    }

    int MaxChainLength()
    {
      int max = 0;
      for(int i = 0; i < theLists.size();i++)
      {
        if(theLists[i].size() != 0 && theLists[i].size() > max )
        {
          max = theLists[i].size();
        }
      }
      return max;
    }

    int averageChainLength()
    {
      float sum = 0;
      float count = 0;
      float average = 0;
      for(int i = 0; i < theLists.size();i++)
      {
        if(theLists[i].size() != 0)
        {
          count += 1;
          sum += theLists[i].size();
        }
      }
      average = sum / count;
      return average;
    }



};

#endif
