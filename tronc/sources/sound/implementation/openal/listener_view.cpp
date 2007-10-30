/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                    *
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

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/listener_view.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        RegisterView(OpenAL::ListenerView, 
                     OpenAL::Listener, 
                     OpenAL::RealWorldViewPoint) ;
        
        ListenerView::ListenerView(
          OpenAL::Listener* i_observer,
          OpenAL::RealWorldViewPoint*     i_viewpoint) 
        : Kernel::TraitView<OpenAL::Listener,OpenAL::RealWorldViewPoint>(i_observer,i_viewpoint),
        SoundListener()
        {
          InternalMessage("Building OpenAL::Listener") ;
        }
        
        float ListenerView::getGain() const
        {
          return 1.0f;
        }
        
        Kernel::Object* ListenerView::getObject() const
        {
          getModel()->getObject() ;
        }
        
        void ListenerView::onInit()
        {
          InternalMessage("OpenAL::Listener::onInit Entering") ;

          this->updateListener();
                      
          InternalMessage("OpenAL::Listener::onInit Leaving") ;
        }
          
        void ListenerView::onClose()
        {
          InternalMessage("OpenAL::Listener::onClose Entering") ;

          //Just one listener by context in openal , it's destroy with openal context
          
          InternalMessage("OpenAL::Listener::onClose Leaving") ;
        }
        
        void ListenerView::onUpdate()
        {
          this->updateListener();
        }
        
      }
    }
  }
}

