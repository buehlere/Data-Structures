/*
Author: Eric Buehler
Date: 11/29/2018
filename: Word.h
*/
#ifndef WORD_H
#define WORD_H

//structs
#include <vector>
#include <list>
#include <string>

//tools
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>

//mine
#include "SeperateChain.h"
using namespace std;


//
// CONSTRUCTION:
// The class constructs a hash table from a text file using either Table1 or
// Table2 from SeperateChain.h. The class can perform spell checks on strings
// by referencing the text file.
//
// ******************PUBLIC OPERATIONS*********************
// bool hashFile(string filename)  --> loads text file to hash table.
// void checkSentence( strint sentence )--> check if words are in the dictionary
// void printHash( )  ---> prints hash table

template<typename T>
class Word
{
  public:
    Word()
    {
      /*empty constructor, used to declare the type of hash table that
      should be used.*/
    }


    void checkSentence(string sentence)
    {
      /**
      * Takes a string of words and checks to see if they are in the
      * provided text file. If they are not, it provides suggestions
      */

      //uses iss stream to obtain words
      istringstream iss(sentence);
      string word;

      //dummy to see the sentence contains mistakes
      bool trigger = 0;

      //loops through words in string
      while(iss >> word)
      {
          if(!table.contains(word))
          {
            trigger = 1;
            cout << "word not found: " << word << endl;

            //finds words suggestions
            swapMethod(word);
            addMethod(word);
            cout << "Perhaps you meant: " << endl;

            //prints suggestions
            printSuggestions();

            //clears suggestions for next word
            suggestion.clear();
          }
      }
      if(trigger = 0)
      {
        cout << "All words are correct" << endl;
      }
    }

    void hashFile(string filename)
    {
      /**
      * takes a filename and reads it into a hash table.
      * The hash table used is determined by the constructor.
      */

      //open and read file
      ifstream file;
      file.open (filename);
      if (!file.is_open()) return;

      //insert into hash table
      string word;
      while (file >> word)
      {
        table.insert(word);
      }
      table.printSummary();
    }

    void printHash()
    {
      /**
      * prints hash table
      */
      table.printTable();
    }





  private:
    T table; //templated table
    vector<string> suggestion;
    string abc = "abcdefghijklmnopqrstuvwxyz";


    void swapMethod(string word)
    {
      /**
      * provides spelling suggestions by swapping each adjacent pair of
      * characters in the word, and looking to see if the new word is in
      * the provided text file.
      */
      for(int i = 0; i < word.length()-1; i++)
      {
        //swaps
        string swap = word;
        char first = swap[i];
        swap[i] = swap[i + 1];
        swap[i + 1] = first;

        //checks table
        if(table.contains(swap))
        {
          suggestion.push_back(swap);
        }
      }
    }

    void addMethod(string word)
    {
      /**
      * provides spelling suggestions by adding a letter between each adjacent
      * pair of characters in the word.
      */

      //in front of word
      for(int i = 0; i < abc.length(); i++)
      {
         string added = word;
         if(table.contains(abc[i] + added))
         {
           suggestion.push_back( abc[i] + added );
         }
      }

      //in between adjacent pairs
      for(int i = 0; i < word.length(); i++)
      {
        for(int j = 0; j < abc.length(); j++)
        {
          string added = word;
          added.insert(i,1, abc[j]);
          if(table.contains(added))
          {
            suggestion.push_back(added);
          }
        }
      }

      //at end of word
      for(int i = 0; i < abc.length(); i++)
      {
        string added = word;
        if(table.contains(added + abc[i]))
        {
          suggestion.push_back( added + abc[i] );
        }
      }
    }

    void printSuggestions()
    {
      /**
      * provides spelling suggestions by adding a letter between each adjacent
      * pair of characters in the word.
      */
      for(int i = 0; i < suggestion.size(); i++ )
      {
        cout << suggestion[i] << endl;
      }
    }



};

#endif
