/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD                               *
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
#include <kernel/parameters.h>
#include <model/collision.h>
#include <model/laser_beam.h>
#include <sound/implementation/openal/collision.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        RegisterView(OpenAL::Collision,
                     Implementation::Collision,
                     OpenAL::RealWorldViewPoint) ;
             
        const std::string Collision::MaximumCollisionEnergyJoules("MaximumCollisionEnergyJoules") ;

        std::string Collision::getSoundFileName() const
        {
          Model::Collision* collision = getTrait<Model::Collision>() ;
          if (collision->getObject1()->getTrait<Model::LaserBeam>() ||
              collision->getObject2()->getTrait<Model::LaserBeam>())
            return "pu_impact_coque.ogg" ;
          else
            return "pu_choc.ogg";
        }
          
        bool Collision::isEvent() const
        {
          return true;
        }

        Kernel::Object* Collision::getObject() const
        {
          return getTrait()->getObject() ;
        }
        
        void Collision::onInit()
        {
          this->initSound(getViewPoint());
        }
                    
        void Collision::onClose()
        {
          this->deleteSound();
        }
                    
        void Collision::onUpdate()
        {
          this->updateSource();
        } 

        float Collision::getGain() const
        {
          Model::Energy energy(getTrait<Model::Collision>()->getEnergy()) ;

          // get a constant magic value and divide, cap to 1
          float maximum_joules = Kernel::Parameters::getValue<float>("Sound",MaximumCollisionEnergyJoules,200) ;

          return std::min(energy.Joule()/maximum_joules,(float)1) ;
        }

      }
    }
  }
}
