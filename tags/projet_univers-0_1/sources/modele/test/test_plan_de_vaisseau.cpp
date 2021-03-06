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

#include <modele/gestionnaire_objets.h>
#include <modele/plan_de_composant.h>
#include <modele/plan_d_etat_de_composant.h>
#include <modele/plan_de_point_d_attache.h>
#include <modele/plan_d_assemblage.h>
#include <modele/test/test_plan_de_vaisseau.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Modele::
                                Test::
                                TestPlanDeVaisseau) ;

namespace ProjetUnivers {

  namespace Modele {

    namespace Test {


      /*!
        On construit un exemple de vaisseau :
        
        
        coque1<- ->coque2<- ->coque3
      */
      Base::Association<PlanDAssemblage> TestPlanDeVaisseau::Construire()
      {
        Base::Composition<PlanDAssemblage> vaisseau ;
        Base::Composition<PlanDEtatDeComposant> etatCoque ;
        Base::Composition<PlanDeComposant> coque ;
        Base::Composition<PlanDePointDAttache> point11 ;
        Base::Composition<PlanDePointDAttache> point21 ;
        Base::Composition<PlanDePointDAttache> point22 ;


        // le r�sultat
        vaisseau = new PlanDAssemblage(Nom("Zarg")) ;
        
        // morceau 1
        coque = new PlanDeComposant(Nom("coque1")) ;
        vaisseau->Ajouter(Base::Association<PlanDeComposant>(coque)) ;
        etatCoque = new PlanDEtatDeComposant(coque) ;
        coque->DefinirEtat(100,etatCoque) ;
                
        point11 = new PlanDePointDAttache(coque) ;
        etatCoque->Ajouter(point11) ;

        GestionnaireObjets::Ajouter(coque.Liberer()) ; 
        GestionnaireObjets::Ajouter(etatCoque.Liberer()) ; 
        
        
        // morceau 2
        coque = new PlanDeComposant(Nom("coque2")) ;
        vaisseau->Ajouter(Base::Association<PlanDeComposant>(coque)) ;
        
        etatCoque = new PlanDEtatDeComposant(coque) ;
        coque->DefinirEtat(100,etatCoque) ;

        point21 = new PlanDePointDAttache(coque) ;
        etatCoque->Ajouter(point21) ;

        point22 = new PlanDePointDAttache(coque) ;
        etatCoque->Ajouter(point22) ;
        
        GestionnaireObjets::Ajouter(coque.Liberer()) ; 
        GestionnaireObjets::Ajouter(etatCoque.Liberer()) ; 

        // morceau 3
        coque = new PlanDeComposant(Nom("coque3")) ;
        vaisseau->Ajouter(Base::Association<PlanDeComposant>(coque)) ;

        etatCoque = new PlanDEtatDeComposant(coque) ;
        coque->DefinirEtat(100,etatCoque) ;

        Base::Composition<PlanDePointDAttache> point31 ;
        point31 = new PlanDePointDAttache(coque) ;
        etatCoque->Ajouter(point31) ;
        
        GestionnaireObjets::Ajouter(coque.Liberer()) ; 
        GestionnaireObjets::Ajouter(etatCoque.Liberer()) ; 

        // contraintes
        Base::Composition<PlanDeContrainte> contrainte ;
        contrainte = new PlanDeContrainte(point11,
                                          point21,
                                          PlanDeContrainte::Rigide) ;
        vaisseau->Ajouter(Base::Association<PlanDeContrainte>(contrainte)) ;
        GestionnaireObjets::Ajouter(contrainte.Liberer()) ; 

        contrainte = new PlanDeContrainte(point22,
                                          point31,
                                          PlanDeContrainte::Rigide) ;
        vaisseau->Ajouter(Base::Association<PlanDeContrainte>(contrainte)) ;
        GestionnaireObjets::Ajouter(contrainte.Liberer()) ; 
        
        GestionnaireObjets::Ajouter(point11.Liberer()) ; 
        GestionnaireObjets::Ajouter(point21.Liberer()) ; 
        GestionnaireObjets::Ajouter(point22.Liberer()) ; 
        GestionnaireObjets::Ajouter(point31.Liberer()) ; 
        
        Base::Association<PlanDAssemblage> resultat(vaisseau) ;
        GestionnaireObjets::Ajouter(vaisseau.Liberer()) ; 
        
        


        return resultat ;
      }

      void TestPlanDeVaisseau::testConstruction()
      {
        Base::Association<PlanDAssemblage> type(Construire()) ;
      }

      void TestPlanDeVaisseau::setUp() 
      {
      }
      
      void TestPlanDeVaisseau::tearDown() 
      {
      }

    }
  }
}

