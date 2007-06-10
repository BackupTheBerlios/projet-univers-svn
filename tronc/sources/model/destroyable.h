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


#ifndef PU_MODEL_DESTROYABLE_H_
#define PU_MODEL_DESTROYABLE_H_


#include <model/energy.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {


    
      
    /// Trait for objects that can be damaged.
    /*!
    @todo
      implement tache 2378.
    @par Etat
      planning
    */
    class Destroyable : public Kernel::Trait
    {
    public:

      /// Build a new.
      Destroyable(const Energy& _pointsDeVieTotal) ;
   
    /*!
      @name Principal methods
    */
    // @{
   
      /// Get a percentage of life points.
      /*!
        - 100% means a brand new
        - 0%  means a completely destroyed one
      */
      float getLife() const ;
   
      /// Damage the element.
      void damage(const Energy& _energy) ;
   
    // @}
   
      /// Abstact class means virtual destructor.
      virtual ~Destroyable() ;
    
   
    protected:


      
      /// Energy to completelly destroy the element == total life points.
      Energy totalResistance ;
      
      /// Remaining energy.
      Energy resistance ;


    };

  }

}

#endif
