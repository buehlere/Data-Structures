// Fig. 19.4: ListNode.h
// ListNode class-template definition.
#ifndef LISTNODE_H
#define LISTNODE_H

// forward declaration of class List required to announce that class 
// List exists so it can be used in the friend declaration at line 12
template<typename NODETYPE> class List;                            

template<typename NODETYPE>
class ListNode {
   friend class List<NODETYPE>; // make List a friend

public:
   explicit ListNode(const NODETYPE& info) // constructor
      : data{info}, nextPtr{nullptr} {}

   NODETYPE getData() const {return data;} // return data in node
private:
   NODETYPE data; // data
   ListNode<NODETYPE>* nextPtr; // next node in list
}; 

#endif


