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
#ifndef PU_MODEL_WITH_TRANSITIONS_H_
#define PU_MODEL_WITH_TRANSITIONS_H_

#include <map>
#include <string>
#include <kernel/object_reference.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// Represents a game state.
    /*!
      A game state has transitions to other states.
    */
    class WithTransitions : public Kernel::Trait 
    {
    public:

      /// Construction.
      WithTransitions() ;
    
      /// Add a transition. 
      void addTransition(const std::string& name,Kernel::Object*) ;
      
      /// The special transition on trait removal.
      void setNext(Kernel::Object*) ;
      
      /// Triggers a transition.
      void trigger(const std::string& name) ;

    protected:

      /// Trigger a transition whose name is @command.
      virtual bool call(const Kernel::TypeIdentifier& trait_type,
                        const std::string&            command) ;
      
    private:

      /// Named transitions to objects
      std::map<std::string,Kernel::ObjectReference> m_transitions ;
    };
    
  }
}

#endif /*PU_MODEL_WITH_TRANSITIONS_H_*/
