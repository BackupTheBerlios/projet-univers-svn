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
#include <iostream>
#include <kernel/object.h>

#include <model/model.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/listener.h>
#include <model/player.h>
#include <model/plays.h>
#include <model/active.h>

#include <sound/test/sound_test_fixture.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      Kernel::Object* SoundTestFixture::createObserver(Kernel::Object* parent) const
      {
        Kernel::Object* observer = parent->createObject() ;
        observer->addTrait(new Model::Listener()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Model::Active()) ;
        Kernel::Link<Model::Plays>(observer,observer) ;

        return observer ;
      }
    }
  }
}

