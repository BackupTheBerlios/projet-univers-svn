// composition.h
// Pointeur en composition :
// l'objet pointé est un composant de l'objet qui pointe
// lorsque l'objet composé est détruit ses composants sont detruits


#ifndef COMPOSITION_H
#define COMPOSITION_H




#include "exception.h"


template <class T> class Association ;


/*
CLASS
  Composition

  Classe générique réalisant la composition d'objet.

UTILISATIONS
	
  Utilisez cette classe partout ! Mais surtout dans les trois cas suivants:

  1. Pour pointer sur le résultat d'une fonction fabriquante. La création se fait avec un new, il n'y a pas de destruction 
  à gérer. Cette utilisation peut se réveler pratique si vous utilisez des exceptions, en effet, lorsqu'une exception 
  est levée, on sort du block et il faut détruire les jets alloués dans le tas. Un simple pointeur 
  est insuffisant pour une bonne gestion des exceptions.

EXAMPLE

  Classe1* fabriquant() {

  // résultat :
  Composition<Classe1>	res = new Classe1(...)

  // traitements 
  // N.B. Si une exception est levée ici, l'jet sera détruit.
  .....

  // on se sépare de l'jet pointé :
  return res.release() ;
  }

END

  2. Pour pointer sur les attributs agrégés à une classe. Cela évite d'écrire un destructeur, 
  car celui généré par defaut par les compilateurs appèle le destructeur sur tous les 
  attributs.

EXAMPLE

  class A {

  ....
  };

  class B {

  Composition<A>	attribut_agrégé_classe_A ;

  };
END

  3. Pour gérer une variable locale.

EXAMPLE

  <i>type</i> <b>fonction</b>( ... ) {

  Composition<A> temp(new A(...)) ;

  temp->....
  ....
		
  }

END

  En effet, si surviens une exception pendant la "manipulation" de temp ou 
  d'un autre jet, l'jet désigné par temp sera detruit.

*/
template <class T> class Composition {

public:


  ////////////////////
  // Le destructeur détruit l'objet pointé, c'est là tout l'intérêt de 
  // cette classe.
  ~Composition()
  {
    delete pt ;
  }

  /////////////////
  // Vérifie que le pointeur est non NULL : 
  T* operator ->() const
  {
    if (pt == NULL) 

      throw Exception("Composition::->") ;

    return pt ;
  }

  // *******************************
  // GROUP: Opérateurs de conversion
  // *******************************
  
  ////////////////////
  // Accès à l'objet agrégé.
  const T& operator *() const
  {
    return *pt ;
  }

  T& operator *() 
  {
    return *pt ;
  }


  // ***********************
  // GROUP: Adoption/Abandon
  // ***********************

  ///////////////////
  // Constructeur, l'objet pointé est adopté. Par défaut, 
  // le pointeur pointe sur NULL.
  Composition(T* _pt = NULL)
    : pt(_pt)
  {}

  ////////////////////
  // Affectation entre un pointeur et un pointeur d'agrégation, 
  // l'objet est adopté.
  Composition<T>& operator =(T* _pt) {

    if (*this != Association<T>(_pt)) {

      delete pt ;
      pt = _pt ;
    }

    return *this ;
	
  }

  /////////////////////
  // Affectation entre pointeurs d'agrégation, cette 
  // affectation transfére la responsabilité de l'objet.
  Composition<T>& operator =(Composition<T>& _x) {

    if (*this != _x) {

      delete pt ;
      pt = _x.pt ;
      _x.pt = NULL ;
    }

    return *this ;
  }

  /////////////////
  // Renvoie un pointeur sur l'objet agrégé. Cet objet n'est plus agrégé. 
  // Cette fonction permet à l'agrégation de se libérer de la 
  // responsabilité de l'objet pointé.
  T* release() {

    T* rc = pt ;
    pt = NULL ;
    return rc ;
  }

  // *****************************************************
  // GROUP: Opérateurs de comparaison avec une association 
  // *****************************************************

  /////////////////////
  // Comparaison avec une association.
  Booleen operator == (const Association<T>& _p) ;

  /////////////////////
  // Comparaison avec une association.
  Booleen operator !=(const  Association<T>& _p) ;
	

private:
  ////////////////////
  // Pointeur sur l'objet agrégé.
  T* pt ;


  // GROUP: Méthodes Interdites

  /////////////////
  // Cette méthode n'est pas implémentée, pour qu'elle ne soit pas utilisée.
  void operator [](size_t) ;

  /////////////////
  // Cette méthode n'est pas implémentée, pour qu'elle ne soit pas utilisée.
  Composition(const Composition< T >&) ;

};

#ifdef _INC_TEMP_CODE_
#include "composition.cxx"
#endif

#endif
