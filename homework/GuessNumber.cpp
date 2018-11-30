/*
*Eric Buehler
*Dr. Sevkli
*Homework #1
*9-1-2018
*GuessNumber.cpp
*====================
* Adding a data structure to the Guess the Number game.
* I choose to use a stack to limit the number of guesses a player
* has.
*/

// Randomly generate numbers between 1 and 1000 for user to guess.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack> //data structure I'm adding.

using namespace std;

void guessGame(); // function prototype
bool isCorrect( int, int, stack<int> & t); // function prototype


int main()
{
   // srand( time( 0 ) ); // seed random number generator
   guessGame();

   return 0; // indicate successful termination

} // end main

// guessGame generates numbers between 1 and 1000
// and checks user's guess
void guessGame()
{
   int answer; // randomly generated number
   int guess; // user's guess
   char response; // 'y' or 'n' response to continue game
   stack<int> guesses; //build a stack with the number of guesses allowed.



   // loop until user types 'n' to quit game
   do {
      //adding guesses
      guesses.push(0);
      guesses.push(1);
      guesses.push(2);
      guesses.push(3);
      guesses.push(4);
      guesses.push(5);
      guesses.push(6);
      guesses.push(7);
      guesses.push(8);
      guesses.push(9);
      // generate random number between 1 and 1000
      // 1 is shift, 1000 is scaling factor
      answer = 1 + rand() % 1000;

      // prompt for guess
      cout << "I have a number between 1 and 1000.\n"
           << "Can you guess my number?\n"
           << "Please type your first guess." << endl << "? ";
      cin >> guess;

      // loop until correct number
      while ( !isCorrect( guess, answer, guesses ) )
         cin >> guess;

      // prompt for another game

      cout << "Would you like to play again (y or n)? ";
      cin >> response;


      cout << endl;
   } while ( response == 'y' );
} // end function guessGame

// isCorrect returns true if g equals a
// if g does not equal a, displays hint
bool isCorrect( int g, int a, stack<int> & t )
{
   if(t.top() == 0) //no guesses left; ends loop
   {
     cout << "\nSorry! You ran out of guesses.\n";
     return true;
   }
   // guess is correct
   if ( g == a )
   {
     cout << "\nExcellent! You guessed the number!\n";
     return true;
   }
   // guess is incorrect; display hint; reports remaining guesses;
   // removes a guess by popping an element off the stack.
   if ( g < a )
   {
     cout << "Too low. You have "  << t.top() << " guesses left. Try Again."
     << endl << "? ";
     t.pop(); //removes a guess
   }
   else
   {
     cout << "Too high. You have "  << t.top() << " guesses left. Try Again."
     << endl << "? ";
     t.pop();

   }
   return false;
} // end function isCorrect
