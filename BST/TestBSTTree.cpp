//Author: Eric Buehler and Wei Wu
//Date: 10/31/2018
//TestBSTTree.cpp: this file tests our BST constructor and methods
#include <iostream>
#include <iomanip>
#include "indexBST.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;



int main()
{
   //testing constructor and methords for BST using ProgramDefects.txt
   IndexBST tree("ProgramDefects.txt");
   tree.inOrderTraversal();
   cout << "\n\n";
   tree.height();
   cout << "\n\n";
   tree.NumberofNodes();
   cout << "\n\n";
   tree.findmax();
   cout << "\n\n";
   tree.breadthDisplay();
   cout << "\n\n";
   tree.startingLetter('a');
   cout << "\n\n";

}
