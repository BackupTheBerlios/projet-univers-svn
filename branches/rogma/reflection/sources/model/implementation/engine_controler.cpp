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
#include <kernel/object.h>
#include <kernel/relation.h>
#include <model/engine.h>
#include <model/control_connection.h>
#include <model/engine_controler.h>

namespace ProjetUnivers
{
  namespace Model
  {

    RegisterTrait(EngineControler) ;

    void connectThrottleControler(Kernel::Object* throttle,
                                  Kernel::Object* controler)
    {
      EngineControler* temp = controler->getTrait<EngineControler> () ;
      if (temp)
      {
        Kernel::Link<ControlConnection>(throttle,controler) ;
      }
    }

    void connectControlerEngine(Kernel::Object* controler,
                                Kernel::Object* engine)
    {
      Engine* temp = engine->getTrait<Engine> () ;
      if (temp)
      {
        Kernel::Link<ControlConnection>(controler,engine) ;
      }
    }

    Kernel::Trait* EngineControler::read(Kernel::Reader* reader)
    {
      EngineControler* result = new EngineControler() ;

      while (!reader->isEndNode() && reader->processNode())
      {
        Trait::read(reader) ;
      }
      reader->processNode() ;

      return result ;
    }

    int EngineControler::getPowerPercentage() const
    {
      int percentage = 0 ;

      Kernel::Object* throttle = Kernel::Relation::getUniqueLinked<Kernel::Inverse<ControlConnection> >(getObject()) ;

      /// get throttle pitch
      if (throttle && throttle->getTrait<Oriented> ())
      {
        float
            pitch =
                throttle->getTrait<Oriented> ()->getOrientation().getQuaternion().getPitch().valueDegrees() ;

        percentage = (int) (pitch / 0.9) ;
      }

      return percentage ;
    }

  }
}
