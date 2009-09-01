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

#include <model/detection_data.h>
#include <model/positionned.h>

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
                     Model::HeadUpDisplay,
                     Ogre::RealWorldViewPoint) ;

        namespace 
        {
          std::string reticule_material ;
        }
        
        std::string getReticuleMaterial()
        {
          if (reticule_material == "")
          {
            reticule_material = Kernel::Parameters::getValue<std::string>("Display","ReticuleMaterial","PU/material/reticule") ;
          }
          return reticule_material ;
        }

        void HeadUpDisplay::onInit()
        {
          m_implementation.reset(
                new HUD::HeadUpDisplayViewPoint(getObject(),
                                                getViewPoint())) ;
          m_implementation->init() ;

          m_reticule_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName())) ;
          getOverlay()->add2D(m_reticule_container) ;
          
          m_reticule_container->setPosition(0,0) ;
          m_reticule_container->setWidth(1) ;
          m_reticule_container->setHeight(1) ;

          m_reticule = 
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName()) ;
          m_reticule->setMaterialName(getReticuleMaterial()) ; 
          
          m_reticule->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
          m_reticule->setVerticalAlignment(::Ogre::GVA_CENTER) ;
          m_reticule_container->_addChild(m_reticule) ;

          const float size = 0.05 ;
          
          m_reticule->setLeft(-size/2) ;
          m_reticule->setTop(-size/2) ;
          m_reticule->setDimensions(size,size) ;
          
          getOverlay()->show() ;
        }
        
        void HeadUpDisplay::onClose()
        {
          if (m_implementation.get())
          {
            m_implementation.reset() ;
          }
          if (m_reticule_container)
          {
            getOverlay()->remove2D(m_reticule_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule_container) ;
            m_reticule_container = NULL ;
            m_reticule = NULL ;
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
