// composition.cxx

#include "association.h"

template <class T> inline Booleen 
Composition<T>::operator == (const Association<T>& _p)
{
  return pt == (T *)_p ;
}

template <class T> inline Booleen 
Composition<T>::operator !=(const  Association<T>& _p)
{
  return pt != _p.get_ptr() ;
}
