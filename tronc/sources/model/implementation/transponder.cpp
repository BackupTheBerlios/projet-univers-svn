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
#include <kernel/trait.h>
#include <kernel/object.h>
#include <model/transponder.h>

namespace ProjetUnivers {
  namespace Model {
      
    Transponder::Transponder(Kernel::Object* code)
    : m_code(code)
    {}

    void Transponder::setCode(Kernel::Object* code)
    {
      m_code = code ;
      notify() ;
    }
    
    Kernel::Object* Transponder::getCode() const
    {
      return m_code ;
    }

    bool Transponder::areFoe(Kernel::Object* code1,Kernel::Object* code2)
    {
      if (!code1 || !code2)
        return false ;
      
      Transponder* identification1 = code1->getParent<Transponder>() ;
      Transponder* identification2 = code2->getParent<Transponder>() ;
      
      if (!identification1 || !identification2)
        return false ;
      
      return identification1->getCode() != identification2->getCode() ;  
    }

    bool Transponder::areFriend(Kernel::Object* code1,Kernel::Object* code2)
    {
      if (!code1 || !code2)
        return false ;
      
      Transponder* identification1 = code1->getParent<Transponder>() ;
      Transponder* identification2 = code2->getParent<Transponder>() ;
      
      if (!identification1 || !identification2)
        return false ;
      
      return identification1->getCode() == identification2->getCode() ;  
    }
    
  }
}
