/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


template <class OBJET> 
ListeAssociation<OBJET>::ListeAssociation()
: liste(new TamponListeAssociation<OBJET>())
{}

template <class OBJET> 
ListeAssociation<OBJET>::~ListeAssociation() {

  if(liste->Laisser())

    delete liste ;
  
}

template <class OBJET> 
ListeAssociation<OBJET>::ListeAssociation(const ListeAssociation< OBJET >& _l)
: liste(_l.liste->Prendre()) 
{}

template <class OBJET> void 
ListeAssociation<OBJET>::AjouterEnTete(const Association<OBJET> _n) {

  // deux cas : 
  // la liste n'est pas partagée, on peut lui ajouter directement 
  // la liste est partagée, on copie puis on ajoute 

  if (liste->NombreReferences() > 1)
  {


    TamponListeAssociation<OBJET>* temp 
      = new TamponListeAssociation<OBJET>(*liste) ;

    // pas besoin de tester, il ya d'autres références
    liste->Laisser() ;

    liste = temp ;

  }

  // dans tous les cas on ajoute
  liste->AjouterEnTete(_n) ;

}

template <class OBJET> void 
ListeAssociation<OBJET>::AjouterEnQueue(const Association<OBJET> _n) {

  if (liste->NombreDeReferences() > 1)
  {


    TamponListeAssociation<OBJET>* temp 
      = new TamponListeAssociation<OBJET>(*liste) ;

    // pas besoin de tester, il ya d'autres références
    liste->Laisser() ;

    liste = temp ;

  }

  // dans tous les cas on ajoute
  liste->AjouterEnQueue(_n) ;

}

template <class OBJET> void 
ListeAssociation<OBJET>::AjouterEnQueue(const ListeAssociation< OBJET > _elt) {


  if (liste->NombreReferences() > 1)
  {


    TamponListeAssociation<OBJET>* temp 
      = new TamponListeAssociation<OBJET>(*liste) ;

    // pas besoin de tester, il ya d'autres références
    liste->Laisser() ;

    liste = temp ;

  }

  // dans tous les cas on ajoute
  for(IterateurListeAssociation<OBJET> i(_elt) ; i.Valide() ; ++i)

    liste->AjouterEnQueue(i.Association()) ;

}


template <class OBJET> Booleen 
ListeAssociation<OBJET>::Contient(const Association< OBJET >& _el) const {


  return Position(_el) != 0 ;

}

template <class OBJET> Association< OBJET > 
ListeAssociation<OBJET>::Dernier() const {

  Association< OBJET > resultat ;

  IterateurListeAssociation<OBJET> i(*this) ; 
	
  while(i.Valide()) {
		
    resultat = i ;	
    ++i ;
    if( ! i.Valide() )

      return resultat ;
  }

  // code bidon, ne devrais pas être atteind ...
  return resultat ;



}

template <class OBJET> void 
ListeAssociation<OBJET>::Enlever(unsigned int _pos) {

  if (liste->NombreDeReferences() > 1)
  {

    TamponListeAssociation<OBJET>* temp 
      = new TamponListeAssociation<OBJET>(*liste) ;

    // pas besoin de tester, il ya d'autres références
    liste->Laisser() ;

    liste = temp ;

  }

  // dans tous les cas on enlève
  liste->Enlever(_pos) ;					
}


template <class OBJET> unsigned int 
ListeAssociation<OBJET>::Position(const Association< OBJET >& _el) const {

  unsigned int compteur = 0 ;

  for(IterateurListeAssociation<OBJET> i(*this) ; i.Valide() ; ++i) {

    ++compteur ;

    if (_el == i)

      return compteur ;
  }

  return 0 ;

}

template <class OBJET> ListeAssociation< OBJET >& 
ListeAssociation<OBJET>::operator=(const ListeAssociation< OBJET >& _l) {


  if (liste)
  {

    if (liste->Laisser())

      delete liste ;
  }
  
  
  liste = _l.liste->Prendre() ;


  return *this ;
}

template <class OBJET> 
unsigned int 
ListeAssociation<OBJET>::NombreDElements() const {

  return liste->NombreDElements() ;

}

//////////////
// Constructeur.
template <class OBJET> 
ListeAssociation<OBJET>::ListeAssociation(const ListeComposition< OBJET >& _l)
: liste(new TamponListeAssociation<OBJET>())
{

  for(
  IterateurListeComposition< OBJET > j(_l) ; 
  j.Valide() ;
  ++j)

    liste->AjouterEnQueue(j.getAssociation()) ;

  

}

////////////////
// Opérateur d'affectation.
template <class OBJET> 
ListeAssociation< OBJET >& 
ListeAssociation<OBJET>::operator=(const ListeComposition< OBJET >& _l)
{
  
  if (liste) {

    if (liste->Laisser())

      delete liste ;

  }
  liste = new TamponListeAssociation<OBJET>() ;
  
  for(
  IterateurListeComposition< OBJET > j(_l) ; 
  j.Valide() ;
  ++j)

    liste->AjouterEnQueue(j) ;

  return *this ;
}

//////////////////
// Enlève tous les éléments.
template <class OBJET> 
void 
ListeAssociation<OBJET>::Vider()
{

  // on laisse la liste en cours
  if(liste->Laisser())

    delete liste ;
  
  // et on en prends une nouvelle, vide
  liste = new TamponListeAssociation<OBJET>() ;

}
