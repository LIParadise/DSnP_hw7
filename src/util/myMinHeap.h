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
   void delMin();
   void delData(size_t );

private:
   // DO NOT add or change data members
   vector<Data>   _data;

   // helper functions.

   // fix the heap. would call heapFixUp or heapFixDown;
   void heapFix    ( size_t );

   // fixing ill-formed heap caused by deletion.
   // shall not be used to fix update of node.
   void heapFixDown( size_t );

   // counterpart for heapFixDown
   void heapFixUp  ( size_t );
   
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
    _data[s] = _data[parent] ;
    s = parent;
  }
  _data[s] = other;
}

template <typename T>
void
MinHeap<T>::delMin()
{
  swap( _data[0], _data[_data.size()-1] );
  _data.erase(_data.back());
  heapFix();
}

template <typename T>
void
MinHeap<T>::delData( size_t s )
{
  swap( _data[s], _data[_data.size()-1] );
  _data.pop_back();
  heapFix( s );
}

template <typename T>
void
MinHeap<T>::heapFixDown( size_t idx)
{
  // just fix downwards.
  // other part of the heap is still in valid state,
  // thus just compare it to its descendants.
  if( !( idx<_data.size()) )
    return;

  while (idx < _data.size())
  {
    size_t tmp     = idx;
    size_t childL  = 2*idx + 1;
    size_t childR  = 2*idx + 2;
    if( childL < _data.size() )
      if( _data[childL] < _data[tmp] )
        tmp = childL;
    if( childR < _data.size() )
      if( _data[childR] < _data[tmp] )
        tmp = childR;
    if( tmp == idx )
      break;
    swap( _data[idx], _data[tmp] );
    idx = tmp;
  }
}

template <typename T>
void
MinHeap<T>::heapFixUp( size_t idx )
{
  // just fix upwards.
  // other part of the heap is still in valid state,
  // thus just compare it to its parent.
  if( idx == 0 )
    return;

  while( idx != 0 )
  {
    size_t parent = (idx-1)/2;
    if( _data[idx] < _data[parent] )
    {
      swap( _data[idx], _data[parent] );
      idx = parent;
    }
  }
}

template <typename T>
void
MinHeap<T>::heapFix( size_t idx )
{
  size_t parent = (idx-1)/2;

  if( idx != 0 )
    if( _data[idx] < _data[parent] )
    {
      heapFixUp( idx );
      return;
    }
  heapFixDown( idx );
  return ;
}
#endif // MY_MIN_HEAP_H
