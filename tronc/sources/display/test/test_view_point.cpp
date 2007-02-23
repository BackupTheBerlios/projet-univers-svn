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

#include <model/model.h>


#include <display/view_point.h>
#include <display/implementation/ogre/universe.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/observer.h>

#include <display/test/test_view_point.h>


/// Registerment du test
CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Display::Test::TestViewPoint) ;


namespace ProjetUnivers {
  namespace Display {
    namespace Test {

      void TestViewPoint::testBuild()
      {
        Model::init() ;
        Kernel::Log::InternalMessage("Entering TestViewPoint::testConstruction") ;
        /// On construit un modèle
        Model::load("TestDemonstration") ;
        Model::Object* model_observer(Model::getObject("Observer")) ;

        Kernel::Log::InternalMessage("TestViewPoint building viewpoint") ;
        /// On en construit un point de vue
        std::auto_ptr<ViewPoint> pdv(ViewPoint::build(model_observer)) ;

        Kernel::Log::InternalMessage("TestViewPoint getting observer view") ;
        /// Vérification de la structure.
        Object* observer(pdv->getObserverView()) ;
        CPPUNIT_ASSERT_MESSAGE("no Observer view object",observer) ;

        Kernel::Log::InternalMessage("TestViewPoint getting positionned trait") ;

        Implementation::Ogre::Positionned* 
          observer_positionned = observer->getTrait<Implementation::Ogre::Positionned>() ;
        CPPUNIT_ASSERT_MESSAGE("no Positionned trait for observer",observer_positionned) ;

        Kernel::Log::InternalMessage("TestViewPoint getting observer trait") ;
        
        Implementation::Ogre::Observer* 
          observer_observer = observer->getTrait<Implementation::Ogre::Observer>() ;
        CPPUNIT_ASSERT_MESSAGE("no Observer trait for observer",observer_observer) ;

        Kernel::Log::InternalMessage("TestViewPoint getting Universe view") ;
        Implementation::Ogre::Universe* 
          vueUnivers(observer->getParent<Implementation::Ogre::Universe>()) ;
        CPPUNIT_ASSERT_MESSAGE("no Univers view object",vueUnivers) ;

        Kernel::Log::InformationMessage(vueUnivers->getObject()->print().c_str()) ;


        Kernel::Log::InternalMessage("TestViewPoint getting ogre viewpoint") ;
        Implementation::Ogre::ViewPoint* 
          ogrePointdeView(vueUnivers->getViewPoint()) ;
        CPPUNIT_ASSERT_MESSAGE("no specific view point",ogrePointdeView) ;

        
        Kernel::Log::InternalMessage("Leaving TestViewPoint::testConstruction") ;
        
      }
      
      void TestViewPoint::setUp()
      {
        
      }
      
      void TestViewPoint::tearDown()
      {
        
      }
      

    }
  }
}
