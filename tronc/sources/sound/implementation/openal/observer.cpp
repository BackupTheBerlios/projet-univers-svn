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

#include <sound/implementation/openal/observer.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace OpenAL {
        
        RegisterView(OpenAL::Observer, 
                     Model::Observer, 
                     OpenAL::RealWorldViewPoint) ;
        
        Observer::Observer(Model::Observer*    i_observer,
                           RealWorldViewPoint* i_viewpoint) 
        : Kernel::TraitView<Model::Observer,RealWorldViewPoint>(i_observer,i_viewpoint),
          SoundListener()
        {
          InternalMessage("Building OpenAL::Observer") ;
        }
        
        float Observer::getGain()
        {
        	return 1.0f;
        }
                   	        
        Position Observer::getPosition()
        {	
        	Model::Positionned* positionned = this->getObject()->getTrait<Model::Positionned>();
        	if(positionned)
        	{
        		//TODO warning la position n'est pas absolu
        		return positionned.getPosition();
        	}
        	else
        	{
        		return Position();
        	}
        }
                   	            
        Orientation Observer::getOrientation()
        {
        	Model::Oriented* oriented = this->getObject()->getTrait<Model::Oriented>();
        	if(oriented)
        	{
        	   //TODO warning l'orientation n'est pas absolu
        	   return oriented.getOrientation();
        	}
        	else
        	{
        	   return Orientation();
        	}
        }
                   	            
        Speed Observer::getSpeed()
        {
        	Model::Mobile* mobile = this->getObject()->getTrait<Model::Mobile>();
        	if(mobile)
        	{
        		//TODO warning la vitesse n'est pas absolu
        		return mobile.getSpeed();
        	}
        	else
        	{
        		return Speed();
        	}
        }
        
        
        void Observer::onInit()
        {
          InternalMessage("OpenAL::Observer::onInit Entering") ;

          this->updateListener();
                      
          InternalMessage("OpenAL::Observer::onInit Leaving") ;
        }
          
        void Observer::onClose()
        {
          InternalMessage("Display::Observer::onClose Entering") ;

          //Just one listener by context in openal , it's destroy with openal context
          
          InternalMessage("Display::Observer::onClose Leaving") ;
        }
        
        void Observer::onUpdate()
        {
        	this->updateListener();
        }
        
      }
    }
  }
}

