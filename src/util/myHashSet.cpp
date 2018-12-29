#include "myHashSet.h"
#include <algorithm>

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
HashSet<T>::check( const T& other ) const
{
  auto* bucketPtr = _buckets + bucketNum(other) ;
  return ( bucketPtr->find( other ) == bucketPtr -> end()  );
}

template <typename T>
bool
HashSet<T>::query( T& other ) const
{
  auto* bucketPtr = _buckets + bucketNum(other) ;
  for_each ( bucketPtr->begin(), bucketPtr->end(),
      [] ( T& data_stored_in_hash )
      {
        if( data_stored_in_hash == other )
          other = data_stored_in_hash;
        // FIXME
      }
}
