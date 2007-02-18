/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <model/model.h>
#include <model/object.h>
#include <model/stellar_system.h>
#include <model/universe.h>

#include <model/test/test_demonstration.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestDemonstration) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      /*!
        @todo
          Ne pas passer par le chargement de TestDemonstration mais 
          faire un copier coller de son contenu dans le setup + une destruction 
          dans le tearDown puis executer les commandes d'accès diverses
      */
      void TestDemonstration::testBuild()
      {
        Model::load("TestDemonstration") ;

        Object* observer(Model::getObject("Observer")) ;
        CPPUNIT_ASSERT_MESSAGE("pas d'observateur",observer) ;
        
        Universe* universe(observer->getParent<Universe>()) ;
        CPPUNIT_ASSERT_MESSAGE("pas d'univers pour l'observateur",universe) ;

        StellarSystem* system(observer->getParent<StellarSystem>()) ;
        CPPUNIT_ASSERT_MESSAGE("pas de systeme stellaire pour l'observateur",system) ;
        
      }

      void TestDemonstration::setUp() 
      {
      }
      
      void TestDemonstration::tearDown() 
      {
      }

    }
  }
}

