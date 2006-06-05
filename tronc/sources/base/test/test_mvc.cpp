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

          
          
          /// Une vue sur 2 modèles
          class VuePersonne : public Vue<ModelePersonne>, public Vue<ModeleTete>
          {
          public:
  
            void Raffraichir()
            {
              personne_attribut = personne->AccesAttribut() ;
              tete_attribut = personne->AccesTete()->AccesAttribut() ;
              raffraichie = VRAI ;
            }
  
            VuePersonne(const Association<ModelePersonne>& _personne)
            : Vue<ModelePersonne>(_personne), 
              Vue<ModeleTete>(_personne->AccesTete()), personne(_personne),
              personne_attribut(_personne->AccesAttribut()),
              tete_attribut(_personne->AccesTete()->AccesAttribut())
            {
              this->AjouterMiseAJourElementaire(
                    boost::bind(&VuePersonne::Raffraichir,this)) ;
            }
            
            
            Entier AccesPersonneAttribut() const
            {
              return personne_attribut ;
            }
            
            Entier AccesTeteAttribut() const 
            {
              return tete_attribut ;
            }
            
            Booleen raffraichie ;
            
          private:
          
            Association<ModelePersonne> personne ;
            
            Entier personne_attribut ;
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
             this->AjouterMiseAJourElementaire(
                    boost::bind(&AffichagePersonne::Raffraichir,this)) ;            
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
          Composition<ModeleTete> tete(new ModeleTete()) ;
          Composition<ModelePersonne> CompPersonne(new ModelePersonne(tete.Liberer())) ;
          Association<ModelePersonne> personne(CompPersonne) ;
          
          
          // point de vue
          Composition<PointDeVue> pointDeVue(new PointDeVue()) ;          
          
          // Création des vues
          Composition<VuePersonne> vuePersonne(new VuePersonne(personne)) ;
          Association<VuePersonne> vue(vuePersonne) ;
          pointDeVue->Ajouter(vuePersonne.Liberer()) ;

          Composition<VuePersonne> vuePersonne2(new VuePersonne(personne)) ;
          Association<VuePersonne> vue3 = (vuePersonne2) ;
          pointDeVue->Ajouter(vuePersonne2.Liberer()) ;

          Composition<AffichagePersonne> affichagePersonne(new AffichagePersonne(personne)) ;
          Association<AffichagePersonne> vue2(affichagePersonne) ;
          pointDeVue->Ajouter(affichagePersonne.Liberer()) ;
          
          vue->raffraichie = FAUX ;
          vue2->raffraichie = FAUX ;
          vue3->raffraichie = FAUX ;
          
          // Utilisation
          
          // changement de personne
          personne->ChangerAttribut(10) ;
          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vue->AccesPersonneAttribut() == 10) ;
          CPPUNIT_ASSERT(vue->AccesTeteAttribut() == 0) ;
          CPPUNIT_ASSERT(vue->raffraichie == VRAI) ;
          CPPUNIT_ASSERT(vue2->raffraichie == VRAI) ;
          CPPUNIT_ASSERT(vue3->raffraichie == VRAI) ;
          
          vue->raffraichie = FAUX ;
          vue2->raffraichie = FAUX ;
          vue3->raffraichie = FAUX ;

          // aucun changement du modèle
          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vue->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vue2->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vue3->raffraichie == FAUX) ;

          // changement de tete
          personne->AccesTete()->ChangerAttribut(20) ;

          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vue->AccesPersonneAttribut() == 10) ;
          CPPUNIT_ASSERT(vue->AccesTeteAttribut() == 20) ;
          CPPUNIT_ASSERT(vue->raffraichie == VRAI) ;
          CPPUNIT_ASSERT(vue2->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vue3->raffraichie == VRAI) ;

          // Changement des 2
          personne->ChangerAttribut(100) ;
          personne->AccesTete()->ChangerAttribut(200) ;
          pointDeVue->Raffraichir() ;
          CPPUNIT_ASSERT(vue->AccesPersonneAttribut() == 100) ;
          CPPUNIT_ASSERT(vue->AccesTeteAttribut() == 200) ;
          CPPUNIT_ASSERT(vue2->AccesPersonneAttribut() == 100) ;
          CPPUNIT_ASSERT(vue3->AccesPersonneAttribut() == 100) ;
          
          
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
