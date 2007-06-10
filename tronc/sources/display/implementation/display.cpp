/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <display/exception.h>
#include <display/implementation/real_world_view_point.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/real_world_view_point.h>

#include <display/display.h>
#include <display/display_input.h>

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
      std::set<Kernel::ViewPoint*> viewPoints ;
      
      void clear() 
      {
        for(std::set<Kernel::ViewPoint*>::iterator viewpoint = viewPoints.begin() ;
            viewpoint != viewPoints.end() ;
            ++viewpoint)
        {
          delete *viewpoint ;
        }
        viewPoints.clear() ;
      }      
      ~LocalMemory()
      {
        clear() ;
      }
    };
    
    LocalMemory local ;
    
    /// active wiepoint.
    Implementation::RealWorldViewPoint* active = NULL ;

    bool initialised = false ;

  // @}
    
    bool init() 
    {
      if (! initialised)
      {
        bool result = Implementation::Ogre::init() ; 
        
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
      }
      
      local.clear() ;
      Implementation::Ogre::close() ;
    }

    size_t getWindowHandle()
    {
      check(initialised, Exception("Module non initialisé")) ;
      
      return Implementation::Ogre::getWindowHandle() ;
    }

    void getWindowSize(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top)
    {
      check(initialised, Exception("Module non initialisé")) ;

      Implementation::Ogre::getWindowSize(width,height,depth,left,top) ;
    }

    Kernel::ViewPoint* addViewPoint(Kernel::ViewPoint* _pdv)
    {
      local.viewPoints.insert(_pdv) ;
      return _pdv ;
    }

    void desactivateViewPoint(Kernel::ViewPoint* _pdv)
    {
      if (_pdv)
      {
        _pdv->close() ;
      }
    }


    void removeViewPoint(Kernel::ViewPoint* _pdv)
    {
      if (active == _pdv)
      {
        desactivateViewPoint(active) ;
        active = NULL ;
      }
      
      if (local.viewPoints.erase(_pdv) != 0)
      {
        delete _pdv ;
      }
    }
    
    
    
    /// @c i_viewpoint becomes the active viewpoint.
    void activateViewPoint(Implementation::RealWorldViewPoint* i_viewpoint)
    {
      if (i_viewpoint)
      {
        desactivateViewPoint(active) ;
        active = i_viewpoint ;
        
        /// if not initialised init it.
        active->init() ;
        
        active->activate() ;
        
      }      
    }
    
    Kernel::ViewPoint* buildRealWorldViewPoint(Kernel::Object* i_observer)
    {
      Implementation::RealWorldViewPoint* temp = new Implementation::Ogre::RealWorldViewPoint(i_observer) ;
      addViewPoint(temp) ;
      /// ??? 
      activateViewPoint(temp) ;
      return temp ;
    }
  
    void update() 
    {
      check(initialised, Exception("Module non initialisé")) ;
      check(active!=NULL, Exception("Pas de point de vue actif")) ;
      Implementation::Ogre::update() ;
    }
  }
  
}
