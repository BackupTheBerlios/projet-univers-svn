#ifndef ENSEMBLE_ASSOCIATION_H
#define ENSEMBLE_ASSOCIATION_H

#include "association.h"

/*
CLASS
  EnsembleAssociation

  Ensemble d'élément d'une classe d'objets en association.

UTILISATION
  Même utilisations que pour Association, en ce qui concerne les ensembles.
*/
template <class OBJET> class EnsembleAssociation {
public:


  
  // ********************
  // GROUP: Construction
  // ********************

  
  //////////////
  // Constructeur par défaut.
  EnsembleAssociation() ;

  //////////////
  // Destructeur par défaut.
  ~EnsembleAssociation() ;

  /////////////////
  // Constructeur de copie, _e est vidé après cela.
  EnsembleAssociation(const EnsembleAssociation< OBJET >& _e);

  /////////////////
  // Aggrege un élément à l'ensemble.
  void add(const Association< OBJET >& _elt);

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
#include "ensemble_association.cxx"
#endif





#endif
