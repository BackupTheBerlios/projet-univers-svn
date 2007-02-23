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

#ifndef _PU_MODEL_POSITIONNED_H_
#define _PU_MODEL_POSITIONNED_H_


#include <model/trait.h>
#include <model/position.h>
#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {

    /// Propriété des objets ayant une position dans un espace.
    class Positionned : public Trait
    {
    public:

    /*!
      @name Construction
    */
    // @{
    
      /// Constructeur.
      Positionned(const Position&) ;

      /// Positionne par rapport à son propre référentiel.
      Positionned() ;
  

    // @}
    /*!
      @name get
    */
    // @{

      /// Position de l'objet.
      Position getPosition() const ;

      /// Orientation de l'objet
      Orientation getOrientation() const ;

    // @}
    /*!
      @name Update
    */
    // @{

      void changeOrientation(const Orientation&) ;

    // @}
        
    private:

      
      Position position ;  
      Orientation orientation ;
    
    };
  }
}

#endif 
