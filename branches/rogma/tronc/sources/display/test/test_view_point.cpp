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


#include <display/point_de_vue.h>
#include <display/implementation/ogre/univers.h>

#include <display/test/test_point_de_vue.h>


/// Registerment du test
CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Display::Test::TestViewPoint) ;


namespace ProjetUnivers {
  namespace Display {
    namespace Test {

      void TestViewPoint::testConstruction()
      {

        Kernel::Log::InternalMessage("Entering TestViewPoint::testConstruction") ;

        /// On construit un modèle
        Model::load("TestDemonstration") ;
        
        Kernel::Log::InternalMessage("TestViewPoint::testConstruction#1") ;
        
        Kernel::Association<Model::Object> 
                                observateur(Model::getObject("Observer")) ;

        Kernel::Log::InternalMessage("TestViewPoint::testConstruction#2") ;
        
        /// On en construit un point de vue
        Kernel::Composition<ViewPoint> pdv(ViewPoint::Construire(observateur)) ;

        Kernel::Log::InternalMessage("Leaving TestViewPoint::testConstruction") ;

        /// Vérification de la structure.
        Kernel::Association<Object> vueObserver(pdv->getViewObserver()) ;
        CPPUNIT_ASSERT_MESSAGE("no Observer view object",vueObserver) ;
        
        Kernel::Association<Implementation::Ogre::Univers> 
          vueUnivers(vueObserver->getParent<Implementation::Ogre::Univers>()) ;
        CPPUNIT_ASSERT_MESSAGE("no Univers view object",vueUnivers) ;
        
        Kernel::Association<Implementation::Ogre::ViewPoint> 
          ogrePointdeView(vueUnivers->getViewPoint()) ;
          
        CPPUNIT_ASSERT_MESSAGE("no specific view point",ogrePointdeView) ;
        
        pdv = NULL ;
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
