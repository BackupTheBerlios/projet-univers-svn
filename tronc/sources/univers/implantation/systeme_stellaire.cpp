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

#include "systeme_stellaire.h"
#include "etoile.h"
#include "planetoide.h"


namespace ProjetUnivers {

  namespace Univers {
    
    
    class Planetoide ;
    class Etoile ;
    
    


    // *******************
    // GROUP: Constructeur
    // *******************


    ////////////////////
    // Constructeur.
    SystemeStellaire::SystemeStellaire()
    {}
    
    //////////////////
    // Ajoute une étoile.
    void SystemeStellaire::AjouterEtoile(Etoile* _etoile)
    {
      this->etoiles.Ajouter(_etoile) ;
    }  
  
    
    //////////////////
    // Ajoute un planétoïde.
    void SystemeStellaire::AjouterPlanetoide(Planetoide* _planetoide)
    {
      this->planetoides.Ajouter(_planetoide) ;
    }
     
    
  }

}


