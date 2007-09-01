/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                 *
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
#ifndef PU_SOUND_IMPLEMENTATION_SOUND_BACKGROUND_H_
#define PU_SOUND_IMPLEMENTATION_SOUND_BACKGROUND_H_

#include <kernel/log.h>

#include <sound/implementation/openan/sound_background.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

      	RegisterView(OpenAL::BackgroundSound, 
                          Model::BackgroundSound, 
                          OpenAL::RealWorldViewPoint) ;
             
      	BackgroundSound::BackgroundSound(Model::BackgroundSound*    i_observer,
                                RealWorldViewPoint* i_viewpoint) 
        : Kernel::TraitView<Model::BackgroundSound,RealWorldViewPoint>(i_observer,i_viewpoint),
        SoundEmitter()
        {
      		InternalMessage("Building OpenAL::BackgroundSound") ;
        }
        	          
  	    Name BackgroundSound::getSoundFileName()
  	    {
  	    	this->getModel()->getFileName();
  	    }
  	      
  	    bool BackgroundSound::isLooping()
  	    {
  	    	return true;
  	    }
  	      
  	    bool BackgroundSound::isActive()
  	    {
  	    	return true;
  	    }
  	      
  	    bool BackgroundSound::isListenerRelative()
  	    {
  	    	return true;
  	    }
  	      
  	    Position BackgroundSound::getPosition()
  	    {
  	    	return Position();
  	    }
  	      
  	    Orientation BackgroundSound::getOrientation()
  	    {
  	    	return Orientation();
  	    }
  	      
  	    Speed BackgroundSound::getSpeed()
  	    {
  	    	return Speed();
  	    }
  	
  	    float BackgroundSound::getOuterAngle()
  	    {
  	    	return 360f;
  	    }
  	      
  	    
  	    float BackgroundSound::getInnerAngle()
  	    {
  	    	return 360f;
  	    }
  	      
  	   
  	    float BackgroundSound::getMaxDistance()
  	    {
  	    	return 1000f;
  	    }
        	
        void onInit()
        {
        	this->initSound();
        }
        	          
        void onClose()
        {
        	this->deleteSound();
        }
        	          
        void onUpdate()
        {
        	this->updateSource();
        } 
      
      }
    }
  }
}
