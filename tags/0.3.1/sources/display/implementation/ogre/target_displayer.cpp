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
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/target_displayer.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// This view will be automatically maintained.
        RegisterView(TargetDisplayer,
                     Model::TargetDisplayer,
                     Ogre::RealWorldViewPoint) ;

        TargetDisplayer::TargetDisplayer(Model::TargetDisplayer* i_object,
                                         RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::TargetDisplayer,
                            RealWorldViewPoint>(i_object,i_viewpoint),
          m_reticule_container(NULL),
          m_reticule(NULL),
          m_implementation(NULL)
        {}

        namespace 
        {
          std::string reticule_material ;
        }
        
        std::string getReticuleMaterial()
        {
          if (reticule_material == "")
          {
            try
            {
              reticule_material = Kernel::Parameters::getValue<std::string>("Display","ReticuleMaterial") ;
            }
            catch(...)
            {
              InternalMessage("Display","getReticuleMaterial : error") ;
              reticule_material = "PU/material/reticule" ;
            }
          }
          return reticule_material ;
        }

        void TargetDisplayer::onInit()
        {
          m_implementation.reset(
                new HeadUpDisplay::TargetDisplayerViewPoint(getObject(),
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
        
        void TargetDisplayer::onClose()
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

        void TargetDisplayer::onUpdate()
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
