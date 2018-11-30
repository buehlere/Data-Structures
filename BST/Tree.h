// Fig. 19.22: Tree.h
// Tree class-template definition.
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <regex>
#include "TreeNode.h"



// Tree class-template definition
template<typename NODETYPE>
class Tree {
public:
   // insert node in Tree
   Tree(string name)
   {
     rootPtr=NULL;
     int lineNumber = 0;
     ifstream file(name);
     string str;
     while (std::getline(file, str))
     {
       lineNumber += 1;
       cout << lineNumber << endl;
       istringstream iss(str);
       string word;
       while(iss >> word)
       {
         if (regex_match (word, regex("[A-Za-z]*") ))
         {
           transform(word.begin(), word.end(), word.begin(), ::tolower);
           cout << word << endl;
         }
       }
       }

   }

   void insertNode(const NODETYPE& value)
   {
      insertNodeHelperIterative(value);
   }

   void NumberofNodes()
   {

     //call NumberofNodesHelper function
     //and print the return value

       int count=NumberofNodesHelper(rootPtr);
       std::cout<< count << ' ' ;

   }

   bool searchNode(NODETYPE element)
   {
     TreeNode<NODETYPE>* current = rootPtr; // Start from the root
    // fill the method
     while (current != NULL)
     {
         if (element< current->data)
         {
          current=current->leftPtr;

         }
         else if (element > current->data)
         {
         current=current->rightPtr;
         }
         else
         return true;

     }
     return false;
   }
   bool search(NODETYPE element)
   {
        TreeNode<NODETYPE>* result=searchNodeHelper(element);
        if (result!=NULL)
        {
           return true;
        }
        else
        {
           return false;
        }

   }
   bool deleteNode(const NODETYPE& value)
   {
        TreeNode<NODETYPE>* leftmost=NULL;
        TreeNode<NODETYPE>* currentPtr=searchNodeHelper(value);
        if(currentPtr == NULL)
        {
           return false;
        }
        else
        {
            if(currentPtr->leftPtr==NULL && currentPtr->rightPtr == NULL)
              {
                if(currentPtr->parent == NULL)
                {
                    rootPtr=NULL;
                }
                else if (currentPtr->parent->leftPtr==currentPtr)
                {
                    currentPtr->parent->leftPtr=NULL;
                }
                else
                {
                    currentPtr->parent->rightPtr=NULL;
                }
                delete currentPtr;
              }

            else if (currentPtr->leftPtr!=NULL && currentPtr->rightPtr==NULL)
            {
                if(currentPtr->parent->leftPtr==currentPtr)
                {
                   currentPtr->parent->leftPtr=currentPtr->leftPtr;
                }
                else
                {
                   currentPtr->parent->rightPtr=currentPtr->leftPtr;
                }
                delete currentPtr;
            }
            else if (currentPtr->leftPtr==NULL && currentPtr->rightPtr!=NULL)
            {
                if(currentPtr->parent->leftPtr == currentPtr)
                {
                   currentPtr->parent->leftPtr=currentPtr->rightPtr;
                }
                else
                {
                   currentPtr->parent->rightPtr=currentPtr->rightPtr;
                }
                delete currentPtr;
            }
            else
            {
              TreeNode<NODETYPE>* temp=currentPtr->rightPtr;
              TreeNode<NODETYPE>* successor;

              while(temp->leftPtr!=NULL)
              {
                 temp=temp->leftPtr;
              }
              successor=temp;

              if(currentPtr->rightPtr==successor)
              {
                successor->leftPtr=currentPtr->leftPtr;
                if ( successor->rightPtr == NULL)
                {
                 currentPtr->rightPtr=NULL;
                }

              }
              else
              {
                successor->parent->leftPtr=successor->rightPtr;


              }
              currentPtr->data=successor->data;
              delete successor;

            }
            return true;
        }
   }
   // begin preorder traversal of Tree
   void preOrderTraversal() const
   {
      preOrderHelper(rootPtr);
   }

   // begin inorder traversal of Tree
   void inOrderTraversal() const
   {
      // fill the method
      inOrderHelper(rootPtr);
   }

   // begin postorder traversal of Tree
   void postOrderTraversal() const
   {
      // fill the method
        postOrderHelper(rootPtr);
   }


private:
   TreeNode<NODETYPE>* rootPtr;

   int NumberofNodesHelper(TreeNode<NODETYPE>* root)
   {
     // return number of nodes in the tree
       if (root !=NULL)
       return 1+NumberofNodesHelper(root->leftPtr)+NumberofNodesHelper(root->rightPtr);
       else
       return 0;
   }

   // utility function called by insertNode; receives a pointer
   // to a pointer so that the function can modify pointer's value
   void insertNodeHelper(TreeNode<NODETYPE>** ptr, const NODETYPE& value)
   {
      // subtree is empty; create new TreeNode containing value
      if (*ptr == NULL)
      {
          *ptr = new TreeNode<NODETYPE>(value);
      }
      else
      { // subtree is not empty
             // data to insert is less than data in current node
         if (value < (*ptr)->data) {
            insertNodeHelper(&((*ptr)->leftPtr), value);
         }
         else {
            // data to insert is greater than data in current node
            if (value > (*ptr)->data) {
               insertNodeHelper(&((*ptr)->rightPtr), value);
            }
            else { // duplicate data value ignored
               std::cout << value << " dup" << std::endl;
            }
         }
      }
   }

   void insertNodeHelperIterative(const NODETYPE& value)
   {
    // write iterative insert function
       TreeNode<NODETYPE> *current = rootPtr;
       TreeNode<NODETYPE> *parentP = NULL;
       if (current==NULL)
       {
         rootPtr=new TreeNode<NODETYPE>(value);
         return;
       }
       while(current!=NULL)
       {
            parentP=current;

            if(value < current->data)
            {
               current=current->leftPtr;
            }
            else
            {
                current=current->rightPtr;
            }
      }


      if (parentP->data > value)
      {

         parentP->leftPtr= new TreeNode<NODETYPE>(value);

      }
      else
      {
         parentP->rightPtr= new TreeNode<NODETYPE>(value);
      }

   }
   TreeNode<NODETYPE>* searchNodeHelper(NODETYPE element)
   {
        TreeNode<NODETYPE>* current= rootPtr;
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
   // utility function to perform preorder traversal of Tree
   void preOrderHelper(TreeNode<NODETYPE>* ptr) const
   {
      if (ptr != NULL)
      {
         std::cout << ptr->data << ' '; // process node
         preOrderHelper(ptr->leftPtr); // traverse left subtree
         preOrderHelper(ptr->rightPtr); // traverse right subtree
      }
   }

   // utility function to perform inorder traversal of Tree
   void inOrderHelper(TreeNode<NODETYPE>* ptr) const
  {
      // fill the method
       if(ptr !=NULL)
       {

        inOrderHelper(ptr->leftPtr);
        std::cout<< ptr->data<< ' ';
        inOrderHelper(ptr->rightPtr);
       }

   }

   // utility function to perform postorder traversal of Tree
   void postOrderHelper(TreeNode<NODETYPE>* ptr) const
   {

      // fill the method
      if(ptr !=NULL)
      {
        postOrderHelper(ptr->leftPtr);
        postOrderHelper(ptr->rightPtr);
        std::cout<<ptr->data<<' ';
      }
   }

};

#endif
