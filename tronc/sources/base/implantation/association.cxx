// association.cxx

#include "composition.h"

template <class T> inline Association<T>& 
Association<T>::operator =(const Composition<T>& _x)
{

  pt = (T *)_x ;
  return *this ;
}

template <class T> inline Booleen 
Association<T>::operator == (const Composition<T>& _x) const 
{
  return pt == (T *)_x ;
}

template <class T> inline Booleen 
Association<T>::operator != (const Composition<T>& _x) const
{
  return pt == (T *)_x ;
}

template <class T> inline 
Association<T>::Association(const Composition<T>& _x)
  : pt((T *)_x)
{}

template <class T> inline T* 
Association<T>::operator ->() const {

  if (pt == NULL) {

    cout << "Association::->" << endl ;
    throw Exception("Association::->") ;
  }
	
  return pt ;
	
}

	
