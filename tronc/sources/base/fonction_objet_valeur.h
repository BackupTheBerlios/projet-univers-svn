#ifndef FONCTION_OBJET_VALEUR_H
#define FONCTION_OBJET_VALEUR_H


#include "association.h"
#include "string.h"


/*
CLASS
  FonctionValeur

  Une fonction de valeurs est une fonction au sens math�matique qui associe 
  � un �l�ment de INDICE un �l�ment de VALEUR. INDICE peut �tre n'importe 
  quelle classe d'objets et VALEUR doit �tre une classe de valeurs.
  

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
  // Ajoute un �l�ment identifi� par le nom du param�tre.
  void add(const Association< INDICE >&, const VALEUR&) ;

  /////////////////
  // Modifie l'�l�ment associ� au param�tre de type INDICE. Si l'�l�ment
  // n'existe pas alors cela a l'effet de add.
  void set(const Association< INDICE >&, const VALEUR&) ;


  // *******************
  // GROUP: Acc�s
  // *******************

  //////////////////
  // Acc�s � un �l�ment en fonction de l'identifiant.
  VALEUR getElement(const Association< INDICE >&) const ;

  ////////////////////////
  // Op�rateur de comparaison
	Booleen operator==(const FonctionObjetValeur< INDICE,VALEUR >& _right) const ;


private:



  ////////////////////
  // Donn�es stok�es dans un tableau de listes.
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
