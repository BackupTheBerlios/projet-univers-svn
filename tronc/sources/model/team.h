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
#ifndef PU_MODEL_TEAM_H_
#define PU_MODEL_TEAM_H_

#include <string>

#include <kernel/trait.h>
#include <kernel/reader.h>

namespace ProjetUnivers {
  namespace Model {

    /// Represents a team.
    /*!
    */
    class Team : public Kernel::Trait
    {
    public:

      /// Constructs with a name.
      Team(const std::string& name) ;
      
      /// Constructs.
      Team() ;

      /// Add a flying group.
      void addFlyingGroup(const std::string& name) ;
      
      /// Read a Team trait.
      /*!
        stored as 
        @code
          <Team [name="name"]\>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      const std::string& getName() const ;
      
    private:

      /// Team name.
      std::string m_name ;
      
    };

  }
}

#endif /*PU_MODEL_TEAM_H_*/
