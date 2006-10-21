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
CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Affichage::Test::TestPointDeVue) ;


namespace ProjetUnivers {
  namespace Affichage {
    namespace Test {

      void TestPointDeVue::testConstruction()
      {

        Base::Traceur::MessageInterne("Entering TestPointDeVue::testConstruction") ;

        /// On construit un modèle
        Modele::Charger("TestDemonstration") ;
        
        Base::Traceur::MessageInterne("TestPointDeVue::testConstruction#1") ;
        
        Base::Association<Modele::Objet> 
                                observateur(Modele::AccesObjet("Observateur")) ;

        Base::Traceur::MessageInterne("TestPointDeVue::testConstruction#2") ;
        
        /// On en construit un point de vue
        Base::Composition<PointDeVue> pdv(PointDeVue::Construire(observateur)) ;

        Base::Traceur::MessageInterne("Leaving TestPointDeVue::testConstruction") ;

        /// Vérification de la structure.
        Base::Association<Objet> vueObservateur(pdv->AccesVueObservateur()) ;
        CPPUNIT_ASSERT_MESSAGE("no Observateur view object",vueObservateur) ;
        
        Base::Association<Implantation::Ogre::Univers> 
          vueUnivers(vueObservateur->AccesParent<Implantation::Ogre::Univers>()) ;
        CPPUNIT_ASSERT_MESSAGE("no Univers view object",vueUnivers) ;
        
        Base::Association<Implantation::Ogre::PointDeVue> 
          ogrePointdeVue(vueUnivers->AccesPointDeVue()) ;
          
        CPPUNIT_ASSERT_MESSAGE("no specific view point",ogrePointdeVue) ;
        
        pdv = NULL ;
      }
      
      void TestPointDeVue::setUp()
      {
        
      }
      
      void TestPointDeVue::tearDown()
      {
        
      }
      

    }
  }
}
