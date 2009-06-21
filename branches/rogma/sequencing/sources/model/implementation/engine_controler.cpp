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
#include <kernel/object.h>
#include <model/engine.h>
#include <model/engine_controler.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(EngineControler) ;
    
    void connectThrottleControler(Kernel::Object* throttle,
                                  Kernel::Object* controler)
    {
      EngineControler* temp = controler->getTrait<EngineControler>() ;
      if (temp)
      {
        temp->m_throttle = throttle ;
      }
    }

    void connectControlerEngine(Kernel::Object* controler,
                                Kernel::Object* engine)
    {
      Engine* temp = engine->getTrait<Engine>() ;
      if (temp)
      {
        temp->m_controler = controler ;
      }
    }
    
    EngineControler::EngineControler()
    : Kernel::Trait(),
      m_throttle()
    {}

    Kernel::Trait* EngineControler::read(Kernel::Reader* reader)
    {
      EngineControler* result = new EngineControler() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "ObjectReference")
        {
          result->m_throttle = Kernel::ObjectReference::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;

      return result ;
    }

    int EngineControler::getPowerPercentage() const
    {
      int percentage = 0 ;

      /// get throttle pitch
      if (m_throttle && m_throttle->getTrait<Oriented>())
      {
        float pitch 
          = m_throttle->getTrait<Oriented>()->getOrientation().getQuaternion().getPitch().valueDegrees() ;
        
        percentage = (int)(pitch/0.9) ;
      }
      
      return percentage ;      
    }
    
  }
}
