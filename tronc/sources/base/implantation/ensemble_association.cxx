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

namespace ProjetUnivers {

  namespace Base {

    
    template <class OBJET> EnsembleAssociation<OBJET>::EnsembleAssociation<OBJET>()
    : Implantation::ListeAssociation<OBJET>()
    {}
    
    
    //////////////////
    // Constructeur de copie.
    template <class OBJET> 
    EnsembleAssociation<OBJET>::EnsembleAssociation
    (const EnsembleAssociation< OBJET >& _s)
      : Implantation::ListeAssociation<OBJET>(_s)
    {}
    
    
    template <class OBJET> 
    void 
    EnsembleAssociation<OBJET>::Ajouter(const Association<OBJET>& _el) {
    
      if (! Contient(_el))
    
        Implantation::ListeAssociation<OBJET>::AjouterEnQueue(_el) ;
    }
    
    //////////////////
    // Ajoute des éléments.
    template <class OBJET> 
    void 
    EnsembleAssociation<OBJET>::Ajouter(const EnsembleAssociation< OBJET >& _el) {
    
      for(Implantation::IterateurListeAssociation<OBJET> i(_el) ; i.Valide() ; ++i)
    
        Ajouter(i) ;
    }
    
    
    
    //////////////////
    // Enlève un élément.
    template <class OBJET> 
    void 
    EnsembleAssociation<OBJET>::Enlever(const Association<OBJET>& _el) {
    
      unsigned int position = this->Position(_el) ;
      
      
      if (position != 0)
    
        Implantation::ListeAssociation<OBJET>::Enlever(position) ;
    }
    
    
    
    template <class OBJET> 
    Booleen 
    EnsembleAssociation<OBJET>::
    Contient(const Association<OBJET>& _r) const
    {
      return Implantation::ListeAssociation<OBJET>::Contient(_r) ;
    }
    
    ///////////////////////
    // Egalité.
    template <class OBJET> 
    Booleen 
    EnsembleAssociation<OBJET>::
    operator==(const EnsembleAssociation<OBJET>& _r) const
    {
    
      if (this->NombreDElements() != _r.NombreDElements())
    
        return FAUX ;
    
      for(
      Implantation::IterateurListeAssociation<OBJET> i(_r) ;
      i.Valide() ;
      ++i)
      {
        if (! this->Contient(i)) 
    
          return FAUX ;
      }
    
      return VRAI ;
    
    }
    
  }
}
