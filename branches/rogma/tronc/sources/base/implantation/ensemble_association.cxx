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

#include <base/implantation/tampon_ensemble_association.h>
#include <base/iterateur_ensemble_association.h>

#include <iostream>

namespace ProjetUnivers {

  namespace Base {

    
    template <typename OBJET> EnsembleAssociation<OBJET>::EnsembleAssociation()
    : tampon(new Implantation::TamponEnsembleAssociation<OBJET>())
    {}
    
    
    template <typename OBJET> 
    EnsembleAssociation<OBJET>::
    EnsembleAssociation(const EnsembleAssociation<OBJET>& _s)
      : tampon(_s.tampon->Prendre())
    {}
    
    
    template <typename OBJET> 
    void 
    EnsembleAssociation<OBJET>::Ajouter(const Association<OBJET>& _el) 
    {

      // soit il faut copier l'ensemble à modifier (s'il est partagé)
      // soit on peut directement le modifier
      
      if (tampon->nombreDeReferences == 1)
      {
        tampon->ensemble.insert(&(*_el)) ;
      }
      else
      {

        if (! Contient(_el))
        {
          Implantation::TamponEnsembleAssociation<OBJET>* nouveauTampon 
             = new Implantation::TamponEnsembleAssociation<OBJET>(*tampon) ;

          if (tampon->Laisser())
            delete tampon ;
          
          tampon = nouveauTampon ;

          tampon->ensemble.insert(&(*_el)) ;
        }      
      }
    }
    
    template <typename OBJET> 
    void 
    EnsembleAssociation<OBJET>::Ajouter(const EnsembleAssociation<OBJET>& _el) 
    {
    
      for(IterateurEnsembleAssociation<OBJET> i(_el) ; i.Valide() ; ++i)
    
        // bof --> ne faire qu'une copie
        Ajouter(i) ;
    }
    
    
    
    template <typename OBJET>
    void 
    EnsembleAssociation<OBJET>::Enlever(const Association<OBJET>& _el) 
    {

      if (Contient(_el))
      {
        if (tampon->nombreDeReferences != 1) 
        {
          Implantation::TamponEnsembleAssociation<OBJET>* nouveauTampon 
             = new Implantation::TamponEnsembleAssociation<OBJET>(*tampon) ;

          if (tampon->Laisser())
            delete tampon ;
          
          tampon = nouveauTampon ;

        }
          
        tampon->ensemble.erase(_el.operator->()) ;
      }
    }

    template <typename OBJET>
    void 
    EnsembleAssociation<OBJET>::Vider()
    {
      if (tampon->Laisser())
        delete tampon ;
        
      tampon = new Implantation::TamponEnsembleAssociation<OBJET>() ;
    }
    
    
    template <typename OBJET> 
    Booleen 
    EnsembleAssociation<OBJET>::
    Contient(const Association<OBJET>& _r) const
    {
      return tampon->ensemble.find(_r.operator->()) != tampon->ensemble.end() ;
    }
    
    template <typename OBJET> 
    Booleen 
    EnsembleAssociation<OBJET>::
    operator==(const EnsembleAssociation<OBJET>& _r) const
    {
    
      return tampon->ensemble == _r.tampon->ensemble ;
    }

    template <typename OBJET> 
    EntierPositif 
    EnsembleAssociation<OBJET>::
    NombreDElements() const 
    {
      return tampon->ensemble.size() ;
    }

    
  }
}
