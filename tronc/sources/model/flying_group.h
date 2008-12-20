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
#ifndef PU_MODEL_FLYING_GROUP_H_
#define PU_MODEL_FLYING_GROUP_H_

#include <string>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {

    /// Represents a FlyingGroup.
    /*!
    */
    class FlyingGroup : public Kernel::Trait
    {
    public:

      /// Constructs with a name.
      FlyingGroup(const std::string& name) ;
      
      /// Change group's name.
      void setName(const std::string& name) ;

      /// Access to name.
      const std::string& getName() const ;
      
    private:

      /// Group name.
      std::string m_name ;
      
      /// True if it has the player in it.
      bool m_has_player ;
      
      /// Number of ships in the group
      unsigned int m_number_of_ships ;
      
      /// Ship model name.
      std::string m_ship_name ;
      
    };

  }
}

#endif /*PU_MODEL_FLYING_GROUP_H_*/
