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

#include <base/traceur.h>

#include <modele/modele.h>


#include <affichage/point_de_vue.h>
#include <affichage/implantation/ogre/univers.h>

#include <affichage/test/test_point_de_vue.h>


/// Enregistrement du test
CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Display::Test::TestViewPoint) ;


namespace ProjetUnivers {
  namespace Display {
    namespace Test {

      void TestViewPoint::testConstruction()
      {

        Base::Traceur::MessageInterne("Entering TestViewPoint::testConstruction") ;

        /// On construit un modèle
        Model::load("TestDemonstration") ;
        
        Base::Traceur::MessageInterne("TestViewPoint::testConstruction#1") ;
        
        Base::Association<Model::Object> 
                                observateur(Model::AccesObject("Observateur")) ;

        Base::Traceur::MessageInterne("TestViewPoint::testConstruction#2") ;
        
        /// On en construit un point de vue
        Base::Composition<ViewPoint> pdv(ViewPoint::Construire(observateur)) ;

        Base::Traceur::MessageInterne("Leaving TestViewPoint::testConstruction") ;

        /// Vérification de la structure.
        Base::Association<Object> vueObservateur(pdv->AccesVueObservateur()) ;
        CPPUNIT_ASSERT_MESSAGE("no Observateur view object",vueObservateur) ;
        
        Base::Association<Implantation::Ogre::Univers> 
          vueUnivers(vueObservateur->AccesParent<Implantation::Ogre::Univers>()) ;
        CPPUNIT_ASSERT_MESSAGE("no Univers view object",vueUnivers) ;
        
        Base::Association<Implantation::Ogre::ViewPoint> 
          ogrePointdeVue(vueUnivers->AccesViewPoint()) ;
          
        CPPUNIT_ASSERT_MESSAGE("no specific view point",ogrePointdeVue) ;
        
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
