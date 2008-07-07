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
#include <kernel/error.h>

#include <display/implementation/ogre/ogre.h>

#include <display/display.h>
#include <display/display_input.h>

namespace ProjetUnivers {
  namespace Display {


    size_t getWindowHandle()
    {
      return Implementation::Ogre::getWindowHandle() ;
    }

    void getWindowSize(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top)
    {
      Implementation::Ogre::getWindowSize(width,height,depth,left,top) ;
    }

    void injectKey(const unsigned int& key_code)
    {
      Implementation::Ogre::injectKey(key_code) ;
    }
	
    void start()
    {
    }

    void terminate()
    {
    }
    
  }
}
