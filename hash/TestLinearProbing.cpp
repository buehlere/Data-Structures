#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "LinearProbing.h"

using namespace std;
 string generateRandomName(int length){
    	string alphabet ("abcdefghijklmnopqrstuvwxyz");
    	int n = alphabet.size();
    	string result;
    	for (int i=0; i<length; i++) {
    	    result = result + alphabet[(rand()%n)]; //13

      }
    	return result;
  }

  string generatePassw(int length){
       string numbers("0123456789");
       int n = numbers.size();
       string result;
       for (int i=0; i<length; i++) {
           result = result + numbers[(rand()%n)];

       }
       return result;
   }
    // Simple main
int HashTable::counter=0;
int main( )
{
  //srand (time(NULL));
  srand(12); // to see which words are being generating.
  HashTable h1(11);
  std::string user;
  std::string no;

  for (int i=0;i<17;i++){
       user=generateRandomName(4+rand()%5);
       no=generatePassw(6);
       HashedObj newRecord(no,user);
       h1.insert(newRecord);
 }
    h1.printTable();

    HashedObj deleteRecord("139984","nwsy");
    if (h1.remove(deleteRecord)){
       std::cout << "Deleted Record:" << '\n';
       deleteRecord.printInfo();
    }
    h1.printTable();
    return 0;
}
