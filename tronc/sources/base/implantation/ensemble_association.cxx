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


template <class OBJET> EnsembleAssociation<OBJET>::EnsembleAssociation<OBJET>()
  : ListeAssociation<OBJET>()
{}


//////////////////
// Constructeur de copie.
template <class OBJET> 
EnsembleAssociation<OBJET>::EnsembleAssociation
(const EnsembleAssociation< OBJET >& _s)
  : ListeAssociation<OBJET>(_s)
{}


template <class OBJET> 
void 
EnsembleAssociation<OBJET>::Ajouter(const Association<OBJET>& _el) {

  if (! Contient(_el))

    ListeAssociation<OBJET>::AjouterEnQueue(_el) ;
}

//////////////////
// Ajoute des �l�ments.
template <class OBJET> 
void 
EnsembleAssociation<OBJET>::Ajouter(const EnsembleAssociation< OBJET >& _el) {

  for(IterateurListeAssociation<OBJET> i(_el) ; i.Valide() ; ++i)

    Ajouter(i) ;
}



template <class OBJET> 
Booleen 
EnsembleAssociation<OBJET>::
Contient(const Association<OBJET>& _r) const
{
  return ListeAssociation<OBJET>::Contient(_r) ;
}

///////////////////////
// Egalit�.
template <class OBJET> 
Booleen 
EnsembleAssociation<OBJET>::
operator==(const EnsembleAssociation<OBJET>& _r) const
{

  if (this->NombreDElements() != _r.NombreDElements())

    return FAUX ;

  for(
  IterateurListeAssociation<OBJET> i(_r) ;
  i.Valide() ;
  ++i)
  {
    if (! this->Contient(i)) 

      return FAUX ;
  }

  return VRAI ;

}
//
////////////////////////
//// Inclusion.
//template <class OBJET> 
//Booleen 
//EnsembleAssociation<OBJET>::
//operator<=(const EnsembleAssociation<OBJET>& _r) const 
//{
//  if (this->NombreDElements() > _r.NombreDElements())
//
//    return FAUX ;
//
//  for(
//  IterateurListeAssociation<OBJET> i(*this) ;
//  i.Valide() ;
//  ++i)
//  {
//    if (! _r.Contient(i)) 
//
//      return FAUX ;
//  }
//
//  return VRAI ;
//
//
//}
//
/////////////////////////
//// Inclusion strict.
//template <class OBJET> 
//Booleen 
//EnsembleAssociation<OBJET>::
//operator<(const EnsembleAssociation<OBJET>& _r) const
//{
//
//  if (this->NombreDElements() >= _r.NombreDElements())
//
//    return FAUX ;
//
//  return (*this <= _r) ;
//}
//
///////////////////////
//// Dit oui si les deux ensembles ont une intersection.
//template <class OBJET> 
//Booleen
//EnsembleAssociation<OBJET>::
//intersection(const EnsembleAssociation<OBJET>& _r) const
//{
//
//  if (_r.NombreDElements() == 0 || this->NombreDElements() == 0)
//
//    return FAUX ;
//
//  for(
//  IterateurListeAssociation<OBJET> i(*this) ;
//  i.Valide() ;
//  ++i)
//  {
//
//    if (_r.Contient(i))
//
//      return VRAI ;
//
//  }
//
//  return FAUX ;
//
//}
