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


#include <modele/assemblage.h>
#include <modele/contrainte.h>
#include <modele/composant.h>
#include <modele/gestionnaire_objets.h>
#include <modele/plan_d_assemblage.h>
#include <modele/vaisseau.h>

#include <modele/test/test_plan_de_vaisseau.h>
#include <modele/test/test_vaisseau.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Modele::
                                Test::
                                TestVaisseau) ;

using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {

  namespace Modele {

    namespace Test {


      Association<Vaisseau> TestVaisseau::Construire()
      {

        Association<PlanDAssemblage> planZarg(TestPlanDeVaisseau::Construire()) ;


        Composition<Vaisseau> vaisseau(new Vaisseau(Nom("Zarg 01"),planZarg)) ; 
        Association<Vaisseau> resultat(vaisseau) ;
        GestionnaireObjets::Ajouter(vaisseau.Liberer()) ;
        
        return resultat ;
      }

      void TestVaisseau::testConstruction()
      {
        Base::Association<Vaisseau> vaisseau(TestVaisseau::Construire()) ;
        
        std::cout << GestionnaireObjets::AfficherObjets() << std::endl ;
        
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

