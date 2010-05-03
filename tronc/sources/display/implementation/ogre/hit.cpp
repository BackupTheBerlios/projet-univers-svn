/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/sized.h>
#include <model/positioned.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/hit.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Hit,Implementation::Hit,RealWorldViewPoint) ;

        void Hit::onInit()
        {
          InternalMessage("Display","Entering Hit::onInit") ;

          m_node = getView<Positioned>()->getNode()->createChildSceneNode() ;

          createAnimatedBillboard(m_node,"PU/explosion/explosion",Model::Duration::Second(1),getTrait<Model::Sized>()->getRadius()) ;
        }

        void Hit::onClose()
        {
          if (getAncestor<Model::Positioned>())
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->m_node->getName()) ;
          }
        }

      }
    }
  }
}

