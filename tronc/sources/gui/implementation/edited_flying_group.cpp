/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2011 Mathieu ROGER                                 *
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
#include <model/flying_group.h>
#include <model/edited.h>
#include <model/plays_in.h>
#include <model/player.h>
#include <gui/implementation/edited_team.h>
#include <gui/implementation/edited_flying_group.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {

      DeclareDeducedTrait(EditedFlyingGroup,
                          And(HasTrait(Model::FlyingGroup),
                              HasParent(HasTrait(EditedTeam)),
                              Or(IsRelated(Kernel::Inverse<Model::PlaysIn>,HasTrait(Model::Player)),
                                 Not(IsRelated(Kernel::Inverse<Model::PlaysIn>,HasTrait(Model::Player)))))) ;
    }
  }
}
