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
#pragma once

#include <kernel/trait.h>
#include <kernel/object_reference.h>
#include <kernel/reader.h>

#include <model/oriented.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Test
    {
      class TestLoad ;
    }
    
    class GuidanceSystem ;

    /// Connect a stick to a guidance controler. 
    void connectStickControler(Kernel::Object* stick,
                               Kernel::Object* controler) ;

    /// Connect an guidance controler to a guidance system. 
    void connectControlerGuidanceSystem(Kernel::Object* controler,
                                        Kernel::Object* system) ;
    
    /// Computer part that control orientation.
    /*!
      @see GuidanceSystem 
    */
    class GuidanceControler : public Kernel::Trait
    {
    public:

      /// Constructor.
      GuidanceControler() ;

      /// Read a GuidanceControler trait.
      /*!
        stored as 
        @code
          <GuidanceControler>
            [<ObjectReference id=".." [name=stick]/>] 
          </GuidanceControler>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to stick orientation.
      Orientation getStickOrientation() const ;
      
    private:
      
      /// the stick 
      /*!
        it is a normalised orientation of a stick.
      */ 
      Kernel::ObjectReference  m_stick ;
      
      friend void connectStickControler(Kernel::Object* stick,
                                        Kernel::Object* controler) ;
      
      friend class ProjetUnivers::Model::Test::TestLoad ;
    };
    
    
  }
}
