/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/selection.h>
#include <model/selected.h>

namespace ProjetUnivers
{
  namespace Model
  {

    Selected::Selected()
    {}

    bool Selected::isSelected(Kernel::Object* by) const
    {
      return Kernel::Relation::areLinked<Selection>(by,getObject()) ;
    }

    void Selected::select(Kernel::Object* by)
    {
      Kernel::Link<Selection>(by,getObject()) ;
      notify() ;
    }

    void Selected::unSelect(Kernel::Object* by)
    {
      Kernel::UnLink<Selection>(by,getObject()) ;
      notify() ;
    }

    bool Selected::isSelected() const
    {
      return Kernel::Relation::getLinked<Kernel::Inverse<Selection> >(getObject()).size() != 0 ;
    }
  }
}
