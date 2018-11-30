//IndexBST.h
//Author: Eric Buehler and Wei Wu
//Date: 10/31/2018
// indexBST.h: This file defines our BST tree class 
#ifndef INDEXBST_H
#define INDEXBST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <queue>
#include "Node.h"

class IndexBST
{
      public:
      IndexBST()
      {
        //if a file is not provided, an empty tree is constructed
        root=NULL;

      }
      IndexBST(std::string filename)
      {
        /*
        Description:
        This constructor creates a tree such that each node has data fields
        to store a word, the count of occurrences of that word in a document
        file, and the line number for each occurrence.
        -optional input: at .txt file.
        -output: a tree constructed as described above.

        Time Complexity: O(n^3log(n))
        For each character in the string of each word in each line of the text
        file, we remove any alphanumeric characters. Thus we have three nested
        loops. We also search for the word log(n).

        */
        root=NULL; //set root to null
        int lineNumber = 0;
        std::ifstream file(filename); //put file into ifstream
        std::string lines;
        while (std::getline(file, lines))
        {
          /*
          Using getline on the the ifstream, we can extract the lines from the
          text file.
          */
          lineNumber += 1; //keeping track of line numbers
          std::istringstream iss(lines); //lines into isstream
          std::string word;
          while(std::getline(iss,word,' '))
          {
            /*
            using a delimiter of ' ' we can extract the words from each
            line of the text file.
            */

            //controlling for lower and upper case
            std::transform(word.begin(),word.end(),word.begin(),::tolower);

            //removing non-alphanumerics
            word.erase(std::remove_if(word.begin(), word.end(),
                  [](char ch){ return !::iswalnum(ch); }), word.end());

            //search for word in tree structure
            Node<std::string>* result= search(word);

             if(result == NULL)
             {
               /*
                 if the word isn't in the tree structure, we create a new
                 node for the word.
               */
                Node<std::string>* parentP=NULL;
                Node<std::string>* current=root;
                if (current == NULL)
                {
                    root = new Node<std::string>(word);
                    (root->line).add(lineNumber);
                    break;
                }
                while(current!=NULL)
                {
                 /*
                   we use a while() loop to find the correct place for
                   our new word. std::string allows us to compare words to
                   place the words in alphabetic order.
                 */
                  parentP=current;

                  if(word < current->data)
                  {
                  current=current->leftPtr; //less than current, left
                  }
                  else
                  {
                  current=current->rightPtr; //greater than, right
                  }
                }
               if (parentP->data > word)
              {
                parentP->leftPtr= new Node<std::string>(word);
                (parentP->leftPtr->line).add(lineNumber);
              }
              else if (parentP->data < word)
              {
                parentP->rightPtr= new Node<std::string>(word);
                (parentP->rightPtr->line).add(lineNumber);
              }
            }
             else
             {
               /*
                if the word is already in the tree, then we update the list
                of that words node with the new line number.
               */
               if (((result->line).index(lineNumber))==-1)
               {
                 //check to see if line number is already included.
                (result->line).add(lineNumber);
               }
                result->occurrence +=1; //update occurences
             }
           }
         }
       }
      Node<std::string>* search(std::string element)
      {
        Node<std::string>* current= root;
        while (current!=NULL)
        {
           if(element < current->data)
           {
              current=current->leftPtr;
           }
           else if(element > current->data)
           {
              current=current->rightPtr;
           }
           else
           {
              return current;
           }
        }
        return current;
      }

      void inOrderTraversal() const
      {
        /*A public method that print the nodes in ascending order*/

        inOrderHelper(root);
      }
      void NumberofNodes()
      {
          /*A public method that print the total number of nodes in the tree*/
           int count1=NumberofNodesHelper(root);
           std::cout<<count1<<' ';
      }
      void height()
      {
           /*A public method that print out the height of the tree*/
           int count2=heightHelper(root);
           std::cout<<count2<<' ';
      }
    void breadthDisplay()
    {
      /*
        breadthDisplay using the breadth-first search algorithm to display
        the words at each level of the tree.
        -input: NA
        -ouput: NA, but the program displays the tree's words in a breadth
          first traversal.
        Time Complexity: T(n) = O(n)
        We must loop through all the node children, which are placed in the
        queue.
      */
      if(root == NULL)
      {
        //if the tree is empty return
        return;
      }
      //create a queue to store nodes, initialize with the root.
      std::queue<Node<std::string>*> level;
      level.push(root);
      while(level.empty() == false)
      {
        /*
          After displaying a nodes data we can store its children in a
          queue. We can loop through this queue of the node's children to
          display the nodes in a breadth-first traversal.
        */
        //assign the node at the top of the queue to a temp node.
        Node<std::string>* temp = level.front();
        temp = level.front();
        //display temp node data
        std::cout << temp->data << ' ';
        //pop of temp from queue
        level.pop();
        //put temp's children into a queue
        if(temp->leftPtr != NULL)
        {
          level.push(temp->leftPtr);
        }
        if(temp->rightPtr != NULL)
        {
          level.push(temp->rightPtr);
        }
      }
    }
    void startingLetter(char start)
    {
      /*
        This function takes as a parameter the letter in which the word
        starts, and prints all words in the tree that start with that word.
        -input= NA
        -oupt = NA, but starting helper prints all words starting with the
        given letter.
        Time Complexity: O(n)
        We must check every element in the tree to see if it starts with the
        given letter.
      */
      startingHelper(root, start);
    }

