#ifndef FONCTION_COMPOSITION_VALEUR_OBJET_H
#define FONCTION_COMPOSITION_VALEUR_OBJET_H


#include "association.h"
#include "string.h"


/*
CLASS
  FonctionCompositionValeurObjet

  Une fonction au sens mathématique qui associe à un élément de INDICE_VALEUR 
  un élément de OBJET. INDICE_VALEUR doit être une classe de valeur, et OBJET 
  une classe d'objet. Cette fonction est en composition : lorsqu'elle est 
  detruite, les éléments de OBJET le sont aussi.
  

*/
template <class INDICE_VALEUR, class OBJET > 
          class FonctionCompositionValeurObjet {
public:

  // *******************
  // GROUP: Constructeur
  // *******************


  //////////////////
  // Constructeur.
  FonctionCompositionValeurObjet() ;

  
  // *******************
  // GROUP: Modification
  // *******************

  //////////////////
  // Ajoute un élément.
  void add(const INDICE_VALEUR& , const OBJET*) ;

  /////////////////
  // Modifie l'élément associé à INDICE_VALEUR. Si l'élément
  // n'existe pas dans la fonction alors cela a l'effet de add.
  void set(const INDICE_VALEUR&, const OBJET&) ;


  // *******************
  // GROUP: Accès
  // *******************

  //////////////////
  // Accès à un élément en fonction de l'identifiant.
  Association< OBJET > getElement(const INDICE_VALEUR&) const ;

  ////////////////////////
  // Opérateur de comparaison
	Booleen operator==(
    const FonctionCompositionValeurObjet< INDICE_VALEUR, OBJET >& _right) 
    const ;


private:




};

#ifdef _INC_TEMP_CODE_
#include "fonction_composition_valeur_objet.cxx"
#endif





#endif
