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

#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/laser_beam.h>
#include <display/implementation/ogre/ogre.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {

      DeclareDeducedTrait(LaserBeam,And(HasTrait(Model::LaserBeam),HasTrait(RecursivelyPositioned))) ;

      namespace Ogre
      {

        RegisterView(Ogre::LaserBeam,
                     Implementation::LaserBeam,
                     Ogre::RealWorldViewPoint) ;


        void LaserBeam::onInit()
        {
          InternalMessage("Display","Entering Ogre::LaserBeam::onInit") ;

          Positioned* positioned(getView<Positioned>()) ;

          m_beam = this->getViewPoint()->getManager()->createRibbonTrail(Utility::getUniqueName()) ;

          m_beam->addNode(positioned->getNode()) ;
          m_beam->setNumberOfChains(1) ;
          m_beam->setMaterialName("PU/base/laser") ;
          m_beam->setMaxChainElements(400) ;
          m_beam->setInitialColour(0,::Ogre::ColourValue::Red) ;

          Model::LaserBeam* laser_beam(getTrait<Model::LaserBeam>()) ;
          m_beam->setTrailLength(convert(laser_beam->getLength())) ;
          m_beam->setInitialWidth(0,convert(laser_beam->getRadius())) ;

          // put it on the node
          m_node = this->getViewPoint()->getManager()->getRootSceneNode()->createChildSceneNode() ;
          m_node->attachObject(m_beam) ;

          InternalMessage("Display","Leaving Ogre::LaserBeam::onInit") ;
        }

        void LaserBeam::onClose()
        {
          InternalMessage("Display","Display::LaserBeam::onClose Entering") ;

          this->getViewPoint()->getManager()->destroyRibbonTrail(m_beam) ;
          this->getViewPoint()->getManager()->destroySceneNode(m_node->getName()) ;

          InternalMessage("Display","Display::LaserBeam::onClose Leaving") ;
        }



      }
    }
  }
}
