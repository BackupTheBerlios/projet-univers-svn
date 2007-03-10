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

#ifndef PU_MODEL_POSITION_H_
#define PU_MODEL_POSITION_H_

#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {

    /// Une position dans un espace � trois dimensions.
    /*!
      Une position est :
      - un point d'origine : une sorte de r�f�rentiel
      - 3 coordonn�es par rapport � ce point
      
      @see Positionne
    */
    class Position 
    {
    public:
    
    // *************************
    /*!
      @name Construction
    */
    // *************************
    // @{  

      /// Constructeur par d�faut.
      Position() ;
      
      /// Construit la position indiqu�e.
      /*!
        On donne une origine et 3 distances.
      */  
      Position(const Distance& x, 
               const Distance& y, 
               const Distance& z) ;

      /// Constructeur de copie.
      Position(const Position&) ;
      
    // @}
    // *************************
    /*!
      @name Construction
    */
    // *************************      
    // @{  
      
      /// Op�rateur d'�gatit�.
      bool operator==(const Position&) const ;
      
      // Distance entre 2 Position.
      Distance calculateDistance(const Position&) const ; 
    
      Distance getXCoordinate() const ;
      Distance getYCoordinate() const ;
      Distance getZCoordinate() const ;
      
    // @}
    
    private:
    

      /*!
        Implementation l'aide de trois distances, 
        qui sont les distances entre les divers projections sur les plans 
        des coordonn�es et le point qui sert d'origine au syst�me.      
      */
      Distance xCoordinate ;
      Distance yCoordinate ;
      Distance zCoordinate ;      
      
    };
  }
}
#endif
