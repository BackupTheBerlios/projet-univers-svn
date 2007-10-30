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
#include <sound/sound.h>
#include <sound/test/test_openal_init.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestOpenALInit) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestOpenALInit::basicTest()
      {
        /*!
          - just init sound module and show the EFX version and the number of effect slot
        */
 
        Sound::init() ;
        
        ALCdevice* device;
        ALCcontext* contexte;
        ALint auxSlotNumber;
        ALint minVersion;
        ALint maxVersion;
        
        contexte = alcGetCurrentContext();
        device = alcGetContextsDevice(contexte);
        alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &auxSlotNumber);
        alcGetIntegerv(device, ALC_EFX_MINOR_VERSION, 1, &minVersion);
        alcGetIntegerv(device, ALC_EFX_MAJOR_VERSION, 1, &maxVersion);   
        printf("Your system can support :\n -%d aux effect slot\n -an EFX version between %d and %d",auxSlotNumber, minVersion, maxVersion);
      }

      void TestOpenALInit::setUp() 
      {
      }
      
      void TestOpenALInit::tearDown() 
      {
      }
      

    }
  }
}

