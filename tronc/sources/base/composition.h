// composition.h
// Pointeur en composition :
// l'objet point� est un composant de l'objet qui pointe
// lorsque l'objet compos� est d�truit ses composants sont detruits


#ifndef COMPOSITION_H
#define COMPOSITION_H




#include "exception.h"


template <class T> class Association ;


/*
CLASS
  Composition

  Classe g�n�rique r�alisant la composition d'objet.

UTILISATIONS
	
  Utilisez cette classe partout ! Mais surtout dans les trois cas suivants:

  1. Pour pointer sur le r�sultat d'une fonction fabriquante. La cr�ation se fait avec un new, il n'y a pas de destruction 
  � g�rer. Cette utilisation peut se r�veler pratique si vous utilisez des exceptions, en effet, lorsqu'une exception 
  est lev�e, on sort du block et il faut d�truire les jets allou�s dans le tas. Un simple pointeur 
  est insuffisant pour une bonne gestion des exceptions.

EXAMPLE

  Classe1* fabriquant() {

  // r�sultat :
  Composition<Classe1>	res = new Classe1(...)

  // traitements 
  // N.B. Si une exception est lev�e ici, l'jet sera d�truit.
  .....

  // on se s�pare de l'jet point� :
  return res.release() ;
  }

END

  2. Pour pointer sur les attributs agr�g�s � une classe. Cela �vite d'�crire un destructeur, 
  car celui g�n�r� par defaut par les compilateurs app�le le destructeur sur tous les 
  attributs.

EXAMPLE

  class A {

  ....
  };

  class B {

  Composition<A>	attribut_agr�g�_classe_A ;

  };
END

  3. Pour g�rer une variable locale.

EXAMPLE

  <i>type</i> <b>fonction</b>( ... ) {

  Composition<A> temp(new A(...)) ;

  temp->....
  ....
		
  }

END

  En effet, si surviens une exception pendant la "manipulation" de temp ou 
  d'un autre jet, l'jet d�sign� par temp sera detruit.

*/
template <class T> class Composition {

public:


  ////////////////////
  // Le destructeur d�truit l'objet point�, c'est l� tout l'int�r�t de 
  // cette classe.
  ~Composition()
  {
    delete pt ;
  }

  /////////////////
  // V�rifie que le pointeur est non NULL : 
  T* operator ->() const
  {
    if (pt == NULL) 

      throw Exception("Composition::->") ;

    return pt ;
  }

  // *******************************
  // GROUP: Op�rateurs de conversion
  // *******************************
  
  ////////////////////
  // Acc�s � l'objet agr�g�.
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
  // Constructeur, l'objet point� est adopt�. Par d�faut, 
  // le pointeur pointe sur NULL.
  Composition(T* _pt = NULL)
    : pt(_pt)
  {}

  ////////////////////
  // Affectation entre un pointeur et un pointeur d'agr�gation, 
  // l'objet est adopt�.
  Composition<T>& operator =(T* _pt) {

    if (*this != Association<T>(_pt)) {

      delete pt ;
      pt = _pt ;
    }

    return *this ;
	
  }

  /////////////////////
  // Affectation entre pointeurs d'agr�gation, cette 
  // affectation transf�re la responsabilit� de l'objet.
  Composition<T>& operator =(Composition<T>& _x) {

    if (*this != _x) {

      delete pt ;
      pt = _x.pt ;
      _x.pt = NULL ;
    }

    return *this ;
  }

  /////////////////
  // Renvoie un pointeur sur l'objet agr�g�. Cet objet n'est plus agr�g�. 
  // Cette fonction permet � l'agr�gation de se lib�rer de la 
  // responsabilit� de l'objet point�.
  T* release() {

    T* rc = pt ;
    pt = NULL ;
    return rc ;
  }

  // *****************************************************
  // GROUP: Op�rateurs de comparaison avec une association 
  // *****************************************************

  /////////////////////
  // Comparaison avec une association.
  Booleen operator == (const Association<T>& _p) ;

  /////////////////////
  // Comparaison avec une association.
  Booleen operator !=(const  Association<T>& _p) ;
	

private:
  ////////////////////
  // Pointeur sur l'objet agr�g�.
  T* pt ;


  // GROUP: M�thodes Interdites

  /////////////////
  // Cette m�thode n'est pas impl�ment�e, pour qu'elle ne soit pas utilis�e.
  void operator [](size_t) ;

  /////////////////
  // Cette m�thode n'est pas impl�ment�e, pour qu'elle ne soit pas utilis�e.
  Composition(const Composition< T >&) ;

};

#ifdef _INC_TEMP_CODE_
#include "composition.cxx"
#endif

#endif
