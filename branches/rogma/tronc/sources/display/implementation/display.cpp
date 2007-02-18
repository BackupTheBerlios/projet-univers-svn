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

#include <kernel/ensemble_composition.h>


#include <display/exception.h>
#include <display/implementation/ogre/ogre.h>
#include <display/view_point.h>

#include <display/display.h>

namespace ProjetUnivers {
  namespace Display {

  /*!
    @name Attributs
  */
  // @{

    struct LocalMemory 
    {
      /// Les points de vue gérés par l'affichage.
      /*!
        @composite
      */
      std::set<ViewPoint*> viewPoints ;
      
      void clear() 
      {
        for(std::set<ViewPoint*>::iterator viewpoint = viewPoints.begin() ;
            viewpoint != viewPoints.end() ;
            ++viewpoint)
        {
          delete *viewpoint ;
        }
      }      
      ~LocalMemory()
      {
        clear() ;
      }
    };
    
    LocalMemory local ;
    
    /// Le point de vue actif.
    ViewPoint* active ;

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
      local.clear() ;
      Implementation::Ogre::close() ;
    }

    size_t getWindowHandle()
    {
      check(initialise, Exception("Module non initialisé")) ;
      
      return Implementation::Ogre::getWindowHandle() ;
    }

    /// Accès à la taille de la fenêtre
    void getWindowSize(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top)
    {
      check(initialise, Exception("Module non initialisé")) ;

      Implementation::Ogre::getWindowSize(width,height,depth,left,top) ;
    }

    /// Ajoute un point de vue.
    ViewPoint* addViewPoint(ViewPoint* _pdv)
    {
      local.viewPoints.insert(_pdv) ;
      return _pdv ;
    }

    /// Supprime le point de vue.
    void removeViewPoint(ViewPoint* _pdv)
    {
      if (local.viewPoints.erase(_pdv) != 0)
      {
        delete _pdv ;
      }
    }
    
    
    /// 
    /*!
      Inutile car il suffit d'activer un autre point de vue ?
    */
    void desactivateViewPoint(ViewPoint* _pdv)
    {
      if (_pdv)
      {
        _pdv->desactivate() ;
      }
    }
    
    /// Le point de vue devient celui actif.
    void activateViewPoint(ViewPoint* _pdv)
    {
      if (_pdv)
      {
        desactivateViewPoint(active) ;
        active = _pdv ;
        active->init() ;
        active->activate() ;
      }      
    }
  
  
    void update() 
    {
      check(initialised, Exception("Module non initialisé")) ;
      check(active!=NULL, Exception("Pas de point de vue actif")) ;
    
      active->update() ;
      Implementation::Ogre::update() ;
    }
  }
  
}
