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

template <class OBJET> inline 
EnsembleComposition<OBJET>::EnsembleComposition()
: ListeComposition<OBJET>()
{}

template <class OBJET> inline 
EnsembleComposition<OBJET>::~EnsembleComposition()
{}

template <class OBJET> inline
void EnsembleComposition<OBJET>::Ajouter(OBJET* _elt)
{
  Composition<OBJET> element(_elt) ;
  
  if (! Contient(element))
    ListeComposition<OBJET>::AjouterEnTete(element.Liberer()) ;
    
}
    
template <class OBJET> inline
void EnsembleComposition<OBJET>::Enlever(const Association< OBJET >& _el)
{
  // on cherche l'élément
  unsigned int position(ListeComposition<OBJET>::Position(_el)) ;
  if (position != 0)
    ListeComposition<OBJET>::Enlever(position) ;
}
    
    
template <class OBJET> inline
Booleen 
EnsembleComposition<OBJET>::Contient(const Association< OBJET >& _el) const
{
  return ListeComposition<OBJET>::Contient(_el) ;
}
 
