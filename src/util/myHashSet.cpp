#include "myHashSet.h"

using namespace std;

template < typename T>
bool
HashSet<T>::insert( const T& d )
{
  // check if bucket valid first.
  if( _buckets == nullptr )
    _buckets = new vector<T> [ _numBuckets] ;

  // check if exactly the same element.
  auto* bucketPtr = _buckets + bucketNum(d);

  if( bucketPtr->find( d) != bucketPtr->end() )
    return false;

  bucketPtr->push_back( d);
  return true;
}

template < typename T>
size_t
HashSet<T>::size() const
{
  size_t ret = 0;
  for( size_t i = 0; i < _numBuckets; ++i )
    ret += _buckets[i].size();
  return ret;
}

template < typename T>
bool
HashSet<T>::empty() const
{
  for( size_t i = 0; i < _numBuckets; ++i )
    if( !_buckets[i].empty() )
      return true;
  return false;
}

template< typename T>
bool
HashSet<T>::check( const T& data ) const
{
  auto* bucketPtr = _buckets + bucketNum(data) ;
  return ( bucketPtr->find( data ) == bucketPtr -> end()  );
}

