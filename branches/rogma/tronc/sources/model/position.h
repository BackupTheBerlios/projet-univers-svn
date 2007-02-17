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

#ifndef _PU_MODELE_POSITION_H_
#define _PU_MODELE_POSITION_H_


#include <base/association.h>
#include <modele/distance.h>

namespace ProjetUnivers {

  namespace Model {


    /// Une position dans un espace à trois dimensions.
    /*!
      Une position est :
      - un point d'origine : une sorte de référentiel
      - 3 coordonnées par rapport à ce point
      
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

      /// Constructeur par défaut.
      Position() ;
      
      /// Construit la position indiquée.
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
      
      /// Opérateur d'égatité.
      Base::Booleen operator==(const Position&) const ;
      
      // Distance entre 2 Position.
      Distance CalculerDistance(const Position&) const ; 
    
      Distance AccesCoordonneeX() const ;
      Distance AccesCoordonneeY() const ;
      Distance AccesCoordonneeZ() const ;
      
    // @}
    
    private:
    

      /*!
        Implantation l'aide de trois distances, 
        qui sont les distances entre les divers projections sur les plans 
        des coordonnées et le point qui sert d'origine au système.      
      */
      Distance coordonneeX ;
      Distance coordonneeY ;
      Distance coordonneeZ ;      
      
    };
  }
}
#endif
