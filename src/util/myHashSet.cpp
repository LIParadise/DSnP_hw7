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
  for_each ( bucketPtr->begin(), bucketPtr->end(),
            [&other] ( const T& data_stored_in_hash )
            {
              if( data_stored_in_hash == other ){
                other = data_stored_in_hash;
                return true;
              }
            } );
  return false;
}

template <typename T>
bool
HashSet<T>::update( const T& other )
{
  if( _buckets == nullptr )
    return false;
  auto* bucketPtr = _buckets + bucketNum(other) ;
  for_each ( bucketPtr->begin(), bucketPtr->end(),
            [&other] ( T& data_stored_in_hash )
            {
              if( data_stored_in_hash == other ){
                data_stored_in_hash = other;
                return true;
              }
            } );
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
      bucketPtr->erase( it );
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
    return _buckets[0].begin();
}

template <typename T>
typename HashSet<T>::iterator
HashSet<T>::end() const 
{
  if( _buckets == nullptr )
    return vector<T>().end();
  else
    return iterator(_buckets[_numBuckets-1].end(), _numBuckets-1 );
}


