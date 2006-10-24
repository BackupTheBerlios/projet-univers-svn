/***************************************************************************
 *   Copyright (C) 2004 by Projet Univers                                  *
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

#include <iostream>
using namespace std ;

#include <base/test/test_mvc.h>

#include <base/implantation/liste_association.h>
#include <base/implantation/iterateur_liste_association.h>

#include <base/modele.h>
#include <base/vue.h>
#include <base/point_de_vue.h>


CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Base::Implantation::Test::TestMVC) ;

namespace ProjetUnivers {
  
  namespace Base {
    
    namespace Implantation {
      
      namespace Test {

        /// un espace de nom local
        namespace
        {
          class ModeleTete ;
          
          
          class ModelePersonne : public Modele
          {
          public:
          
            ModelePersonne(ModeleTete* _tete)
            : Modele(), attribut(0), tete(_tete)
            {}
          
            void ChangerAttribut(const Entier& nouvelleValeur) 
            {
              attribut = nouvelleValeur ;
              Notifier() ;
            }  
            
            Entier AccesAttribut() const
            {
              return attribut ;
            }
            
            Association<ModeleTete> AccesTete() const
            {
              return tete ;
            }
            
          private:
          
            /// un attribut qui va etre modifié
            Entier attribut ;
            
            Composition<ModeleTete> tete ; 
            
          };

          class ModeleTete : public Modele
          {
          public:
          
            ModeleTete()
            : Modele(), attribut(0)
            {}
          
            void ChangerAttribut(const Entier& nouvelleValeur) 
            {
              attribut = nouvelleValeur ;
              Notifier() ;
            }  
            
            Entier AccesAttribut() const
            {
              return attribut ;
            }
            
          private:
          
            /// un attribut qui va etre modifié
            Entier attribut ;
            
          };

          
          
          /// Une vue sur une tete
          class VueTete : public Vue<ModeleTete>
          {
          public:
  
            void Raffraichir()
            {
              tete_attribut = Vue<ModeleTete>::observe->AccesAttribut() ;
              raffraichie = VRAI ;
            }
  
            VueTete(const Association<ModeleTete>& _tete)
            : Vue<ModeleTete>(_tete),
              tete_attribut(_tete->AccesAttribut())
            {
            }
            
            
            
            Entier AccesTeteAttribut() const 
            {
              return tete_attribut ;
            }
            
            Booleen raffraichie ;
            
          private:
            
            Entier tete_attribut ;
            
          };
          
          /// Une vue sur personne
          class AffichagePersonne : public Vue<ModelePersonne>
          {
          public:
  
            void Raffraichir()
            {
              personne_attribut = Vue<ModelePersonne>::observe->AccesAttribut() ;
              raffraichie = VRAI ;
            }
  
            AffichagePersonne(const Association<ModelePersonne>& _personne)
            : Vue<ModelePersonne>(_personne), 
              personne_attribut(_personne->AccesAttribut())
            {
            }
            
            
            Entier AccesPersonneAttribut() const
            {
              return personne_attribut ;
            }
            
            Booleen raffraichie ;
            
          private:
            Entier personne_attribut ;
          };
          
          
        }


        void TestMVC::TesteObservation()
        {
          
          
          try {
          // Création du modèle
          Composition<ModeleTete> compTete(new ModeleTete()) ;
          Association<ModeleTete> tete(compTete) ;
          Composition<ModelePersonne> CompPersonne(new ModelePersonne(compTete.Liberer())) ;
          Association<ModelePersonne> personne(CompPersonne) ;
          
          
          // point de vue
          Composition<PointDeVue> pointDeVue(new PointDeVue()) ;          
          
          // Création des vues
          Composition<VueTete> compVueTete(new VueTete(tete)) ;
          Association<VueTete> vueTete(compVueTete) ;
          pointDeVue->Ajouter(compVueTete.Liberer()) ;


          Composition<AffichagePersonne> compAffichagePersonne(new AffichagePersonne(personne)) ;
          Association<AffichagePersonne> vuePersonne(compAffichagePersonne) ;
          pointDeVue->Ajouter(compAffichagePersonne.Liberer()) ;
          
          vueTete->raffraichie = FAUX ;
          vuePersonne->raffraichie = FAUX ;
          
          // Utilisation
          
          // changement de personne
          personne->ChangerAttribut(10) ;
          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vueTete->AccesTeteAttribut() == 0) ;
          CPPUNIT_ASSERT(vueTete->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie == VRAI) ;
          
          vueTete->raffraichie = FAUX ;
          vuePersonne->raffraichie = FAUX ;

          // aucun changement du modèle
          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vueTete->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie == FAUX) ;

          // changement de tete
          personne->AccesTete()->ChangerAttribut(20) ;

          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vueTete->AccesTeteAttribut() == 20) ;
          CPPUNIT_ASSERT(vueTete->raffraichie == VRAI) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie == FAUX) ;

          // Changement des 2
          personne->ChangerAttribut(100) ;
          personne->AccesTete()->ChangerAttribut(200) ;
          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vueTete->AccesTeteAttribut() == 200) ;
          CPPUNIT_ASSERT(vuePersonne->AccesPersonneAttribut() == 100) ;
          
          
          }
          
          catch(Exception& e)
          {
            std::cout << "TestMVC " << e.Message() << std::endl ;
          }
          
        }


        void TestMVC::setUp()
        {
        }
  
        void TestMVC::tearDown()
        {
        }

 
       
       
      }
    }
  }
}
