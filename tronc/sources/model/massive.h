/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_MASSIVE_H_
#define PU_MODEL_MASSIVE_H_

#include <kernel/trait.h>
#include <kernel/reader.h>

#include <model/mass.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that have a mass.
    /*!
      Here we have a problem : 
      - composite object have composite masses...
      - this trait is a kind of mass for atomic objects
      
    */
    class Massive : public Kernel::Trait
    {
    public:
      
      /// Construct.
      Massive(const Mass& i_mass) ;

      /// Read a Massive trait.
      /*!
        stored as 
          <Massive>
            [<Mass .../>]
          </Massive>
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to local mass.
      /*!
        Local mass is the mass of the object without its components.
      */
      Mass getMass() const ;
      
//      /// Access to total mass.
//      /*!
//        Total mass is the mass of the object with its components.
//      @todo
//        Find a way to maintain it.
//        A view on itself ???
//        With onInit/onClose add/remove its local mass to direct Massive parent?
//        Does not work with elementary update of a mass
//      */
//      Mass getTotalMass() const ;    
    
      /// Set the local mass.
      void changeMass(const Mass& i_mass) ;
      
//      void addTotalMass(const Mass& i_mass) ;
//      void removeTotalMass(const Mass& i_mass) ;
      
    private:
      
      Mass m_mass ;

//      Mass m_total_mass ;
    };
  }
}

#endif /*PU_MODEL_MASSIVE_H_*/
