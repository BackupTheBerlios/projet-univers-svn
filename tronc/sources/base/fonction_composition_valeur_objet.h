#ifndef FONCTION_COMPOSITION_VALEUR_OBJET_H
#define FONCTION_COMPOSITION_VALEUR_OBJET_H


#include "association.h"
#include "string.h"


/*
CLASS
  FonctionCompositionValeurObjet

  Une fonction au sens math�matique qui associe � un �l�ment de INDICE_VALEUR 
  un �l�ment de OBJET. INDICE_VALEUR doit �tre une classe de valeur, et OBJET 
  une classe d'objet. Cette fonction est en composition : lorsqu'elle est 
  detruite, les �l�ments de OBJET le sont aussi.
  

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
  // Ajoute un �l�ment.
  void add(const INDICE_VALEUR& , const OBJET*) ;

  /////////////////
  // Modifie l'�l�ment associ� � INDICE_VALEUR. Si l'�l�ment
  // n'existe pas dans la fonction alors cela a l'effet de add.
  void set(const INDICE_VALEUR&, const OBJET&) ;


  // *******************
  // GROUP: Acc�s
  // *******************

  //////////////////
  // Acc�s � un �l�ment en fonction de l'identifiant.
  Association< OBJET > getElement(const INDICE_VALEUR&) const ;

  ////////////////////////
  // Op�rateur de comparaison
	Booleen operator==(
    const FonctionCompositionValeurObjet< INDICE_VALEUR, OBJET >& _right) 
    const ;


private:




};

#ifdef _INC_TEMP_CODE_
#include "fonction_composition_valeur_objet.cxx"
#endif





#endif
