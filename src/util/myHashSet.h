/****************************************************************************
  FileName     [ myHashSet.h ]
  PackageName  [ util ]
  Synopsis     [ Define HashSet ADT ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2014-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef MY_HASH_SET_H
#define MY_HASH_SET_H

#include <vector>
#include <algorithm>

using namespace std;

//---------------------
// Define HashSet class
//---------------------
// To use HashSet ADT,
// the class "Data" should at least overload the "()" and "==" operators.
//
// "operator ()" is to generate the hash key (size_t)
// that will be % by _numBuckets to get the bucket number.
// ==> See "bucketNum()"
//
// "operator ==" is to check whether there has already been
// an equivalent "Data" object in the HashSet.
// Note that HashSet does not allow equivalent nodes to be inserted
//
template <class Data>
class HashSet
{
public:
   HashSet(size_t b = 0) : _numBuckets(0), _buckets(nullptr) { if (b != 0) init(b); }
   ~HashSet() { reset(); }

   // TODO: implement the HashSet<Data>::iterator
   // o An iterator should be able to go through all the valid Data
   //   in the Hash
   // o Functions to be implemented:
   //   - constructor(s), destructor
   //   - operator '*': return the HashNode
   //   - ++/--iterator, iterator++/--
   //   - operators '=', '==', !="
   //
   class iterator
   {
      friend class HashSet<Data>;

   public:
      iterator( const typename vector<Data>::iterator& it,
          size_t s = 0, HashSet<Data>* const ptr = nullptr):
        _itor( it), _bucketIdx(s), _caller(ptr) {}

      iterator() :
        _bucketIdx(0), _caller(nullptr) {}

      const Data& operator * () const ;
      iterator& operator ++ () ;
      iterator& operator -- () ;
      iterator  operator ++ (int) ;
      iterator  operator -- (int) ;
      iterator& operator =  ( const iterator& i) ;
      bool operator != (const iterator& i) const ;
      bool operator == (const iterator& i) const ;
   private:
      typename vector<Data>::iterator _itor;
      size_t                          _bucketIdx;
      HashSet<Data>*                  _caller;
   };

   void init(size_t b) { _numBuckets = b; _buckets = new vector<Data>[b]; }
   void reset() {
      _numBuckets = 0;
      if (_buckets) { delete [] _buckets; _buckets = nullptr; }
   }
   void clear() {
      for (size_t i = 0; i < _numBuckets; ++i) _buckets[i].clear();
   }
   size_t numBuckets() const { return _numBuckets; }

   vector<Data>& operator [] (size_t i) { return _buckets[i]; }
   const vector<Data>& operator [](size_t i) const { return _buckets[i]; }

   // TODO: implement these functions
   //
   // Point to the first valid data
   iterator begin() const ;
   // Pass the end
   iterator end() const ;
   // return true if no valid data
   bool empty() const ;
   // number of valid data
   size_t size() const ;

   // check if d is in the hash...
   // if yes, return true;
   // else return false;
   bool check(const Data& d) const ;

   // query if d is in the hash...
   // if yes, replace d with the data in the hash and return true;
   // else return false;
   bool query(Data& d) const ;

   // update the entry in hash that is equal to d (i.e. == return true)
   // if found, update that entry with d and return true;
   // else insert d into hash as a new entry and return false;
   bool update(const Data& d) ;

   // return true if inserted successfully (i.e. d is not in the hash)
   // return false is d is already in the hash ==> will not insert
   bool insert(const Data& d);

   // return true if removed successfully (i.e. d is in the hash)
   // return fasle otherwise (i.e. nothing is removed)
   bool remove(const Data& d) ;

   // =============helper functions============================

private:
   // Do not add any extra data member
   size_t            _numBuckets;
   vector<Data>*     _buckets;

   size_t bucketNum(const Data& d) const {
      return (d() % _numBuckets); }
};

template < typename T>
bool
HashSet<T>::insert( const T& d )
{
  // check if bucket valid first.
  if( _buckets == nullptr )
    _buckets = new vector<T> [ _numBuckets] ;

  // check if exactly the same element.
  auto* bucketPtr = _buckets + bucketNum(d);

  if( find( bucketPtr->begin(), bucketPtr->end(), d ) !=
      bucketPtr->end() ){
    return false;
  }

  bucketPtr->push_back( d);
  return true;
}

template < typename T>
size_t
HashSet<T>::size() const
{
  if( _buckets == nullptr )
    return 0;
  size_t ret = 0;
  for( size_t i = 0; i < _numBuckets; ++i )
    ret += _buckets[i].size();
  return ret;
}

template < typename T>
bool
HashSet<T>::empty() const
{
  if( _buckets == nullptr )
    return true;
  for( size_t i = 0; i < _numBuckets; ++i )
    if( !_buckets[i].empty() )
      return true;
  return false;
}

template< typename T>
bool
HashSet<T>::check( const T& other ) const
{
  if( _buckets == nullptr )
    return false;
  auto* bucketPtr = _buckets + bucketNum(other) ;
  return ( bucketPtr->find( other ) == bucketPtr -> end()  );
}

template <typename T>
bool
HashSet<T>::query( T& other ) const
{
  if( _buckets == nullptr )
    return false;
  auto* bucketPtr = _buckets + bucketNum(other) ;
  auto  itor = find_if( bucketPtr->begin(), bucketPtr->end(),
                       [&other] ( const T& stored_data ) -> bool
                       {
                         return (other == stored_data);
                       } );
  if( itor != bucketPtr -> end() )
  {
    other = (*itor);
    return true;
  }
  return false;
}

template <typename T>
  bool
HashSet<T>::update( const T& other )
{
  if( _buckets == nullptr )
    return false;

  auto* bucketPtr = _buckets + bucketNum(other) ;
  for( auto it = bucketPtr->begin(); it != bucketPtr->end(); ++it )
  {
    if( *it == other )
    {
      *it = other;
      return true;
    }
  }
  bucketPtr->push_back( other);
  return false;
}

template <typename T>
  bool
HashSet<T>::remove( const T& other ) 
{
  if( _buckets == nullptr )
    return false;
  auto* bucketPtr = _buckets + bucketNum(other) ;
  for( auto it = bucketPtr->begin(); it != bucketPtr->end(); ++it )
  {
    if( *it == other )
    {
      swap( (*it), (*(bucketPtr->end() -1) ) );
      bucketPtr -> pop_back();
      return true;
    }
  }
  return false;
}

template <typename T>
typename HashSet<T>::iterator
HashSet<T>::begin() const 
{
  if( _buckets == nullptr )
    return vector<T>().begin();
  else
    return iterator(_buckets[0].begin(), 0,
                    const_cast<HashSet<T>*> (this) );
}

template <typename T>
typename HashSet<T>::iterator
HashSet<T>::end() const 
{
  if( _buckets == nullptr )
    return vector<T>().end();
  else
    return iterator(_buckets[_numBuckets-1].end(),
                    _numBuckets-1,
                    const_cast<HashSet<T>*> (this) );
}

template <typename T>
const T&
HashSet<T>::iterator::operator * () const 
{
  return (*_itor );
}

template <typename T>
  typename HashSet<T>::iterator&
HashSet<T>::iterator::operator ++ () // pre-increment operator
{
  if( _caller == nullptr )
    return (*this);

  _itor++;
  while( _itor == (*_caller)[_bucketIdx].end()
        && _bucketIdx < _caller->numBuckets()-1 )
  {
    ++ _bucketIdx;
    _itor = (*_caller)[_bucketIdx].begin() ;
  }
  return (*this);
}

template <typename T>
  typename HashSet<T>::iterator
HashSet<T>::iterator::operator ++ (int dummy) 
  // post-increment operator
{
  if( _caller == nullptr )
    return (*this);

  auto tmp = (*this);
  operator ++ ();
  return tmp;
}

template <typename T>
  typename HashSet<T>::iterator&
HashSet<T>::iterator::operator -- () // pre-decrement operator
{
  if( _caller == nullptr )
    return (*this);

  while( _itor == (*_caller)[_bucketIdx].begin() 
        && _bucketIdx > 0)
  {
    _bucketIdx --;
    _itor = (*_caller ) [_bucketIdx].end();
  }
  _itor--;
  return (*this);
}

template <typename T>
  typename HashSet<T>::iterator
HashSet<T>::iterator::operator -- (int dummy) 
  // post-decrement operator
{
  if( _caller == nullptr )
    return (*this);

  auto tmp = (*this);
  operator -- ();
  return tmp;
}

template <typename T>
bool
HashSet<T>::iterator::operator == ( const HashSet<T>::iterator&
                                   other_itor ) const
{
  return ( (_itor) == (other_itor._itor) );
}

template <typename T>
bool
HashSet<T>::iterator::operator != ( const HashSet<T>::iterator&
                                   other_itor ) const
{
  return ( ! ( operator == ( other_itor ) ) );
}

template <typename T>
typename HashSet<T>::iterator&
HashSet<T>::iterator::operator = ( const HashSet<T>::iterator&
                                  other_itor )
{
  if( this != &other_itor )
  {
    _itor      = other_itor._itor;
    _bucketIdx = other_itor._bucketIdx;
    _caller    = other_itor._caller;
  }
}

#endif // MY_HASH_SET_H
