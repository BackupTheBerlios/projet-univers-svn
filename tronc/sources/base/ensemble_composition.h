#ifndef ENSEMBLE_COMPOSITION_H
#define ENSEMBLE_COMPOSITION_H

#include "association.h"

/*
CLASS
  EnsembleComposition

  Ensemble d'�l�ment d'une classe d'objets en composition.

UTILISATION
  M�me utilisations que pour Composition, en ce qui concerne les ensembles.
*/
template <class OBJET> class EnsembleComposition {
public:


  
  // ********************
  // GROUP: Construction
  // ********************

  
  //////////////
  // Constructeur par d�faut.
  EnsembleComposition() ;

  //////////////
  // Destructeur par d�faut.
  ~EnsembleComposition() ;

  /////////////////
  // Constructeur de copie, _e est vid� apr�s cela.
//  EnsembleComposition(const EnsembleComposition< OBJET >& _e);

  /////////////////
  // Aggrege un �l�ment � l'ensemble.
  void add(OBJET* _elt);

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
#include "ensemble_composition.cxx"
#endif





#endif
