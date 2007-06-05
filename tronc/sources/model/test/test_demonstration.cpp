/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>

#include <model/model.h>
#include <model/stellar_system.h>
#include <model/universe.h>
#include <model/observer.h>
#include <model/positionned.h>
#include <model/physical_world.h>

#include <model/test/test_demonstration.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestDemonstration) ;

using namespace ProjetUnivers::Kernel ;

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
        Model::init() ;
        Model::load("TestDemonstration") ;

        Object* observer(Model::getObject("Observer")) ;
        CPPUNIT_ASSERT_MESSAGE("no Observer object",observer) ;
        
        InternalMessage(std::string("sizeof(Object)=") 
                                        + toString(sizeof(Object))) ; 
        
        CPPUNIT_ASSERT_MESSAGE("Observer has no Observer trait",
                               observer->getTrait<Observer>()) ;

        InternalMessage("Testing Observer has Positionned trait") ;
        
        CPPUNIT_ASSERT_MESSAGE("Observer has no Positionned trait",
                               observer->getTrait<Positionned>()) ;

        CPPUNIT_ASSERT_MESSAGE("Observer has Universe trait",
                               observer->getTrait<Universe>()==NULL) ;


        InternalMessage("Testing Observer has Universe ancestor") ;
        
        Universe* universe(observer->getParent<Universe>()) ;
        CPPUNIT_ASSERT_MESSAGE("Observer has no Universe ancestor",
                               universe) ;


        InternalMessage("Testing Universe has object") ;
        Object* universe_object = universe->getObject() ;
        
        CPPUNIT_ASSERT_MESSAGE("universe has no object",
                               universe_object) ;


        InternalMessage("Testing Universe has Universe trait") ;
                               
        CPPUNIT_ASSERT_MESSAGE("universe has no Universe trait",
                               universe->getObject()->getTrait<Universe>()) ;

        InternalMessage("Testing Observer has StellarSystem ancestor") ;

        StellarSystem* system(observer->getParent<StellarSystem>()) ;
        CPPUNIT_ASSERT_MESSAGE("Observer has no StellarSystem ancestor",
                               system) ;
        InternalMessage(std::string("sizeof(StellarSystem)=") 
                                        + toString(sizeof(StellarSystem))) ; 
        InternalMessage(std::string("sizeof(Positionned)=") 
                                        + toString(sizeof(Positionned))) ; 

        CPPUNIT_ASSERT_MESSAGE("Observer has no Positionned root",
                               observer->getRoot<Positionned>()) ;

        CPPUNIT_ASSERT(observer->getParent<PhysicalWorld>()) ;
        Model::close() ;
        
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

