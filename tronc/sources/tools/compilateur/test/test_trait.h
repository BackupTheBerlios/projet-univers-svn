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
#ifndef PU_TOOLS_COMPILER_TEST_TEST_TRAIT_H_
#define PU_TOOLS_COMPILER_TEST_TEST_TRAIT_H_

#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Tools {
    namespace Compiler {
      namespace Test {
      
        /// Test trait.
        class TestTrait : public Kernel::Trait
        {
        public:
    
          /// Constructor.
          TestTrait(const int& value) ;
          
        private:
    
          int m_value ;
          
          
        };
      }    
    }
  }
}

#endif /*PU_TOOLS_COMPILER_TEST_TEST_TRAIT_H_*/
