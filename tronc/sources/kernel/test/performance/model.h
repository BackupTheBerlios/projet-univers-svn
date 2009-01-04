/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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

#include <kernel/deduced_trait.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {
      namespace Performance
      {

        class A : public Trait
        {
        public:
          
          void change()
          {
            notify() ;
          }
          
        };

        class A1 : public A
        {
        };
        
        class A2 : public A
        {
        };
        
        class B : public Trait
        {
        };

        class C : public Trait
        {
        };

        class D : public Trait
        {
        };

        class E : public Trait
        {
        };

        class F : public Trait
        {
        };

        class G : public Trait
        {
        };

        class H : public Trait
        {
        };
        
        class AB : public DeducedTrait
        {
        };

        class ABCD : public DeducedTrait
        {
        };

        class EFGH : public DeducedTrait
        {
        };
        
        class AEG : public DeducedTrait
        {
        };
        
        class BCD : public DeducedTrait
        {
        };
        
      }
    }
  }
}
