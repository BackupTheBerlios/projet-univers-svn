#ifndef FONCTION_OBJET_VALEUR_H
#define FONCTION_OBJET_VALEUR_H


#include "association.h"
#include "string.h"


/*
CLASS
  FonctionValeur

  Une fonction de valeurs est une fonction au sens mathématique qui associe 
  à un élément de INDICE un élément de VALEUR. INDICE peut être n'importe 
  quelle classe d'objets et VALEUR doit être une classe de valeurs.
  

*/
template <class INDICE, class VALEUR > class FonctionObjetValeur {
public:

  // *******************
  // GROUP: Constructeur
  // *******************


  //////////////////
  // Constructeur.
  FonctionObjetValeur() ;

  ///////////////
  // Constructeur de copie.
  FonctionObjetValeur(const FonctionObjetValeur& _v);

  
  // *******************
  // GROUP: Modification
  // *******************

  //////////////////
  // Ajoute un élément identifié par le nom du paramètre.
  void add(const Association< INDICE >&, const VALEUR&) ;

  /////////////////
  // Modifie l'élément associé au paramètre de type INDICE. Si l'élément
  // n'existe pas alors cela a l'effet de add.
  void set(const Association< INDICE >&, const VALEUR&) ;


  // *******************
  // GROUP: Accès
  // *******************

  //////////////////
  // Accès à un élément en fonction de l'identifiant.
  VALEUR getElement(const Association< INDICE >&) const ;

  ////////////////////////
  // Opérateur de comparaison
	Booleen operator==(const FonctionObjetValeur< INDICE,VALEUR >& _right) const ;


private:



  ////////////////////
  // Données stokées dans un tableau de listes.
  //ObValueArray< ObValueList< ObValuePair< String, VALEUR > > > dictionaire ;

  ///////////////////
  // Fonction de hashage.
  //static UnsignedInteger hashFonction(const String&) ;

  //friend class ObValueDictionaryIterator< INDICE,VALEUR> ;

};

#ifdef _INC_TEMP_CODE_
#include "fonction_objet_valeur.cxx"
#endif





#endif
