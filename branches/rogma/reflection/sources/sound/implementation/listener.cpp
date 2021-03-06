/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Morgan GRIGNARD                                 *
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
#include <kernel/deduced_trait.h>
#include <model/listener.h>
#include <model/mobile.h>
#include <model/oriented.h>
#include <model/positioned.h>

#include <sound/implementation/listener.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {

      /*!
        having Or(X,Not(X)) is not a bug
        it is always true but the deduced trait will be updated when X is
      */
      DeclareDeducedTrait(Listener,
                          And(Or(HasParent(HasTrait(Model::Mobile)),
                                 Not(HasParent(HasTrait(Model::Mobile)))),
                              HasTrait(Model::RecursivelyPositioned),
                              HasTrait(Model::Listener))) ;

    }
  } 
}
