/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <kernel/event.h>

namespace ProjetUnivers {
  namespace Kernel {

    /// Constructeur par défaut.
    Event::Event()
    {}

    Event::Event(const Action& _action, 
                 const std::string& _name, 
                 Model* _parameter)
    : action(_action), name(_name), parameter(_parameter)
    {}
      
      /// Constructeur de copie.
    Event::Event(const Event& _event)
    : action(_event.action), 
      name(_event.name), 
      parameter(_event.parameter)
    {}
    
    bool Event::operator==(const Event& _event) const
    {
      return action == _event.action 
             && name ==_event.name
             && parameter == _event.parameter ;
    }
         
  }
}
