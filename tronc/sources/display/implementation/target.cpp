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
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/head_up_display.h>
#include <model/selection.h>
#include <display/implementation/observer.h>
#include <display/implementation/target.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
          
      DeclareDeducedRelation(
          Target,
          Model::Selection,
          And(IsFrom(And(HasChild(HasTrait(Model::HeadUpDisplay)),
                         HasChild(And(HasTrait(Implementation::Observer),
                                      HasTrait(Model::RecursivelyPositionned),
                                      HasTrait(Model::RecursivelyOriented))))),
              IsTo(HasTrait(Model::RecursivelyPositionned)))) ;
    }
  }
}
