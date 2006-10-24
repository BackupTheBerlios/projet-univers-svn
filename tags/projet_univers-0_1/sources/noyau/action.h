/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_NOYAU_ACTION_H_
#define _PU_NOYAU_ACTION_H_

#include <base/association.h>

namespace ProjetUnivers {

  namespace Noyau {


    class Modele ;
    
    
    /// \brief 
    /// Une action de jeu pouvant �tre r�alis�e par un joueur ou une IA.
    
    /// Une action d�crit une op�ration de modification sur le mod�le, il 
    /// s'agit pas exemple ....
    class Action {
    public:
      
      

      // *************************
      /// @name M�thodes principales
      // *************************      
      // @{  
      

      /// R�alise l'action sur le mod�le.

      /// \remark 
      ///     peut �tre il faudrait obtenir le r�sultat de l'action en 
      ///     retours...
      virtual void Realiser(const Base::Association< Modele >&) const = 0 ;
      
      
      
      // }@
      

      // *************************
      /// @name Constructeurs/Destructeurs
      // *************************      
      // @{  
      
      

      /// Classe abstraite donc destructeur virtuel.
      virtual ~Action() ;
    

      
    
    protected:
    
 
 

      /// Classe abstraite donc constructeur prot�g�.
      Action() ;
    
      // }@
    
    
    
    };
  }
}

#endif

