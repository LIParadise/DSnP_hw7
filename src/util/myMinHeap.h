/****************************************************************************
  FileName     [ myMinHeap.h ]
  PackageName  [ util ]
  Synopsis     [ Define MinHeap ADT ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2014-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef MY_MIN_HEAP_H
#define MY_MIN_HEAP_H

#include <algorithm>
#include <vector>
#include <utility>

template <class Data>
class MinHeap
{
public:
   MinHeap(size_t s = 0) { if (s != 0) _data.reserve(s); }
   ~MinHeap() {}

   void clear() { _data.clear(); }

   // For the following member functions,
   // We don't respond for the case vector "_data" is empty!
   const Data& operator [] (size_t i) const { return _data[i]; }   
   Data& operator [] (size_t i) { return _data[i]; }

   size_t size() const { return _data.size(); }

   // TODO
   const Data& min() const;
   void insert(const Data& );
   void delMin() { }
   void delData(size_t i) { }

private:
   // DO NOT add or change data members
   vector<Data>   _data;
   
   // 0 begin root of the heap.
   // (2*n)+1 --> left child.
   // (2*n)+2 --> right child.
};

template <typename T>
const T&
MinHeap<T>::min() const
{
  return (*(_data.begin()));
}

template <typename T>
void
MinHeap<T>::insert( const T& other )
{
  size_t s = _data.size();
  size_t parent;
  _data.push_back( other );
  while( s != 0 )
  {
    parent = (s-1)/2;
    if( _data[parent] < other )
      break;
    _data[s] = move( _data[parent] );
    s = parent;
  }
  _data[s] = other;
}
#endif // MY_MIN_HEAP_H
