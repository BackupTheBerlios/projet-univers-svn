// ob_association.h :
// définition de la classe implémentant les pointeurs de association.

#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include "exception.h"

template <class T> class Composition ;

/*
CLASS
  Association

  Classe générique désignant une association sur un objet.

UTILISATION
  Cette classe sert à désigner des objets non-persistant en lecture 
  et comme retours de fonctions d'accès. Ainsi, lorsqu'on a besoin de désigner 
  un objet existant on utilise cette classe.
*/
template <class T> class Association {
public:

  // ********************
  // GROUP: Constructeurs
  // ********************


  /////////////////
  // Constructeur par défaut.
  Association()
    : pt()
  {}


  ///////////////////
  // Constructeur, prends une référence à l'objet.
  Association(T &_x)
    : pt(&_x)
  {}

  ///////////////////
  // Constructeur, prends une référence à l'objet.
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
  // GROUP: Opérateurs de déréférenciation
  // *************************************


  /////////////////////////
  // Vérifie que le pointeur est non NULL avant d'appeler.
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
  // Egalité avec une autre association.
  Booleen operator == (const Association<T>& _x) const
  {
    return pt == _x.get_ptr() ;
  }

  /////////////////////
  // Comparaison avec une agrégation.
  Booleen operator == (const Composition<T>& _x) const ;

  /////////////////////
  // Comparaison avec un pointeur.
  Booleen operator ==(const T* _x) const {
		
    return pt == _x ;
  }
	
  /////////////////
  // Différence avec une autre association.
  Booleen operator !=(const  Association<T>& _x) const 
  {
    return pt != _x.get_ptr() ;
  }

  /////////////////////
  // Différence avec un pointeur.
  Booleen operator !=(const T* _x) const {
		
    return pt != _x ;
  }
  
  /////////////////////
  // Comparaison avec une agrégation.
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

	
