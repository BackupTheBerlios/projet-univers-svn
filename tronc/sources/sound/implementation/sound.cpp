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
#include <kernel/log.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/real_world_view_point.h>

#include <sound/sound.h>

namespace ProjetUnivers {
  namespace Sound {

  /*!
    @name Attributes
  */
  // @{

    bool initialised = false ;
    std::auto_ptr<Implementation::OpenAL::RealWorldViewPoint> m_sound_system ;
  // @}
    
    void init() 
    {
      InternalMessage("Sound::init entering") ;
      if (! initialised)
      {
        initialised = true ;
        
        Implementation::OpenAL::init() ;    
      }
      InternalMessage("Sound::init leaving") ;
    }
    
    void close()
    {
      InternalMessage("Sound::close entering") ;

      Implementation::OpenAL::close() ;
      
      initialised = false ;
      
      InternalMessage("Sound::close leaving") ;
    }

    void update()
    {
      Implementation::OpenAL::update() ;
    }

    Kernel::ViewPoint* build(Kernel::Object* observer)
    {
      m_sound_system.reset(new Implementation::OpenAL::RealWorldViewPoint(observer)) ;
      m_sound_system->init() ;
    }

  }
}

