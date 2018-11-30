//Node.h
//Author: Eric Buehler and Wei Wu
//Date: 10/31/2018
// Node.h: This file defines our node type for our BST.
#ifndef NODE_H
#define NODE_H

#include<iostream>
#include"list.h"
class IndexBST;
//definition of the node class
template<typename NODETYPE>
class Node {
   friend class IndexBST;
public:
   // constructor
   Node(const NODETYPE& d)
   {
      parent=NULL;
      leftPtr=NULL;
      rightPtr=NULL;
      data=d;
      occurrence=1;


   }
   // return copy of node's data
   NODETYPE getData() const {return data;}
private:
   Node<NODETYPE>* leftPtr; // pointer to left subtree
   Node<NODETYPE>* rightPtr; // pointer to right subtree
   Node<NODETYPE>* parent; // pointer to parent node
   NODETYPE data;
   int occurrence;
   List<int> line;
};
#endif
