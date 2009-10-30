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
#include <model/positioned.h>
#include <model/explosion.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
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

          Model::Positioned* positioned = getObject()->getTrait<Model::Positioned>() ;

          Implementation::Positioned* positioned_ancestor
            = getObject()->getAncestor<Implementation::Positioned>() ;

          if (positioned_ancestor)
          {
            Positioned* parent_node(positioned_ancestor->getView<Positioned>(getViewPoint())) ;
            m_node = static_cast< ::Ogre::SceneNode* >(parent_node->getNode()->createChild()) ;
            m_node->setPosition(convert(positioned->getPosition())) ;
          }
          else
          {
            m_node = this->getViewPoint()->getManager()->getRootSceneNode() ;
            getViewPoint()->setRootObject(getObject()) ;
          }

          m_particle = this->getViewPoint()->getManager()
                           ->createParticleSystem(Utility::getUniqueName(),"PU/explosion") ;
          m_particle->setKeepParticlesInLocalSpace(true) ;

          // reset scale factor
          float size = getObject()->getTrait<Model::Explosion>()->getRadius().Meter()/conversion_factor ;
          m_node->setScale(::Ogre::Vector3(size,size,size)) ;

          m_node->attachObject(m_particle) ;

          InternalMessage("Display","Leaving Ogre::Explosion::onInit") ;
        }

        void Explosion::onClose()
        {
          InternalMessage("Display","Display::Explosion::onClose Entering") ;

          if (getObject()->getAncestor<Model::Positioned>())
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
