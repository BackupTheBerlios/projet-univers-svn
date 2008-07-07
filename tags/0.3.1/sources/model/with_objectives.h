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
#ifndef PU_MODEL_WITH_OBJECTIVES_H_
#define PU_MODEL_WITH_OBJECTIVES_H_

#include <set>
#include <kernel/trait.h>
#include <model/objective.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that have objectives.
    class WithObjectives : public Kernel::Trait
    {
    public:

    /*!
      @name Construction
    */
    // @{
      
      /// Constructs.
      WithObjectives() ;
      
      void addObjective(const Objective&) ;
      void removeObjective(const Objective&) ;
      
    // @}
    /*!
      @name Construction
    */
    // @{
      
      /// Access to objectives.
      const std::set<Objective>& getObjectives() const ;
      
    // @}
      
      
    private:
      
      /// Objectives.
      std::set<Objective> m_objectives ; 
      
      
      
    };

  }
}
#endif /*PU_MODEL_WITH_OBJECTIVES_H_*/
