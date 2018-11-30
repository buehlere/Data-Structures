/*
Author: Eric Buehler
Date: 11/29/2018
filename: Word.h
Description: This file uses hash tables from SeperateChain.h to
* perform a spell checks on sentences
*/
#include <iostream>
#include "SeperateChain.h"
#include "Word.h"
using namespace std;


int main()
{

  //menu creation
  //input
  int menuOption;
  int loaded = 0;

  //different hash tables
  Word<HashTable2> test1;
  Word<HashTable1> test2;

  //menu print
  cout << "1. Load wordlist to Separate Chain Hash Table with std::hash fucntion" << endl;
  cout << "2. Load wordlist to Separate Chain Hash Table with your hash fucntion" << endl;
  cout << "3. Run Spell checker" << endl;
  cout << "Enter greater than 3 to terminate" << endl; //terminate loop

  //while loop to continue promt
  while(menuOption < 4)
  {
    cout << "Enter(1-3)>>";
    cin >> menuOption;
    cout << "\n" << endl;
    if(menuOption == 1)
    {

      //hashes with std
      cout << "Results" << endl;
      test1.hashFile("wordlist.txt");
      //test1.printHash();
      string sentence;
      cout << "................................." << endl;
      cout << "\n";
      loaded = 1;
    }
    if(menuOption == 2)
    {
      //hahses with my hash
      cout << "Results" << endl;
      test2.hashFile("wordlist.txt");
      //test2.printHash();
      string sentence;
      cout << "................................." << endl;
      cout << "\n";
      loaded = 2;
    }
    if(menuOption == 3)
    {
      //sentence check
      cin.ignore();
      string sentence;
      cout << "Enter a sentence >> ";
      getline( cin, sentence );
      cout << "You entered: '" << sentence << "'" << endl;
      if(loaded == 1)
      {
        test1.checkSentence(sentence);
      }
      else if(loaded == 2)
      {
        test2.checkSentence(sentence);
      }
      else cout << "you must load a hash table before spelling checking" << endl;

      cout << "................................." << endl;
      cout << "\n";
     }
   }



  return 0;
}
