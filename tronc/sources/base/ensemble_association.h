#ifndef ENSEMBLE_ASSOCIATION_H
#define ENSEMBLE_ASSOCIATION_H

#include "association.h"

/*
CLASS
  EnsembleAssociation

  Ensemble d'�l�ment d'une classe d'objets en association.

UTILISATION
  M�me utilisations que pour Association, en ce qui concerne les ensembles.
*/
template <class OBJET> class EnsembleAssociation {
public:


  
  // ********************
  // GROUP: Construction
  // ********************

  
  //////////////
  // Constructeur par d�faut.
  EnsembleAssociation() ;

  //////////////
  // Destructeur par d�faut.
  ~EnsembleAssociation() ;

  /////////////////
  // Constructeur de copie, _e est vid� apr�s cela.
  EnsembleAssociation(const EnsembleAssociation< OBJET >& _e);

  /////////////////
  // Aggrege un �l�ment � l'ensemble.
  void add(const Association< OBJET >& _elt);

  //////////////////
  // Enl�ve l'�l�ment _el, s'il n'y est pas ne fait rien.
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
