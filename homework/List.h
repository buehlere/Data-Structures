/*
*Eric Buehler
*Dr. Sevkli
*Homework #3
*9-13-2018
*List.h
*====================
* This is a singly linked list implementation. I'm adding the addAll and
* removeAll methods. See functions for details.
*/

// Randomly generate numbers between 1 and 1000 for user to guess.
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "ListNode.h" // ListNode class definition

template<typename NODETYPE>
class List {
public:
   // destructor
   ~List() {
      if (!isEmpty()) { // List is not empty
         //std::cout << "Destroying nodes ...\n";

         ListNode<NODETYPE>* currentPtr{firstPtr};
         ListNode<NODETYPE>* tempPtr{nullptr};

         while (currentPtr != nullptr) { // delete remaining nodes
            tempPtr = currentPtr;
            //std::cout << tempPtr->data << '\n';
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
         }
      }

      //std::cout << "All nodes destroyed\n\n";
   }

   // insert node at front of list
   void insertAtFront(const NODETYPE& value) {
      ListNode<NODETYPE>* newPtr{getNewNode(value)}; // new node

      if (isEmpty()) { // List is empty
         firstPtr = lastPtr = newPtr; // new list has only one node
      }
      else { // List is not empty
         newPtr->nextPtr = firstPtr; // point new node to old 1st node
         firstPtr = newPtr; // aim firstPtr at new node
      }
   }

   // insert node at back of list
   void insertAtBack(const NODETYPE& value) {
      ListNode<NODETYPE>* newPtr{getNewNode(value)}; // new node

      if (isEmpty()) { // List is empty
         firstPtr = lastPtr = newPtr; // new list has only one node
      }
      else { // List is not empty
         lastPtr->nextPtr = newPtr; // update previous last node
         lastPtr = newPtr; // new last node
      }
   }

   // delete node from front of list
   bool removeFromFront(NODETYPE& value) {
      if (isEmpty()) { // List is empty
         return false; // delete unsuccessful
      }
      else {
         ListNode<NODETYPE>* tempPtr{firstPtr}; // hold item to delete

         if (firstPtr == lastPtr) {
            firstPtr = lastPtr = nullptr; // no nodes remain after removal
         }
         else {
            firstPtr = firstPtr->nextPtr; // point to previous 2nd node
         }

         value = tempPtr->data; // return data being removed
         delete tempPtr; // reclaim previous front node
         return true; // delete successful
      }
   }

   // delete node from back of list

   bool removeFromBack(NODETYPE& value) {
      if (isEmpty()) { // List is empty
         return false; // delete unsuccessful
      }
      else {
         ListNode<NODETYPE>* tempPtr{lastPtr}; // hold item to delete

         if (firstPtr == lastPtr) { // List has one element
            firstPtr = lastPtr = nullptr; // no nodes remain after removal
         }
         else {
            ListNode<NODETYPE>* currentPtr{firstPtr};

            // locate second-to-last element
            while (currentPtr->nextPtr != lastPtr) {
               currentPtr = currentPtr->nextPtr; // move to next node
            }

            lastPtr = currentPtr; // remove last node
            currentPtr->nextPtr = nullptr; // this is now the last node
         }

         value = tempPtr->data; // return value from old last node
         delete tempPtr; // reclaim former last node
         return true; // delete successful
      }
   }

   bool destroy() {
      if (isEmpty()) { // List is empty
         return false; // delete unsuccessful
      }
      else {
         ListNode<NODETYPE>* tempPtr{lastPtr}; // hold item to delete

         if (firstPtr == lastPtr) { // List has one element
            firstPtr = lastPtr = nullptr; // no nodes remain after removal
         }
         else {
            ListNode<NODETYPE>* currentPtr{firstPtr};

            // locate second-to-last element
            while (currentPtr->nextPtr != lastPtr) {
               currentPtr = currentPtr->nextPtr; // move to next node
            }

            lastPtr = currentPtr; // remove last node
            currentPtr->nextPtr = nullptr; // this is now the last node
         }

         delete tempPtr; // reclaim former last node
         return true; // delete successful
      }
   }

