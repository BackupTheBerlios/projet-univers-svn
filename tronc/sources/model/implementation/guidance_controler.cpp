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
#include <model/guidance_controler.h>
#include <model/guidance_system.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(GuidanceControler) ;
    
    void connectStickControler(Kernel::Object* stick,
                               Kernel::Object* controler)
    {
      GuidanceControler* temp = controler->getTrait<GuidanceControler>() ;
      if (temp)
      {
        temp->m_stick = stick ;
      }
    }

    /// Connect an guidance controler to a guidance system. 
    void connectControlerGuidanceSystem(Kernel::Object* controler,
                                        Kernel::Object* system)
    {
      GuidanceSystem* temp = system->getTrait<GuidanceSystem>() ;
      if (temp)
      {
        temp->m_control = controler ;
      }
    }
    
    GuidanceControler::GuidanceControler()
    : Kernel::Trait(),
      m_stick()
    {}

    Kernel::Trait* GuidanceControler::read(Kernel::Reader* reader)
    {
      GuidanceControler* result = new GuidanceControler() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "ObjectReference")
        {
          result->m_stick = Kernel::ObjectReference::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;
      
      return result ;
    }

    Orientation GuidanceControler::getStickOrientation() const
    {
      // normal behaviour
      /*!
        more complex behaviour including malfunctions could return a 
        any orientation, e.g. a random one
      */  
      return m_stick->getOrientation() ;
    }
    
  }
}
