// ob_abstract_list.cpp

#include "liste_abstraite.h"
#include "iterateur_liste.h"

namespace ProjetUnivers {

  namespace Base {
    
    ListeAbstraite::ListeAbstraite()
      :premierNoeud(NULL),dernierNoeud(NULL),nombreDElements(0)
    {}
    
    ListeAbstraite::~ListeAbstraite() 
    {}
    
    void ListeAbstraite::AjouterEnTete(NoeudAbstrait* _n) {
    
      ++nombreDElements ;
    
      if (! (dernierNoeud == NULL)) {
    
        _n->suivant = premierNoeud.Liberer() ;
        premierNoeud = _n ;
        _n->suivant->precedent = premierNoeud ;
    	
      } else {
    
        premierNoeud = _n ;
        dernierNoeud = premierNoeud ;
      }
    
    }
    
    
    void ListeAbstraite::AjouterEnQueue(NoeudAbstrait* _n) {
    
      ++nombreDElements ;
    
      if (!(dernierNoeud == NULL)) {
    
        _n->precedent = dernierNoeud ;
        dernierNoeud->suivant = _n ;
        dernierNoeud = dernierNoeud->suivant ;
    
      } else {
    
        premierNoeud = _n ;
        dernierNoeud = premierNoeud ;
      }
    }
    
    unsigned int ListeAbstraite::NombreDElements() const {
    
      return nombreDElements ;
    
    }
    
    void ListeAbstraite::Vider() {
    
      for(IterateurListe i(*this) ; i.Valide() ; )
    
        i.Enlever() ;
    
    }
  }
}
