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
#include <kernel/view_point.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/real_world_view_point.h>

#include <display/display.h>
#include <display/display_input.h>
#include <display/implementation/display_internal.h>

namespace ProjetUnivers {
  namespace Display {

  /*!
    @name Attributes
  */
  // @{

    struct LocalMemory 
    {
      /// Display view points.
      /*!
        @composite
      */
      std::set<Kernel::ViewPoint*> m_viewPoints ;
      
      void clear() 
      {
        for(std::set<Kernel::ViewPoint*>::iterator viewpoint = m_viewPoints.begin() ;
            viewpoint != m_viewPoints.end() ;
            ++viewpoint)
        {
          delete *viewpoint ;
        }
        m_viewPoints.clear() ;
      }      
      ~LocalMemory()
      {
        clear() ;
      }
    };
    
    LocalMemory local ;
    
    /// active wiepoint.
    Implementation::Ogre::RealWorldViewPoint* active = NULL ;

    bool initialised = false ;

  // @}
    
    bool init(bool choose_display) 
    {
      if (! initialised)
      {
        bool result = Implementation::Ogre::init(choose_display) ; 
        
        initialised = true ;
        
        if (active)
        {
          active->init() ;
        }      
      
        return result ;
      }
      else
      {
        // déjà initialisé
        return true ;
      }
    }
    
    void close()
    {
      if (active)
      {
        active->close() ;
        active = NULL ;
      }
      
      local.clear() ;
      Implementation::Ogre::close() ;
      initialised = false ;
    }

    size_t getWindowHandle()
    {
      CHECK(initialised, "Uninitialised module") ;
      
      return Implementation::Ogre::getWindowHandle() ;
    }

    void getWindowSize(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top)
    {
      CHECK(initialised,"Module non initialisé") ;

      Implementation::Ogre::getWindowSize(width,height,depth,left,top) ;
    }

    Kernel::ViewPoint* addViewPoint(Kernel::ViewPoint* viewpoint)
    {
      local.m_viewPoints.insert(viewpoint) ;
      return viewpoint ;
    }

    void desactivateViewPoint(Kernel::ViewPoint* viewpoint)
    {
      if (viewpoint)
      {
        viewpoint->close() ;
      }
    }

    void removeViewPoint(Kernel::ViewPoint* viewpoint)
    {
      if (active == viewpoint)
      {
        desactivateViewPoint(active) ;
        active = NULL ;
      }
      
      if (local.m_viewPoints.erase(viewpoint) != 0)
      {
        delete viewpoint ;
      }
    }

    /// @c i_viewpoint becomes the active viewpoint.
    void activateViewPoint(Implementation::Ogre::RealWorldViewPoint* i_viewpoint)
    {
      if (i_viewpoint)
      {
        desactivateViewPoint(active) ;
        active = i_viewpoint ;
        
        /// if not initialised init it.
        active->init() ;
      }      
    }

    Kernel::ViewPoint* buildRealWorldViewPoint(Kernel::Object* i_observer)
    {
      Implementation::Ogre::RealWorldViewPoint* temp = new Implementation::Ogre::RealWorldViewPoint(i_observer->getModel()) ;
      addViewPoint(temp) ;
      activateViewPoint(temp) ;
      return temp ;
    }
  
    void update() 
    {
      Implementation::Ogre::update() ;
    }

    void injectKey(const unsigned int& key_code)
    {
      Implementation::Ogre::injectKey(key_code) ;
    }
  }
}
