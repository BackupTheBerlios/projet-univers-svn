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

///////////////
// Renvoie l'élément courant en association.
template <class OBJET> 
IterateurTamponListeAssociation<OBJET>::operator Association< OBJET >()
{
  return noeudCourant()->element ;

}

///////////////
// Renvoie l'élément courant en référence.
template <class OBJET> 
IterateurTamponListeAssociation<OBJET>::operator const OBJET&()
{
  return *noeudCourant()->element ;

}


template <class OBJET> 
IterateurTamponListeAssociation<OBJET>::IterateurTamponListeAssociation
(const TamponListeAssociation<OBJET> &_l)
  : IterateurListe(_l)
{}


template <class OBJET> void 
IterateurTamponListeAssociation<OBJET>::AjouterApres(const Association<OBJET> _n) {

  Composition< NoeudAssociation<OBJET> > n(new NoeudAssociation<OBJET>(_n)) ;

  IterateurListe::AjouterApres(n.Liberer()) ;

}

template <class OBJET> void 
IterateurTamponListeAssociation<OBJET>::AjouterAvant(const Association<OBJET> _n) {

  Composition< NoeudAssociation<OBJET> > n(new NoeudAssociation<OBJET>(_n)) ;

  IterateurListe::AjouterAvant(n.Liberer()) ;

}


template <class OBJET> OBJET* 
IterateurTamponListeAssociation<OBJET>::operator ->() const {

  OBJET* resultat = (OBJET*)(noeudCourant()->element) ;

  if (resultat == NULL)

    throw ExceptionBase("IterateurTamponListeAssociation<OBJET>::operator ->") ;

  return resultat ;

}

template <class OBJET> OBJET& 
IterateurTamponListeAssociation<OBJET>::operator *() const {

  return *(noeudCourant()->element) ;
}