   // is List empty?

   bool isEmpty() const {
      return firstPtr == nullptr;
   }

   // display contents of List
   void print() const {
      if (isEmpty()) { // List is empty
         std::cout << "the list is empty\n\n";
         return;
      }

      ListNode<NODETYPE>* currentPtr{firstPtr};

      std::cout << "list is: ";

      while (currentPtr != nullptr) { // get element data
         std::cout << currentPtr->data << ' ';
         currentPtr = currentPtr->nextPtr;
      }

      std::cout << "\n\n";
   }


  template <typename T> //declaring template type T
  bool addAll(List<T>& otherList)
   /*
   Summary: adds the unique elements of Otherlist to the end of a list.
   * ---------------------
   Input:
   -otherList: a list that will be added to the end of another
   Output:
   -True: If the list has changed.
   -False: If the list hasn't changed.
   */
   {
     //empty case
     ListNode<NODETYPE>* OtherCurrentPtr = otherList.firstPtr; //other element
     ListNode<NODETYPE>* currentPtr = firstPtr; //first element
     bool flag = true;
     if(otherList.isEmpty()) //empty case
     {
       return false;
     }
     if(isEmpty()) //empty case
     {
       while(OtherCurrentPtr != nullptr)
       {
         insertAtBack(OtherCurrentPtr->data);
         OtherCurrentPtr = OtherCurrentPtr->nextPtr;
       }
       return true;
     } else
     {
       while(OtherCurrentPtr != nullptr) //double while loops to compare lists
       {
         currentPtr = firstPtr;
         flag = true; //flag to check if element wans't the same
         while(currentPtr != nullptr && flag == true)
         {
           if(currentPtr->data == OtherCurrentPtr->data)
           {
              flag = false;
           }
           currentPtr = currentPtr->nextPtr;
         }
         if(flag == true)
         {
           insertAtBack(OtherCurrentPtr->data); //add element 
         }
         OtherCurrentPtr = OtherCurrentPtr->nextPtr;
       }
       return true;
     }
   }

 template <typename T> //declaring template type T
 bool removeAll(List<T>& otherList)
  /*
  Summary: Removes all the elements in otherList from this list
  * ---------------------
  Input:
  -otherList: a list whose elements will be removed from this list
  Output:
  -True: If the list has changed.
  -False: If the list hasn't changed.
  */
  {
    //empty case
    ListNode<NODETYPE>* OtherCurrentPtr = otherList.firstPtr; //other element
    ListNode<NODETYPE>* currentPtr = firstPtr; //current element
    ListNode<NODETYPE>* prev = nullptr; //keep track of previous elemet
    if(otherList.isEmpty() || isEmpty()) //empty case
    {
      return false;
    } else
    {
      while(OtherCurrentPtr != nullptr) //while loops for comparison
      {
        currentPtr = firstPtr;
        prev = nullptr;
        while(currentPtr != nullptr)
        {
          if(currentPtr->data == OtherCurrentPtr->data && prev == nullptr)
          //deleting first element
          {
            ListNode<NODETYPE>* temp = currentPtr; //store value
            currentPtr = currentPtr->nextPtr;
            firstPtr = currentPtr; //update head
            delete temp; //delete
          }
          //regular case for deleting from the list
          else if(currentPtr->data == OtherCurrentPtr->data)
          {
            ListNode<NODETYPE>* temp = currentPtr;
            currentPtr = currentPtr->nextPtr;
            prev->nextPtr = currentPtr; //point around deleted element
            delete temp;
          }
          //
          else {
          //if no matches advance list
          prev = currentPtr;
          currentPtr = currentPtr->nextPtr;
          }
        }
        OtherCurrentPtr = OtherCurrentPtr->nextPtr;
      }
      return true;
    }
 }




private:
   ListNode<NODETYPE>* firstPtr{nullptr}; // pointer to first node
   ListNode<NODETYPE>* lastPtr{nullptr}; // pointer to last node

   // utility function to allocate new node
   ListNode<NODETYPE>* getNewNode(const NODETYPE& value) {
      return new ListNode<NODETYPE>{value};
   }
};

#endif
