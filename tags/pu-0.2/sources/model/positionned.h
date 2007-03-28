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

#ifndef PU_MODEL_POSITIONNED_H_
#define PU_MODEL_POSITIONNED_H_


#include <kernel/trait.h>
#include <model/position.h>
#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that have a position and orientation in space.
    /*!
      Iff their parent is also positionned, the position of the object is 
      relative to its parent; whereas, its position is "absolute" and any 
      absolute position is equivalent to (0,0,0).
    */
    class Positionned : public Kernel::Trait
    {
    public:

    /*!
      @name Constructors
    */
    // @{
    
      /// Constructor.
      Positionned(const Position&) ;

      /// Constructor.
      Positionned(const Position&,const Orientation&) ;

      /// Origin position.
      Positionned() ;
  

    // @}
    /*!
      @name get
    */
    // @{

      /// Access to position relative to its parent.
      const Position& getPosition() const ;

      /// Access to position relative to @c i_ancestor.
      /*!
        @pre i_ancestor is a Positionned ancestor of this->getObject(), 
        and every object between the two are also Positionned 
      */
      Position getPosition(Kernel::Object* i_ancestor) const ;

      /// Access to orientation relative to its parent.
      const Orientation& getOrientation() const ;

      /// Access to orientation relative to @c i_ancestor.
      /*!
        @pre i_ancestor is a Positionned ancestor of this->getObject(), 
        and every object between the two are also Positionned 
      */
      Orientation getOrientation(Kernel::Object* i_ancestor) const ;

    // @}
    /*!
      @name Update
    */
    // @{

      void changeOrientation(const Orientation&) ;

      void changePosition(const Position&) ;


    // @}
        
    private:

      
      Position    m_position ;  
      Orientation m_orientation ;
    
    };
  }
}

#endif 
