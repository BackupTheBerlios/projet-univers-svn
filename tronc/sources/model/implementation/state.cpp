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
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/string.h>
#include <model/active.h>
#include <model/displayed.h>
#include <model/played.h>
#include <model/edited.h>
#include <model/state.h>

namespace ProjetUnivers {
  namespace Model {
    
    State::State()
    {}

    void State::setCommandOnQuit(const std::string& command)
    {
      m_command_on_quit = command ;
    }

    void State::addCommandAlias(const std::string& name,
                                const std::string& command)
    {
      m_aliases[name] = command ;
    }
    
    std::string State::getCommandOnQuit() const 
    {
      return m_command_on_quit ;
    }
    
    Active* getTrait(const std::string& name)
    {
      if (name == "Displayed")
      {
        return new Displayed() ;
      }
      else if (name == "Played")
      {
        return new Played() ;
      }
      else if (name == "Edited")
      {
        return new Edited() ;
      }
      else if (name == "Active")
      {
        return new Active() ;
      }
      return NULL ;
    }

    bool State::call(const Kernel::TypeIdentifier& trait_type,
                     const std::string&            command)
    {
      InternalMessage("Model","State::call entering command=" + command) ;
      
      // check for aliases
      std::map<std::string,std::string>::const_iterator finder = m_aliases.find(command) ;
      if (finder != m_aliases.end())
      {
        return call(trait_type,finder->second) ;
      }
      
      InternalMessage("Model","State::call command is not an alias") ;

      // parse the command
      std::string::size_type position_of_parenthesis = command.find('(') ;
      
      if (position_of_parenthesis != std::string::npos)
      {
        std::string command_name = command.substr(0,position_of_parenthesis) ;

        InternalMessage("Model","State::call command name=" + command_name) ;
        
        if (command_name == "pop")
        {
          State* parent = getObject()->getAncestor<State>() ;
          if (parent)
          {
            parent->popState() ;
            return true ;
          }
        }
        else
        {
          // look for ','
          std::string::size_type position_of_comma = command.find(',',position_of_parenthesis) ;

          if (position_of_comma != std::string::npos)
          {
            std::string object_name = command.substr(position_of_parenthesis+1,
                                                     position_of_comma-position_of_parenthesis-1) ;
            
            std::string trait_name = command.substr(position_of_comma+1,
                                                    command.length()-position_of_comma-2) ;

            InternalMessage("Model","State::call object name=" + object_name) ;
            InternalMessage("Model","State::call trait name=" + trait_name) ;
            
            std::auto_ptr<Active> active(getTrait(trait_name)) ;
            Kernel::Object* object = Kernel::Object::get(object_name) ;
            
            if (object && active.get())
            {
              if (command_name == "push")
              {
                pushState(object,active.release()) ;
                return true ;
              }
              else if (command_name == "change")
              {
                changeState(object,active.release()) ;
                return true ;
              }
            }
            
            ErrorMessage("State::call invalid command " + command) ;
          }
        }
      }
      // not executed
      InternalMessage("Model","State::call command name not executed") ;
      return false ; 
      
    }
    
    void State::pushState(Kernel::Object* state,Active* active)
    {
      
      std::auto_ptr<Active> local_active(active) ;
      
      if (!state) 
        return ;
      
      State* parent = state->getAncestor<State>() ;
      
      if (!parent)
        return ;
      
      if (parent == this)
      {
        
        // do not push twice a state (second is ignored) 
        if (m_activated_children.empty() || m_activated_children.back() != state)
        {
          m_activated_children.push_back(state) ;
          enter(state,local_active.release()) ;
        }
      } 
      else
      {
        State* parent = getObject()->getAncestor<State>() ;
        if (parent)
        {
          parent->pushState(state,local_active.release()) ;
        }
        else
        {
          ErrorMessage("Invalid transition") ;
        }

      }
      
    }
    
    void State::popState()
    {
      
      if (m_activated_children.size() == 0)
      {
        ErrorMessage("State::popState : no sub state to pop") ;
        return ;
      }
      
      State* child = m_activated_children.back()->getTrait<State>() ;
      
      if (!child)
      {
        ErrorMessage("State::changeState : activated child to pop is not a state") ;
        return ;
      }
      child->exitSubStates() ;
      exit(m_activated_children.back()) ;
      m_activated_children.pop_back() ;
    }
    
    void State::changeState(Kernel::Object* state,Active* active)
    {
      if (!active)
      {
        ErrorMessage("State::changeState") ;
        return ;
      }
      
      if (!state)
      {
        delete active ;
        ErrorMessage("State::changeState") ;
        return ;
      }

      InternalMessage("Model","Model::State::changeState from " + 
                              Kernel::toString(getObject()->getIdentifier()) + 
                              " to " + Kernel::toString(state->getIdentifier())) ;
      
      State* parent = state->getAncestor<State>() ;

      if (parent == this)
      {
        InternalMessage("Model","Model::State::changeState#1") ; 
        parent->exitSubStates() ;
        InternalMessage("Model","Model::State::changeState#1.1") ; 
        m_activated_children.push_back(state) ;
        enter(state,active) ;
        InternalMessage("Model","Model::State::changeState#1.2") ; 
      } 
      else
      {
        InternalMessage("Model","Model::State::changeState#2") ; 
        State* parent = getObject()->getAncestor<State>() ;
        if (parent)
        {
          parent->changeState(state,active) ;
        }
        else
        {
          ErrorMessage("Invalid transition") ;
        }
      }
    }
    
    void State::enter(Kernel::Object* state,Active* active)
    {
      
      if(! state->getTrait<State>())
      {
        
        delete active ;
        return ;
      }
      
      state->addTrait(active) ;
    }

    void State::exit(Kernel::Object* state)
    {
      Active* active = state->getTrait<Active>() ;
      if (active)
      {
        state->destroyTrait(active) ;
      }
    }
    
    void State::exitSubStates()
    {
      for(std::list<Kernel::ObjectReference>::const_iterator active = m_activated_children.begin() ;
          active != m_activated_children.end() ;
          ++active)
      {
        exit(*active) ;
      }
      
      m_activated_children.clear() ;
      
      std::set<State*> sub_states = getObject()->getDescendants<State>() ;
      
      for(std::set<State*>::const_iterator sub_state = sub_states.begin() ;
          sub_state != sub_states.end() ;
          ++sub_state)
      {
        (*sub_state)->exitSubStates() ;
      }
    }
  }
}

