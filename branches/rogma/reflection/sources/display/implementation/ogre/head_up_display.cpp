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
#include <kernel/string.h>
#include <kernel/log.h>
#include <kernel/parameters.h>

#include <model/positioned.h>

#include <display/implementation/head_up_display.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/solid.h>
#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/head_up_display.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(HeadUpDisplay,
                     Implementation::HeadUpDisplay,
                     Ogre::RealWorldViewPoint) ;

        void HeadUpDisplay::onInit()
        {
          m_implementation.reset(
                new HUD::HeadUpDisplayViewPoint(getObject(),
                                                getViewPoint())) ;
          m_implementation->init() ;

          m_overlay = getOverlay("PU/base/HUD/Reticule") ;

          m_overlay->show() ;

          getOverlay()->show() ;
        }
        
        void HeadUpDisplay::onClose()
        {
          if (m_implementation.get())
          {
            m_implementation.reset() ;
          }
          if (m_overlay)
          {
            m_overlay->hide() ;
          }
        }

        void HeadUpDisplay::onUpdate()
        {
          if (m_implementation.get())
          {
            m_implementation->update(0) ;
          }
        }
        
      }
    }
  }
}
