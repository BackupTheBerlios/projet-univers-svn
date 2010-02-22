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
#pragma once

#include <model/computer_data.h>

namespace ProjetUnivers
{
  namespace Model
  {
    
    /// For objects that represent where to shoot.
    /*!
      For a targeted element, a computer object is built that represent where 
      to shoot. If the ship is aimed at this positioned object then shooting 
      will touch the targeted object provided it does not change direction and 
      speed. 
    */
    class IdealTarget : public ComputerData
    {
    public:

      /// Constructor.
      IdealTarget(Kernel::Object* computer) ;
    
    };
    
  }
}
