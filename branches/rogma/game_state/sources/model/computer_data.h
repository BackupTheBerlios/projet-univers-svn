/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_COMPUTER_DATA_H_
#define PU_MODEL_COMPUTER_DATA_H_

#include <kernel/trait.h>
#include <kernel/object_reference.h>
#include <kernel/object.h>

namespace ProjetUnivers {
  namespace Model {

    /// Trait for objects that are computer data.
    /*!
      In game data that are stored in in game computers.
    */
    class ComputerData : public Kernel::Trait
    {
    public:
      
      /// Constructs.
      ComputerData(Kernel::Object* computer) ;
    
      //: Access to computer
      Kernel::Object* getComputer() const ;
      
    private:
      
      /// The computer holding the data
      Kernel::ObjectReference m_computer ;
    };

  }

}

#endif
