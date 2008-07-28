/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <kernel/object.h>
#include <model/player_configuration.h>
#include <input/implementation/ois/ois.h>
#include <input/implementation/input_object.h>
#include <input/implementation/input_internal.h>
#include <input/input_gui.h>
#include <input/input.h>

namespace ProjetUnivers {
  namespace Input {

    namespace {
      
      /// Objects that handle events and axes
      std::set<Implementation::InputObject*> m_objects ;
      
    }
    
    void registerObject(Implementation::InputObject* object)
    {
      m_objects.insert(object) ;
    }
    
    void unregisterObject(Implementation::InputObject* object)
    {
      m_objects.erase(object) ;
    }
    
    void start()
    {
      Implementation::OIS::start() ;
    }

    void terminate()
    {
      Implementation::OIS::terminate() ;
    }

    std::set<Model::PlayerConfiguration::InputEvent> getEvents()
    {
      std::set<Model::PlayerConfiguration::InputEvent> result ;
      for(std::set<Implementation::InputObject*>::const_iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        const std::set<Model::PlayerConfiguration::InputEvent>& temp = (*object)->getEvents() ;
        result.insert(temp.begin(),temp.end()) ;
      }
      return result ;
    }
    
    std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> getAxes()
    {
      std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> result ;
      for(std::set<Implementation::InputObject*>::const_iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        const std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage>& temp = (*object)->getAxes() ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }
    
    void apply(Model::PlayerConfiguration* configuration,Kernel::Object* object)
    {
      std::set<Model::PlayerConfiguration::InputEvent> events(getEvents()) ;
      
      for(std::set<Model::PlayerConfiguration::InputEvent>::const_iterator 
            event = events.begin() ;
          event != events.end() ;
          ++event)
      {
        std::string command = configuration->getCommand(*event) ;
        if (!command.empty())
        {
          InternalMessage("Input","applying " + command) ;
          object->call(command) ;
        }
      }
      
      std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> axes(getAxes()) ;
      
      for(std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage>::const_iterator 
            axis = axes.begin() ;
          axis != axes.end() ;
          ++axis)
      {
        std::string command = configuration->getAxis(axis->first) ;
        if (!command.empty())
        {
          InternalMessage("Input","applying " + command) ;
          object->call(command,int(axis->second)) ;
        }
        else
        {
          // try with inverted axis
          command = configuration->getAxis(-axis->first) ;
          if (!command.empty())
          {
            InternalMessage("Input","applying " + command) ;
            object->call(command,-int(axis->second)) ;
          }
        }
        
        
      }
      
    }
    
    ::OIS::Keyboard* getOISKeyboard()
    {
      return Implementation::OIS::getOISKeyboard() ;
    }
    
    void init()
    {
      Implementation::OIS::init() ;
    }
   
    void close()
    {
      Implementation::OIS::close() ;
    }

    void update()
    {
      Implementation::OIS::update() ;
    }
    
  }
}



