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

#include <base/traceur.h>
#include <action/action.h>
#include <entrees/implantation/clavier.h>

namespace ProjetUnivers {
  namespace Entrees {
   
    namespace Implantation {
      
      Clavier::Clavier()
      {} 
      
      Clavier::~Clavier()
      {}
  
      bool Clavier::keyPressed(const OIS::KeyEvent &e)    
      {
        
        /// log
        Base::Traceur::MessageInterne(
              Base::Chaine("bouton presse timestamp = ") + 
              Base::Chaine(e.timeStamp)) ;

        /// pour l'instant : on sort si c'est entrée
        switch(e.key)
        {
        case OIS::KC_RETURN:
          Action::Ajouter("Sortie") ;
          break ;
          
        case OIS::KC_UP:
          Action::Ajouter("Haut") ;
          break ;

        case OIS::KC_DOWN:
          Action::Ajouter("Bas") ;
          break ;

        case OIS::KC_LEFT:
          Action::Ajouter("Gauche") ;
          break ;
          
        case OIS::KC_RIGHT:
          Action::Ajouter("Droite") ;
          break ;

        default:
          break ;
        }
        return true ;
      }
      
      bool Clavier::keyReleased(const OIS::KeyEvent &e)
      {
        return true ;
      }
    }
  }
}

