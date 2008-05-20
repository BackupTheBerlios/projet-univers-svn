/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                    *
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
#include <Ogre.h>

#include <kernel/log.h>

#include <sound/implementation/openal/openal.h>

#include <sound/implementation/sound_internal.h>
#include <sound/sound.h>

namespace ProjetUnivers {
  namespace Sound {

  /*!
    @name Attributes
  */
  // @{

    bool initialised = false ;

    /// for ogre audio loading     
    Ogre::LogManager*       log_manager ;
    Ogre::Root*             root ;
    
  // @}

    void initRessources()
    {
      /// if sufficient ressources have not been initialised...
      InternalMessage("Sound","Sound::initRessources entering") ;
      if (! Ogre::MeshManager::getSingletonPtr())
      {
        log_manager = new Ogre::LogManager() ;
        log_manager->createLog("Ogre.log", false, false); 
        root = new Ogre::Root() ;
        
        Ogre::ConfigFile file ;
        file.load("ressources.cfg") ;

        // On parcours ses sections
        Ogre::ConfigFile::SectionIterator section = file.getSectionIterator();

        Ogre::String nomSection, nomType, nomArchitecture ;
        while (section.hasMoreElements())
        {
          nomSection = section.peekNextKey();
          Ogre::ConfigFile::SettingsMultiMap* settings = section.getNext();
          
          Ogre::ConfigFile::SettingsMultiMap::iterator i;
          for (i = settings->begin(); i != settings->end(); ++i)
          {
              nomType = i->first;
              nomArchitecture = i->second;
              Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                  nomArchitecture, nomType, nomSection);
          }
        }
      }

      InternalMessage("Sound","Sound::initRessources leaving") ;
    }
    
    void init() 
    {
      InternalMessage("Sound","Sound::init entering") ;
      if (! initialised)
      {
        initialised = true ;
        Implementation::OpenAL::init() ;    
      }
      InternalMessage("Sound","Sound::init leaving") ;
    }
    
    void close()
    {
      InternalMessage("Sound","Sound::close entering") ;

      Implementation::OpenAL::close() ;
      initialised = false ;
      
      InternalMessage("Sound","Sound::close leaving") ;
    }

    void update()
    {
      Implementation::OpenAL::update() ;
    }

    Kernel::ViewPoint* build(Kernel::Object* listener, Kernel::Object* reference)
    {
      InternalMessage("Sound","Sound::build entering") ;
      InternalMessage("Sound","Sound::build leaving") ; 
      return Implementation::OpenAL::build(listener, reference) ;      
    }

    
  }
}

