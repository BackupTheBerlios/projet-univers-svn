/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <OgreVector3.h>

#include <kernel/log.h>

#include <model/explosion.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/engine.h>
#include <display/implementation/ogre/ogre.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {

      DeclareDeducedTrait(Engine,And(HasTrait(RecursivelyPositioned),
                                     HasTrait(Model::Engine),
                                     // @todo remove this hack
                                     Not(HasParent(HasTrait(Model::Explosion))))) ;

      namespace Ogre
      {

        RegisterView(Ogre::Engine,
            Implementation::Engine,
            Ogre::RealWorldViewPoint) ;

        void Engine::onInit()
        {
          InternalMessage("Display","Entering Ogre::Engine::onInit") ;

          Positioned* positioned(getView<Positioned>()) ;
          Model::Engine* engine(getTrait<Model::Engine>()) ;

          m_output_node = positioned->getNode()->createChildSceneNode(convert(engine->getOutputPosition())) ;

          m_thrust = this->getViewPoint()->getManager()
                         ->createEntity(Utility::getUniqueName(),"thrust.mesh") ;

          m_output_node->attachObject(m_thrust) ;
          // reset scale factor
          scale(m_output_node,engine->getOutputRadius(),engine->getOutputRadius(),engine->getOutputRadius()*2) ;

          m_thrust->setMaterialName("PU/Base/Thrust") ;

          // pass power as a custom parameter to fragment program
          m_thrust->getSubEntity(0)->setCustomParameter(0,::Ogre::Vector4(engine->getPowerPercentage(),0,0,0)) ;

          InternalMessage("Display","Leaving Ogre::Engine::onInit") ;
        }

        void Engine::onClose()
        {
          InternalMessage("Display","Display::Engine::onClose Entering") ;

          this->getViewPoint()->getManager()
               ->destroyEntity(m_thrust) ;

          InternalMessage("Display","Display::Engine::onClose Leaving") ;
        }

        void Engine::onUpdate()
        {
          Model::Engine* engine(getTrait<Model::Engine>()) ;
          m_thrust->getSubEntity(0)->setCustomParameter(0,::Ogre::Vector4(engine->getPowerPercentage(),0,0,0)) ;
        }

      }
    }
  }
}
