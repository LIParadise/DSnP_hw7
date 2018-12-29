#include "myHashSet.h"

template < typename T>
bool
HashSet<T>::insert( const Data& d )
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
