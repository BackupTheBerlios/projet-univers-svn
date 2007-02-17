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

#include <sstream>
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>


#include <base/composition.h>
#include <base/association.h>
#include <affichage/affichage.h>
#include <entrees/implantation/clavier.h>
#include <entrees/entrees.h>

namespace ProjetUnivers {
  namespace Entrees {

    namespace {
      
      /// Detruit les objets locaux
      class SystemeOIS
      {  
      public:
        /// Gestionnaire OIS d'entrées
        OIS::InputManager* gestionnaire ;
   
        /// Clavier
        OIS::Keyboard* clavier ;
    
        SystemeOIS()
        : gestionnaire(), clavier()
        {}
        
        ~SystemeOIS()
        {
          if (clavier) 
          {
            gestionnaire->destroyInputObject(clavier);
            clavier = NULL ;
          }
          if (gestionnaire)
          {
            gestionnaire->destroyInputSystem() ;
          }
        }  
          
      };
    }

    /// Les élément de OIS
    Base::Composition<SystemeOIS> ois ;
   
    /// Notre écouteur de clavier
    Base::Composition<Implantation::Clavier> clavier ;
   
    void init()
    {
      
      if (ois != NULL)
      {
        return ;
      }
      
      ois = new SystemeOIS() ;
      
      OIS::ParamList parametres ;    
      size_t descripteurDeFenetre = 0;
      std::ostringstream nomDescripteurDeFenetre ;

      descripteurDeFenetre = Display::DescripteurFenetre() ;
      nomDescripteurDeFenetre << (unsigned int) descripteurDeFenetre;
      parametres.insert(std::make_pair(
                          std::string("WINDOW"), 
                          nomDescripteurDeFenetre.str())) ;

      // création du gestionnaire
      ois->gestionnaire = OIS::InputManager::createInputSystem(parametres) ;

      // création d'un clavier, avec son écouteur
      ois->clavier = static_cast<OIS::Keyboard*>(
                  ois->gestionnaire->createInputObject(OIS::OISKeyboard,true)) ;
    
      clavier = new Implantation::Clavier() ;
      
      ois->clavier->setEventCallback(clavier.operator->()) ;

    }       
    
    void close()
    {
      ois = NULL ;
     
    }
    
    void Traiter()
    {
      /// capture sur tous les systèmes d'entrée
      ois->clavier->capture() ;
    }
    
  }
}



