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

#include <base/implantation/noeud_abstrait.h>

namespace ProjetUnivers {

  namespace Base {
    
    namespace Implantation {
        
      NoeudAbstrait::NoeudAbstrait()
        :suivant(NULL),precedent(NULL)
      {}
      
      NoeudAbstrait::~NoeudAbstrait()
      {}
      
      void 
      NoeudAbstrait::AjouterAvant(NoeudAbstrait *_p_nouv_n_) {
      
        _p_nouv_n_->precedent = precedent ;
        _p_nouv_n_->suivant = precedent->suivant.Liberer() ;
      
        precedent->suivant = _p_nouv_n_ ;
        precedent = precedent->suivant ;
      }
      
      void NoeudAbstrait::AjouterApres(NoeudAbstrait *_p_nouv_n_) {
      
        Composition<NoeudAbstrait> temp(_p_nouv_n_) ;
        
        _p_nouv_n_->precedent = suivant->precedent ;
        suivant->precedent = temp ;
      
        _p_nouv_n_->suivant = suivant.Liberer() ;
        suivant = temp.Liberer() ;
      }
    }
  }
}
