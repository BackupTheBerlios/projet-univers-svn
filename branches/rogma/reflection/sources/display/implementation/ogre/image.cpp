/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2009 Mathieu ROGER                                 *
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
#include <model/image.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/image.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Image,Implementation::Image,RealWorldViewPoint) ;

        void Image::onInit()
        {
          InternalMessage("Display","Entering Image::onInit") ;
          m_image_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName())) ;
          getOverlay()->add2D(m_image_container) ;
          
          m_image_container->setPosition(0,0) ;
          m_image_container->setWidth(1) ;
          m_image_container->setHeight(1) ;

          m_image = 
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName()) ;

          std::string texture_name(Utility::getUniqueName()) ;
          ::Ogre::Image image ;
          image.load(getObject()->getTrait<Model::Image>()->getName(),"General") ;
          
          ::Ogre::TexturePtr texture = 
            ::Ogre::TextureManager::getSingleton().loadImage(
                  texture_name,
                  ::Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                  image) ;

          // Create a material using the texture
          std::string material_name(Utility::getUniqueName()) ;
          ::Ogre::MaterialPtr material = 
            ::Ogre::MaterialManager::getSingleton().create(
                  material_name,
                  ::Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME) ;

          material->getTechnique(0)->getPass(0)->createTextureUnitState(texture_name) ;
          
          m_image->setMaterialName(material_name) ;
          m_image_container->_addChild(m_image) ;
          m_image->setPosition(0,0) ;
          m_image->setWidth(1) ;
          m_image->setHeight(1) ;
          
          getOverlay()->show() ;
          m_image_container->show() ;
          m_image->show() ;
          
          // create a camera and a viewport if needed.
          Ogre::createCamera() ;
          
          InternalMessage("Display","Leaving Image::onInit") ;
        }
          
        void Image::onClose()
        {
          if (m_image_container)
          {
            getOverlay()->remove2D(m_image_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_image) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_image_container) ;
            m_image_container = NULL ;
            m_image = NULL ;
          }
        }
        
      }
    }
  }
}
