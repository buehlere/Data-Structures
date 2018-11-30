//list.cpp


//default constructor
template <class T>
List<T>::List()
{
    data=new T [INITIAL_CAPACITY];
    capacity=INITIAL_CAPACITY;
    count=0;
}
//copy constructor
template <class T>
List<T>::List(const List<T>& src)
{
    deepCopy(src);

}
//destuctor
template <class T>
List<T>::~List()
{
  delete [] data;

}
//private function deepCopy:copy the List
template <class T>
void List<T>::deepCopy(const List<T>& src)
{

     count=src.count;
     capacity=src.capacity;
 
     data= new T [src.capacity];
     for (int i=0;i<src.count;i++)
     {
          data[i]=src.data[i];

     }

}
//private function expandCapacity
template <class T>
void List<T>::expandCapacity(int newCapacity)
{
    capacity = newCapacity*2;                       // double the capacity
    T *newlist=new T[capacity]; // allocate a new array
    for (int i=0;i<count;i++)                       // copy things from old array to new one
    {
        newlist[i]=data[i];
    }
    delete [] data;                                 // deallocate old array
    data = newlist;
}


//method:add: add the item to the list
template <class T>
void List<T>::add(T item)
{
      if(count>=capacity) // if the number of items is more than the capacity
      {
         expandCapacity(capacity*2); // expand the capacity
         T *newlist=new T [capacity]; // create a new array
         for (int i=0;i<count;i++)  // copy things
         {
             newlist[i]=data[i];
         }
         delete [] data;
       data=newlist;
      }
      data[count]=item; // add the item
      count++;

}
//method size: return the number of items in the list
template <class T>
int List<T>::size() const
{

   return count;

}
// method index: return the index of the item or -1 if not found
template <class T>
int List<T>::index(T item) const
{
    for (int i=0;i<count;i++)
    {
         if(data[i]==item)
         {
          return i;
         }
    }
    return -1;
}
//method insert: insert the item to the list at the position index
template <class T>
void List<T>::insert(int index,T item)
{
  if (index>=0 && index <= count)
 {
  if (count >= capacity) // if the number of items is bigger than capacity
  {
    capacity = capacity*2;
    T *newList = new T[capacity];
    
    for (int i=0; i<index; i++)
    {
      newList[i] = data[i];//copy the old list
    }
    newList[index] = item;
    for (int i= index+1; i <count+1; i++) // move the items after
    {
      newList[i] = data[i-1];
    }
    delete [] data;
    data = newList;
  }

  else 
  {
    T replacedItem = data[index];
    data[index] = item; // insert the item
    for (int i= count; i > index+1; i--)
    {
      data[i] = data[i-1]; //move others after
    }
    data[index+1] = replacedItem;
  }
  count++;
 }
}
// method remove: remove the item at the index
template <class T>
void List<T>::remove(int index)
{
   if(index >= 0 && index < count)
   { 
     for(int i=index;i<count-1;i++)
     {
        data[i]=data[i+1]; // move the items forward

     }
     count--;
   }
   

}
//operator []: return the item at the certain index
template <class T>
T& List<T>::operator[](int index) const
{
     if (index >=0 && index<count)
     {
     return data[index];
     }
     else
     {
        throw IndexError();

     }
    
    
     
}

// operator =: set the list to be another list
template <class T>
List<T>& List<T>::operator=(const List<T>& src)
{
    if(&src != this)
    {
      delete [] data;
      deepCopy(src);
    }
    return *this;

}
//operator +=:concatenation operator that combines two list together
template <class T>
List<T>& List<T>::operator+=(const List<T>& src)
{
    for (int i=0; i< src.count; i++)
    {
      this->add(src.data[i]);
    }
    return *this;
}



//method toString: return a string version of the list
template <class T>
std::string List<T>::toString()const
{
   std::stringstream ss;
   ss<<"[";
   for(int i=0;i<count-1;i++)
   {
     ss<<data[i]<<",";
     
   }
   ss<<data[count-1]<<"]";
   return ss.str();

}
//operator << allows cout 
template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    os << list.toString();
   
    return os;

}
 
