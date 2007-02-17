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


#include <base/composition.h>

#include <modele/vaisseau.h>
#include <modele/moteur.h>
#include <modele/commandes_pilotage.h>

#include <demonstration/construction.h>


namespace ProjetUnivers {

  namespace Demonstration {
  
    using namespace ProjetUnivers::Base ;
    using namespace ProjetUnivers::Model ;

    
    ///////////////
    // construit une mission
    Mission* ConstruireMission() {
    
      // on copnstruit d'abord un vaisseau
      Composition< Vaisseau > vaisseau(new Vaisseau()) ;
      Composition< Composant > composant(new Moteur()) ;
      
      vaisseau->addComposant(new Moteur()) ;
      vaisseau->addComposant(new CommandesPilotage()) ;
    
      
    
    }
    
    

  }
}

