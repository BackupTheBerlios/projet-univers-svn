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

#include <noyau/distance.h>

namespace ProjetUnivers {

  namespace Noyau {

    //using namespace ProjetUnivers::Base ;


    /// Une position absolue dans un espace � trois dimensions.
    /*!
      @deprecated ??
    */
    class Position {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  
     

      /// Construit le point d'origine de l'univers.
      Position() ;

      /// La position particuli�re d'un objet physique.
      Position(const Association< ObjetPhysique >&) ;


      /// Construit la position indiqu�e.
      /*!
        On donne une origine et 3 distances.
      */  
      Position(const Position& _origine,
               const Distance& x, 
               const Distance& y, 
               const Distance& z) ;
      

      /// Constructeur de copie.
      Position(const Position&) ;
      
      // @}

      // *************************
      /// @name Acc�s
      // *************************      
      // @{  
       
     
      

      // Distance entre 2 Position.
      Distance CalculerDistance(const Position&) ; 
    
      // @}
    
    private:
    

      /*!
        Implantation l'aide de trois distances, 
        qui sont les distances entre les divers projections sur les plans 
        des coordonn�es et le point qui sert d'origine au syst�me.      
      */
      Position origine ;
      Distance coordonneeX ;
      Distance coordonneeY ;
      Distance coordonneeZ ;      
      
      
  
  
    };
  }
}
#endif
