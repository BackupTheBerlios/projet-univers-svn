#ifndef ENSEMBLE_COMPOSITION_H
#define ENSEMBLE_COMPOSITION_H

#include "association.h"

/*
CLASS
  EnsembleComposition

  Ensemble d'élément d'une classe d'objets en composition.

UTILISATION
  Même utilisations que pour Composition, en ce qui concerne les ensembles.
*/
template <class OBJET> class EnsembleComposition {
public:


  
  // ********************
  // GROUP: Construction
  // ********************

  
  //////////////
  // Constructeur par défaut.
  EnsembleComposition() ;

  //////////////
  // Destructeur par défaut.
  ~EnsembleComposition() ;

  /////////////////
  // Constructeur de copie, _e est vidé après cela.
//  EnsembleComposition(const EnsembleComposition< OBJET >& _e);

  /////////////////
  // Aggrege un élément à l'ensemble.
  void add(OBJET* _elt);

  //////////////////
  // Enlève l'élément _el, s'il n'y est pas ne fait rien.
  void remove(const Association< OBJET >& _el) ;


  // ********************
  // GROUP: Consultation
  // ********************


  ///////////////////
  // Determine si _el fait partie de l'ensemble.
  Booleen contains(const Association< OBJET >& _el) const ;


};

#ifdef _INC_TEMP_CODE_
#include "ensemble_composition.cxx"
#endif





#endif
