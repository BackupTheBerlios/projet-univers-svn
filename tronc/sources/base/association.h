// ob_association.h :
// d�finition de la classe impl�mentant les pointeurs de association.

#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include "exception.h"

template <class T> class Composition ;

/*
CLASS
  Association

  Classe g�n�rique d�signant une association sur un objet.

UTILISATION
  Cette classe sert � d�signer des objets non-persistant en lecture 
  et comme retours de fonctions d'acc�s. Ainsi, lorsqu'on a besoin de d�signer 
  un objet existant on utilise cette classe.
*/
template <class T> class Association {
public:

  // ********************
  // GROUP: Constructeurs
  // ********************


  /////////////////
  // Constructeur par d�faut.
  Association()
    : pt()
  {}


  ///////////////////
  // Constructeur, prends une r�f�rence � l'objet.
  Association(T &_x)
    : pt(&_x)
  {}

  ///////////////////
  // Constructeur, prends une r�f�rence � l'objet.
  Association(const T &_x)
    : pt((T*)&_x)
  {}

  /////////////////////
  // Constructeur de copie.
  Association(const Association<T>& _x)
    :pt(_x.get_ptr())
  {}
	
  /////////////////////
  // Conversion de ObComposition en ObAssociation
  Association(const Composition<T>& _x) ;


  // *************************************
  // GROUP: Op�rateurs de d�r�f�renciation
  // *************************************


  /////////////////////////
  // V�rifie que le pointeur est non NULL avant d'appeler.
  T* operator ->() const ;



  // *******************
  // GROUP: Affectations
  // *******************



  ////////////////////////////
  // Affectation d'une autre association.
  Association<T>& operator =(Association<T> _r)
  {

    pt = _r.pt ;
    return *this ;
  }

  ///////////////////////////
  // Affectation avec un pointeur d'agregation.
  Association<T>& operator =(const Composition<T>& _x) ;
	

  // *******************
  // GROUP: Comparaisons
  // *******************


  //////////////////
  // Egalit� avec une autre association.
  Booleen operator == (const Association<T>& _x) const
  {
    return pt == _x.get_ptr() ;
  }

  /////////////////////
  // Comparaison avec une agr�gation.
  Booleen operator == (const Composition<T>& _x) const ;

  /////////////////////
  // Comparaison avec un pointeur.
  Booleen operator ==(const T* _x) const {
		
    return pt == _x ;
  }
	
  /////////////////
  // Diff�rence avec une autre association.
  Booleen operator !=(const  Association<T>& _x) const 
  {
    return pt != _x.get_ptr() ;
  }

  /////////////////////
  // Diff�rence avec un pointeur.
  Booleen operator !=(const T* _x) const {
		
    return pt != _x ;
  }
  
  /////////////////////
  // Comparaison avec une agr�gation.
  Booleen operator != (const Composition<T>& _x) const ;

private:


  /////////////////
  // pointeur sur l'jet en association.
  T*	pt ;

  // *******************
  // GROUP: Interdictions
  // *******************


  /////////////////////////
  // Affectation d'un pointeur.
  Association<T>& operator =(T* _p) ;

};

#ifdef _INC_TEMP_CODE_
#include "association.cxx"
#endif

#endif

	