    void findmax()
    {
         /*A public method that prints out the word with the maximum occurrence*/
         Node<std::string>* result=findmaxHelper(root);
         if (result!=NULL)
         {
           std::cout<< result->data << ' ';
         }
    }
private:
      Node<std::string> *root;
      // Function that traverse the tree in ascending order
      // Time Complexity:T(n)=2*T(n\2)+1 = O(n), where n is the number of nodes
      void inOrderHelper(Node<std::string>* ptr) const
      {
       /*
           This function is to print all the nodes in the tree in order.
           parameters: given pointer


       */
       if(ptr !=NULL)
       {

        inOrderHelper(ptr->leftPtr); // call the left subtree
        std::cout<< ptr->data<<' ';  // print root data
        std::cout<< ptr->occurrence<<' ';//print  root occurrence
        std::cout<<"Line#"<<ptr->line<<std::endl; // print root linenumber
        inOrderHelper(ptr->rightPtr);// call the right subtree
       }

      }

      void startingHelper(Node<std::string>* ptr, char start) const
      {
      /*
        startingHelper uses an inorder traversal of the tree. We check
        the first element of the pointer's data to see if it matches
        the starting letter. The fucntion is called by startingLetter().
        -input: a node of the tree, the starting letter we are looking for
        -output: NA, but it prints the matching nodes information.
        Time Complexity: T(n) = O(n). See startingLetter().
      */
       if(ptr !=NULL)
       {
         startingHelper(ptr->leftPtr, start);
         if(ptr->data[0] == start)
         {
           //print node information if it matches letter
           std::cout<< ptr->data<<' ';
           std::cout<< ptr->occurrence<<' ';
           std::cout<<"Line#"<<ptr->line<<std::endl;
         }
         startingHelper(ptr->rightPtr,start);
       }
     }
     //Method that compute the total number of nodes of the tree
     //Time complexity: T(n)=2*T(n\2)+1 = O(n)
     int NumberofNodesHelper(Node<std::string>* rootPtr)
     {
     // return number of nodes in the tree
       if (rootPtr !=NULL)
       return 1+NumberofNodesHelper(rootPtr->leftPtr)+NumberofNodesHelper(rootPtr->rightPtr);
       else
       return 0;
    }
    //Method that compute the height of the tree
    //Time complexity: T(n)=2*T(n/2)+1 = O(n)
     int heightHelper(Node<std::string>* rootPtr)
     {
         if (rootPtr == NULL)
         {
             return 0;
         }
         else
         return std::max(heightHelper(rootPtr->leftPtr),heightHelper(rootPtr->rightPtr))+1;
     }
     // Method to find the word that has the maximum occurrence
     //Time Complexity: T(n)=2*T(n/2)+c = O(n)
     Node<std::string>* findmaxHelper(Node<std::string>* Ptr)
     {
         /*
            This function is to find the node with the maximum occurrence in the tree.
            Parameters: given pointer
            Return: the node with the maximum occurrence.


        */
         if(Ptr!=NULL)
         {
            Node<std::string>* current= Ptr;
            int maxnumber=Ptr->occurrence;
            Node<std::string>* left=findmaxHelper(Ptr->leftPtr); // find the left pointer
            Node<std::string>* right=findmaxHelper(Ptr->rightPtr);// find the right pointer
            if (left != NULL && right !=NULL) // if they are not NULL
            {
               int leftmax=left->occurrence; // get the occurrence
               int rightmax=right->occurrence;
               if(leftmax > maxnumber) //compare with left pointer
               {
                 maxnumber=leftmax;
                 current=left;
               }
               if (rightmax > maxnumber)//compare with right pointer
               {
                 maxnumber=rightmax;
                 current=right;
               }

           }
           return current;
         }
         else
         {
           return Ptr;
         }

     }



};
#endif
