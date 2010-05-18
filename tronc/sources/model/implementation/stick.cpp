/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <kernel/log.h>
#include <model/stick.h>

namespace ProjetUnivers
{
  namespace Model
  {

    std::string Stick::Yaw = "Yaw" ;
    std::string Stick::Pitch = "Pitch" ;
    std::string Stick::Roll = "Roll" ;

    RegisterTrait(Stick) ;

    Stick::Stick()
    : Oriented()
    {}

    Kernel::Trait* Stick::read(Kernel::Reader* reader)
    {
      Stick* result = new Stick() ;

      while (!reader->isEndNode() && reader->processNode())
      {}

      reader->processNode() ;

      return result ;
    }

    const Orientation& Stick::getOrientation() const
    {
      updateOrientation() ;
      return Oriented::getOrientation() ;
    }

    RegisterAxis(Stick::Yaw,"Piloting",Stick,setX) ;
    RegisterAxis(Stick::Pitch,"Piloting",Stick,setY) ;
    RegisterAxis(Stick::Roll,"Piloting",Stick,setZ) ;

  }
}
