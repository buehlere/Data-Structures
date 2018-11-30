#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
//#include "EasyStringHasher.h"
using namespace std;

class HashedObj {
public:
  HashedObj (){
    passw="";
    username="";
    info=EMPTY;
  }
  HashedObj (string pass,string name){
    passw=pass;
    username=name;
    info=ACTIVE;
  }
  void setinfo(int status){
    info=status;
  }
  int getinfo() {
    return info;
  }
  string getName(){
    return username;

  }
  bool operator!=(HashedObj& lhs) {
      return lhs.getName() != username ;
  }
  string printInfo(){
    std::cout << username <<'\t'<< passw<<'\t'<< info <<endl;
  }
  size_t MyHashCode()
  {
      std::size_t h1 = std::hash<std::string>{}(username);
      std::size_t h2 = std::hash<std::string>{}(passw);
      return h1 ^ (h2 << 1); // or use boost::hash_combine

  }
  enum infoLet { ACTIVE=1, EMPTY=2, DELETED=3 };

private:
  string passw;
  string username;
  int info;

};

class HashTable
{
  static int counter;
  public:

    HashTable( int size = 101 ){
        array.resize(nextPrime( size ));
        makeEmpty( );
    }

    bool contains( HashedObj & x )
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.setinfo(EMPTY);
    }

    bool insert( HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ] = x;
        array[ currentPos ].setinfo(ACTIVE);

            // Rehash;
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }


    bool insert( HashedObj && x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].setinfo (ACTIVE);

        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].setinfo (DELETED);
        return true;
    }
    size_t getSize(){
      return array.size();

    }
    void printTable(){
      std::cout << "Maximum" << counter<<"times probe was calculated"<<'\n';
      cout<<"**********************************"<<endl;
      for(int j=0;j<array.size();j++)
        array[j].printInfo();
      cout<<"**********************************"<<endl;
    }

    int myhash( HashedObj & x ) {
        return  x.MyHashCode() % array.size( );
    }
    enum EntryType { ACTIVE=1, EMPTY=2, DELETED=3 };

  private:

    vector<HashedObj> array;
    int currentSize;

    bool isActive( int currentPos )
      { return array[ currentPos ].getinfo() == ACTIVE; }

    int findPos( HashedObj & x )
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].getinfo() != EMPTY &&
               array[ currentPos ] != x )
        {

            counter++;
            currentPos += offset;  // Compute ith probe
            offset ++;
            if( currentPos >= array.size( ) )
                currentPos=currentPos%array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashedObj> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.setinfo(EMPTY);

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.getinfo() == ACTIVE )
                insert( std::move( entry ) );

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

    /**
     * Internal method to return a prime number at least as large as n.
     * Assumes n > 0.
     */
    int nextPrime( int n )
    {
        if( n % 2 == 0 )
            ++n;

        for( ; !isPrime( n ); n += 2 ) ;

        return n;
    }


};


#endif
