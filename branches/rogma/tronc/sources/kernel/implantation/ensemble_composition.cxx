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

namespace ProjetUnivers {

  namespace Base {
    
    template <typename OBJET> inline 
    EnsembleComposition<OBJET>::EnsembleComposition()
    {}
    
    template <typename OBJET> inline 
    EnsembleComposition<OBJET>::~EnsembleComposition()
    {
      for(typename std::set<OBJET*>::iterator objet = ensemble.begin() ;
          objet != ensemble.end() ;
          ++objet)
      {
        delete *objet ;
      }
    }
    
    template <typename OBJET> inline
    void EnsembleComposition<OBJET>::Ajouter(OBJET* _elt)
    {
        
      ensemble.insert(_elt) ;
        
    }
        
    template <typename OBJET> inline
    void EnsembleComposition<OBJET>::Enlever(const Association< OBJET >& _el)
    {

      ensemble.erase(_el.operator->()) ;
      delete (_el.operator->()) ;
    }
        
    template <typename OBJET> inline
    EnsembleComposition<OBJET>::operator EnsembleAssociation<OBJET>() const
    {
      EnsembleAssociation<OBJET> resultat ;
      resultat.tampon = new Implantation::TamponEnsembleAssociation<OBJET>() ;
      resultat.tampon->ensemble = ensemble ;
      
      return resultat ;
       
    }

    template <typename OBJET> inline
    void EnsembleComposition<OBJET>::Vider()
    {
      for(typename std::set<OBJET*>::iterator objet = ensemble.begin() ;
          objet != ensemble.end() ;
          ++objet)
      {
        delete *objet ;
      }
      
      ensemble.clear() ;
      
    }


    template <typename OBJET> inline
    Booleen 
    EnsembleComposition<OBJET>::Contient(const Association< OBJET >& _el) const
    {
      return ensemble.find(_el.operator->()) != ensemble.end() ;
    }

    template <typename OBJET> inline
    EntierPositif EnsembleComposition<OBJET>::NombreDElements() const
    {
      return ensemble.size() ;
    }
    
    
  }
}
