/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#ifndef PU_MODEL_TRANSPONDER_H
#define PU_MODEL_TRANSPONDER_H

#include <kernel/object_reference.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
      
    /// System that identify object's team by a code.
    class Transponder : public Kernel::Trait
    {
    public:
    
      /// Constructs.
      Transponder(Kernel::Object* team) ;

      /// Change transponder code.
      void setCode(Kernel::Object*) ;
      
      /// Access to the transponder code.
      Kernel::Object* getCode() const ;

      /// True iff the two given codes indicate friends.
      static bool areFriend(Kernel::Object* code1,Kernel::Object* code2) ;
      
      /// True iff the two given codes indicate foes.
      static bool areFoe(Kernel::Object* code1,Kernel::Object* code2) ;
      
    private:
      
      /// The code.
      Kernel::ObjectReference m_code ;
    };
  }
}

#endif /*PU_MODEL_TRANSPONDER_H*/
