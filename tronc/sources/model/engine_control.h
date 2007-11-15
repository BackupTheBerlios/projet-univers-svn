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
#ifndef PU_MODEL_ENGINE_CONTROL_H_
#define PU_MODEL_ENGINE_CONTROL_H_

#include <kernel/trait.h>
#include <kernel/trait_reference.h>

#include <model/engine.h>
#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// Component that control engines.
    /*!
        
    */
    class EngineControl : public Kernel::Trait
    {
    public:

      /// Constructor.
      EngineControl(Oriented* i_throttle,Engine* i_engine) ;
      
      /// Perfom engine control.
      int getPowerPercentage() const ;
      
    private:
      
      /// The engine 
      /*!
      */ 
      Kernel::TraitReference<Engine>   m_engine ;
      
      /// The throttle.
      /*!
        An oriented object whose only interesting value is the Pitch ?
      */
      Kernel::TraitReference<Oriented> m_throttle ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_ENGINE_CONTROL_H_*/
