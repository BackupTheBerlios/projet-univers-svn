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

#ifndef _PU_NOYAU_POSITION_H_
#define _PU_NOYAU_POSITION_H_

#include <OgreVector3.h>
#include "distance.h"
#include "types.h"

namespace ProjetUnivers {

  namespace Noyau {

    using namespace ProjetUnivers::Base ;
    /*
    CLASS
      Position
      
      Une position absolue dans l'espace. L'unit� de mesure est le ???.
      
    TYPE_DE_CLASSE
      Objet
      Valeur
    */
    class Position {
    public:
    
      ///////////////////
      // Construit la position indiqu�e, par d�faut la position d'origine, 
      // l'unit� de mesure est le ???.
      Position(const Reel& x = 0, const Reel& y = 0, const Reel& z = 0) ;
      
      ///////////////////
      // Constructeur de copie.
      Position(const Position&) ;
      
      //////////////////
      // Calcule la distance.
      Distance CalculeDistance(const Position&) ; 
    
    private:
    
      ///////////////
      // Implantation � l'aide d'un vecteur � trois coordonn�es.
      Ogre::Vector3 vecteurCoordonnees ;
  
    };
  }
}
#endif
