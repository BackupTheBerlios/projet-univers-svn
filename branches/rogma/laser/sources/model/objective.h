/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#pragma once

#include <set>
#include <kernel/object_reference.h>

namespace ProjetUnivers
{
  namespace Model
  {

    /// Represents an object objective.
    class Objective 
    {
    public:

      /// Elementary objectives
      typedef enum
      {
        Wait = 0,
        Patrol,
        AttackAllEnemies,
        GoTo
      } Kind ;
      
    /*!
      @name Constructors.
    */
    // @{
      
      /// Copy constructor is required for a value class.
      Objective(const Objective&) ;
      
      /// Assignement is required for a value class.
      Objective& operator=(const Objective&) ;
      
      /// The wait objective.
      /*!
        This objective means : dont move and defend yourself.
      */
      static Objective wait() ;
      
      /// Patrol in a @c zone. 
      /*!
        @param zone must be a Sized object.
        
        This objective means : stay in the @c zone.
      */
      static Objective patrol(Kernel::Object* zone) ;
      
      /// Attack all enemies. 
      static Objective attackAllEnemies() ;
      
      /// Go to @c position. 
      /*!
        @param position must be a Positioned object.
        
        This objective means : try to move to the same position of the object.
      */
      static Objective goTo(Kernel::Object* position) ;
      
    // @}
      
      /// Comparison is required for a value class.
      bool operator==(const Objective&) const ;

      /// Comparison is required by std::set.
      bool operator<(const Objective&) const ;
      
      /// Access to objective kind.
      Kind getKind() const ;
      
      /// Access to patrol zone in case the objective is patrol.
      Kernel::ObjectReference getPatrolZone() const ;

      /// Access to the destination position.
      Kernel::ObjectReference getDestination() const ;
      
    private:

      /// Constructs.
      Objective(const Kind&) ;
      
      Kind m_objective_kind ;
      
      /// Abstract parameters if any.
      std::set<Kernel::ObjectReference> m_parameters ;
      
    };

  }
}
