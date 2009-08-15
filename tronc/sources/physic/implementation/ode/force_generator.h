/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#pragma once

#include <kernel/controler.h>
#include <kernel/object.h>
#include <kernel/deduced_trait.h>

#include <model/force_generator.h>

#include <physic/implementation/ode/physic_system.h>

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Implementation
    {

      class ForceGenerator : public Kernel::DeducedTrait
      {};

      namespace Ode
      {
        
        class PhysicalObject ;
              
        /// Force controller.
        /*!
          @see Model::ForceGenerator
        */
        class ForceGenerator : public Kernel::Controler<ForceGenerator,
                                                        PhysicSystem>
        {
        public:
          
          /// simulation
          virtual void prepare() ;
          
        protected:
        
          /// Called after the view is created on a initialized viewpoint.
          virtual void onInit() ;
    
          /// Called when parent changed.
          virtual void onChangeParent(Kernel::Object* i_old_parent) ;
          
        private:

          /// Calculate the object on which this force applies. 
          PhysicalObject* determineObject() const ;

          PhysicalObject* m_object ;
        };
      }
    }
  }
}
