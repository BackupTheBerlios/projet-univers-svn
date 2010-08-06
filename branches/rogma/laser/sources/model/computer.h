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
#pragma once
#include <memory>

#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/reader.h>
#include <model/position.h>

namespace ProjetUnivers
{
  namespace Model
  {

      
    /// For objects that are computer.
    /*!
      A computer has its memory, that is represented by objects.
      These objects may be just like "real" objects. They may be Positioned, 
      Massive, etc...  
    */
    class Computer : public Kernel::Trait
    {
    public:

      /// Constructs.
      Computer() ;
      
      /// Read a Computer trait.
      /*!
        stored as 
        @code
          <Computer/>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to memory.
      Kernel::Model* getMemoryModel() const ;

      /// Gives the position of a detection data relative to another object.
      Position getDataPosition(Kernel::Object* data,
                               Kernel::Object* relative_to) const ;
      
      /// Return the detected objects.
      std::set<Kernel::Object*> getDetectedObjects() const ;

    private:
      
      /// The set of objects in memory.
      std::auto_ptr<Kernel::Model> m_memory ;
      
    };

  }

}
