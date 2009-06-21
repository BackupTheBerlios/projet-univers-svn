/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD Mathieu ROGER                 *
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

#include <model/shot.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/shot.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        RegisterView(OpenAL::Shot, 
                     Implementation::Shot, 
                     OpenAL::RealWorldViewPoint) ;
             
        Shot::Shot(
          Implementation::Shot*        object,
          OpenAL::RealWorldViewPoint*  viewpoint) 
        : Kernel::TraitView<Implementation::Shot,
                            OpenAL::RealWorldViewPoint>(object,viewpoint),
          SoundEmitter()
        {
          InternalMessage("Sound","Building OpenAL::Shot") ;
        }
                    
        std::string Shot::getSoundFileName() const
        {
          return "laser.ogg" ;
        }
          
        bool Shot::isEvent() const
        {
          return true;
        }
        
        Kernel::Object* Shot::getObject() const
        {
          getTrait()->getObject() ;
        }
        
        void Shot::onInit()
        {
          this->initSound(getViewPoint());
        }
                    
        void Shot::onClose()
        {
          this->deleteSound();
        }
                    
        void Shot::onUpdate()
        {
          this->updateSource(getViewPoint());
        }
        
        void Shot::onChangeParent(Kernel::Object* old_parent)
        {
          this->changeParentSource(getViewPoint()) ;
        }
      
      }
    }
  }
}
