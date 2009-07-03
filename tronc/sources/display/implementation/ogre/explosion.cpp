/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <model/positionned.h>
#include <model/explosion.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/explosion.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::Explosion,
                     Implementation::Explosion,
                     Ogre::RealWorldViewPoint) ;


        void Explosion::onInit()
        {
          InternalMessage("Display","Entering Ogre::Explosion::onInit") ;

          Model::Positionned* positionned = getObject()->getTrait<Model::Positionned>() ;

          Implementation::Positionned* positionned_ancestor
            = getObject()->getAncestor<Implementation::Positionned>() ;

          if (positionned_ancestor)
          {
            Positionned* parent_node(positionned_ancestor->getView<Positionned>(getViewPoint())) ;
            m_node = static_cast< ::Ogre::SceneNode* >(parent_node->getNode()->createChild()) ;
            m_node->setPosition(convert(positionned->getPosition())) ;
          }
          else
          {
            m_node = this->getViewPoint()->getManager()->getRootSceneNode() ;
            getViewPoint()->setRootObject(getObject()) ;
          }

          m_mesh = this->getViewPoint()->getManager()
                   ->createEntity(Utility::getUniqueName(),
                                 "explosion.mesh") ;

          // reset scale factor
          float size = getObject()->getTrait<Model::Explosion>()->getRadius().Meter()/conversion_factor ;

          m_node->setScale(::Ogre::Vector3(size,size,size)) ;

          // change orientation
          ::Ogre::Vector3 point(getViewPoint()->getObserver()
                                              ->getTrait<Implementation::Positionned>()
                                              ->getView<Positionned>(getViewPoint())
                                              ->getNode()->_getDerivedPosition()) ;
          m_node->lookAt(point,::Ogre::Node::TS_WORLD,::Ogre::Vector3::UNIT_Z) ;

          // change explosion duration
          std::string material_name = m_mesh->getMesh()->getSubMesh(0)->getMaterialName() ;
          ::Ogre::MaterialPtr material = ::Ogre::MaterialManager::getSingleton().getByName(material_name) ;

          // cloning material then modifying it
          ::Ogre::MaterialPtr cloned_material = material->clone(Utility::getUniqueName()) ;
          ::Ogre::TextureUnitState* texture = cloned_material->getTechnique(0)->getPass(0)->getTextureUnitState(0) ;

          InternalMessage("Display","texture name = " + texture->getTextureName()) ;

          std::string texture_name = texture->getTextureName() ;

          std::string file_name = texture_name.substr(0,texture_name.find_last_of('_')) ;
          std::string extension = texture_name.substr(texture_name.find_last_of('.')) ;
          InternalMessage("Display","file name = " + file_name + extension) ;

          texture->setAnimatedTextureName(file_name + extension,texture->getNumFrames(),getObject()->getTrait<Model::Explosion>()->getDuration().Second()) ;
          cloned_material->compile(true) ;

          // @see http://www.ogre3d.org/phpBB2/viewtopic.php?t=39502&highlight=changing+material
          m_mesh->getSubEntity(0)->setMaterialName(cloned_material->getName()) ;
          // put it on the node
          m_node->attachObject(m_mesh) ;

          InternalMessage("Display","Leaving Ogre::Explosion::onInit") ;
        }

        void Explosion::onClose()
        {
          InternalMessage("Display","Display::Explosion::onClose Entering") ;

          if (getObject()->getAncestor<Model::Positionned>())
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->m_node->getName()) ;
          }

          InternalMessage("Display","Display::Explosion::onClose Leaving") ;
        }


      }
    }
  }
}
