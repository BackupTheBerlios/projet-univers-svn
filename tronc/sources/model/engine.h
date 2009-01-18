/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_ENGINE_H_
#define PU_MODEL_ENGINE_H_

#include <kernel/object_reference.h>
#include <kernel/reader.h>

#include <model/force_generator.h>
#include <model/force.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
  
    namespace Test
    {
      class TestLoad ;
    }
    
    class EngineControler ;
    
    /// Ship/Other objects engine.
    class Engine : public ForceGenerator
    {
    public:

      /// Constructor.
      Engine(const Force& i_force) ;

      /// Read an Engine trait.
      /*!
        stored as 
        @code
          <Engine>
            [<ObjectReference ... [name="controler"]/>]
            <Force ... />
          </Engine>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Get the force.
      virtual Force getAppliedForce() const ;
      
      /// The percentage of power of the engine
      float getPowerPercentage() const ;
      
    private:
      
      /// Maximal "force". 
      /*!
        Orientation is relative to parent physical object.
        Thus normally a ship force is : (0,0,100) or something.
      */
      Force m_full_thrust ;
      
      /// Controler of this engine
      Kernel::ObjectReference m_controler ;
      
      friend void connectControlerEngine(Kernel::Object*,Kernel::Object*) ;
      
      friend class ProjetUnivers::Model::Test::TestLoad ;
    };
    
    
  }
}

#endif /*PU_MODEL_ENGINE_H_*/
