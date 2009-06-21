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

#include <list>
#include <map>
#include <string>
#include <kernel/object_reference.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {

    class Active ;
    
    /// Represents a game state.
    /*!
      A game state has transitions to other states.
    */
    class State : public Kernel::Trait 
    {
    public:

      /// Construction.
      State() ;
    
      /// The special transition on trait removal.
      void setCommandOnQuit(const std::string& command) ;
      
      /// Give a @c name to a @c command. 
      void addCommandAlias(const std::string& name,const std::string& command) ;
      
      /// Access to command on quit.
      std::string getCommandOnQuit() const ;
      
      /// State management
      void pushState(Kernel::Object*,Active*) ;
      
      /// Desactivate the latest activated descendant.
      void popState() ;
      
      /// Change to another state.
      void changeState(Kernel::Object*,Active*) ;
      
    protected:

      /// Trigger a transition whose name is @command.
      /*!
        @param[in] command 
          command to be executed, it has the following format :
          # push(object_name,Trait)
          # change(object_name,Trait)
          # pop()
          where Trait is a subclass of Active.
      */
      virtual bool call(const Kernel::TypeIdentifier& trait_type,
                        const std::string&            command) ;
      
    private:

      /// Activate a state.
      void enter(Kernel::Object*,Active*) ;

      /// Desactivate a state.
      void exit(Kernel::Object*) ;
      
      /// Desactivate all sub states.
      void exitSubStates() ;
      
      /// Executed command on quit or empty string.
      std::string m_command_on_quit ;
      
      /// Stack of activated children
      /*!
        @invariant Every element has trait Active. 
      */
      std::list<Kernel::ObjectReference> m_activated_children ;
      
      /// Command aliases.
      std::map<std::string,std::string> m_aliases ;
    };
    
  }
}

#endif /*PU_MODEL_WITH_TRANSITIONS_H_*/
