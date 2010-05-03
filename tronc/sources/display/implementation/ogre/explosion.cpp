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
#include <model/positioned.h>
#include <model/explosion.h>
#include <display/implementation/ogre/ogre.h>
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

          m_node = getView<Positioned>()->getNode()->createChildSceneNode() ;

          Model::Explosion* explosion = getTrait<Model::Explosion>() ;
          createAnimatedBillboard(m_node,"PU/explosion/explosion",explosion->getDuration(),explosion->getRadius()) ;

          InternalMessage("Display","Leaving Ogre::Explosion::onInit") ;
        }

        void Explosion::onClose()
        {
          InternalMessage("Display","Display::Explosion::onClose Entering") ;

          if (getAncestor<Model::Positioned>())
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
