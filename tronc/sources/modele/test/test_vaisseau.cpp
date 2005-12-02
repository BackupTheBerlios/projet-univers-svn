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

#include <base/composition.h>

#include <modele/composant.h>
#include <modele/vaisseau.h>
#include <modele/test/test_vaisseau.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Modele::
                                Test::
                                TestVaisseau) ;

using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {

  namespace Modele {

    namespace Test {


      Vaisseau* TestVaisseau::Construire()
      {

        Base::Composition<Vaisseau> resultat ;
        
        /// Les composants du vaisseau Zarg
        
        Composition<Objet> aileGauche(new Composant(Composant::Coque)) ;
        Composition<Objet> aileDroite(new Composant(Composant::Coque)) ;
        Composition<Objet> fuselage(new Composant(Composant::Coque)) ;
        
        Composition<Contrainte> contrainte1(new ContrainteFixe(
                                                  aileGauche,
                                                  fuselage)) ;

        Composition<Contrainte> contrainte2(new ContrainteFixe(
                                                  aileDroite,
                                                  fuselage)) ;
        
        /// Un assemblage
        
        Composition<Assemblage> assemblage(new Assemblage()) ;
        
        assemblage->Ajouter(aileGauche) ;
        assemblage->Ajouter(aileDroite) ;
        assemblage->Ajouter(fuselage) ;

        assemblage->Ajouter(contrainte1) ;
        assemblage->Ajouter(contrainte2) ;

        
        /// Un vaisseau
        
        Composition<Vaisseau> vaisseau(new Vaisseau(assemblage)) ;
        
        
        
        /// Enrigstrement des objets
        
        GestionnaireObjets::Ajouter(aileGauche.Liberer()) ;
        GestionnaireObjets::Ajouter(aileDroite.Liberer()) ;
        GestionnaireObjets::Ajouter(fuselage.Liberer()) ;
        GestionnaireObjets::Ajouter(contrainte1.Liberer()) ;
        GestionnaireObjets::Ajouter(contrainte2.Liberer()) ;
        GestionnaireObjets::Ajouter(assemblage.Liberer()) ;
        GestionnaireObjets::Ajouter(vaisseau.Liberer()) ;
        
        
        
        

        return NULL ;
      }

      void TestVaisseau::testConstruction()
      {
        Base::Composition<Vaisseau> type(TestVaisseau::Construire()) ;
      }

      void TestVaisseau::setUp() 
      {
      }
      
      void TestVaisseau::tearDown() 
      {
      }

    }
  }
}

