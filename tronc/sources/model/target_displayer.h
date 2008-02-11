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
#ifndef PU_MODEL_TARGET_DISPLAYER_H_
#define PU_MODEL_TARGET_DISPLAYER_H_

#include <kernel/object_reference.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
      
    /// System that display targets on a hud.
    class TargetDisplayer : public Kernel::Trait
    {
    public:

      /// Constructs.
      TargetDisplayer() ;
      
      /// Connect a target displayer to a targeting system.
      static void connect(Kernel::Object* target_displayer,
                          Kernel::Object* targeting_system) ;
      
      /// Access to current target.
      Kernel::Object* getTargetingSystem() const ;
      
      /// Access to computer model.
      Kernel::Model* getComputerModel() const ;
      
    private:
      
      /// The system handling targets to display.
      mutable Kernel::ObjectReference m_targeting_system ;
    };
  }
}

#endif /*PU_MODEL_TARGET_DISPLAYER_H_*/
