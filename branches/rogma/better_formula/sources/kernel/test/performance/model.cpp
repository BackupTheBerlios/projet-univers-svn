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
#include <kernel/test/performance/model.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {
      namespace Performance
      {
        DeclareDeducedTrait(AB,And(HasTrait(A),HasTrait(B))) ;
        DeclareDeducedTrait(ABCD,And(HasTrait(A),HasTrait(B),HasTrait(C),HasTrait(D))) ;
        DeclareDeducedTrait(EFGH,And(HasTrait(E),HasTrait(F),HasTrait(G),HasTrait(H))) ;
        DeclareDeducedTrait(AEG,And(HasTrait(A),HasTrait(E),HasTrait(G))) ;
        DeclareDeducedTrait(BCD,And(HasTrait(B),HasTrait(C),HasTrait(D))) ;
      }
    }
  }
}
