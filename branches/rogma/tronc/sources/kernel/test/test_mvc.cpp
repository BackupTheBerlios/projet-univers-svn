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

#include <kernel/test/test_mvc.h>

#include <kernel/implementation/liste_association.h>
#include <kernel/implementation/iterateur_liste_association.h>

#include <kernel/model.h>
#include <kernel/vue.h>
#include <kernel/point_de_vue.h>


CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Implementation::Test::TestMVC) ;

namespace ProjetUnivers {
  
  namespace Kernel {
    
    namespace Implementation {
      
      namespace Test {

        /// un espace de nom local
        namespace
        {
          class ModelTete ;
          
          
          class ModelPersonne : public Model
          {
          public:
          
            ModelPersonne(ModelTete* _tete)
            : Model(), attribut(0), tete(_tete)
            {}
          
            void ChangerAttribut(const Entier& nouvelleValeur) 
            {
              attribut = nouvelleValeur ;
              notify() ;
            }  
            
            Entier getAttribut() const
            {
              return attribut ;
            }
            
            Association<ModelTete> getTete() const
            {
              return tete ;
            }
            
          private:
          
            /// un attribut qui va etre modifié
            Entier attribut ;
            
            Composition<ModelTete> tete ; 
            
          };

          class ModelTete : public Model
          {
          public:
          
            ModelTete()
            : Model(), attribut(0)
            {}
          
            void ChangerAttribut(const Entier& nouvelleValeur) 
            {
              attribut = nouvelleValeur ;
              notify() ;
            }  
            
            Entier getAttribut() const
            {
              return attribut ;
            }
            
          private:
          
            /// un attribut qui va etre modifié
            Entier attribut ;
            
          };

          
          
          /// Une vue sur une tete
          class ViewTete : public View<ModelTete>
          {
          public:
  
            void update(const Event& _evenement)
            {
              tete_attribut = View<ModelTete>::observe->getAttribut() ;
              raffraichie = VRAI ;
            }
  
            ViewTete(const Association<ModelTete>& _tete)
            : View<ModelTete>(_tete),
              tete_attribut(_tete->getAttribut())
            {
            }
            
            /// Suppression.
            virtual void Supprimer()
            {
              
            }
            
            
            Entier getTeteAttribut() const 
            {
              return tete_attribut ;
            }
            
            Booleen raffraichie ;
            
          private:
            
            Entier tete_attribut ;
            
          };
          
          /// Une vue sur personne
          class DisplayPersonne : public View<ModelPersonne>
          {
          public:
  
            void update(const Event& _evenement)
            {
              personne_attribut = View<ModelPersonne>::observe->getAttribut() ;
              raffraichie = VRAI ;
            }
  
            DisplayPersonne(const Association<ModelPersonne>& _personne)
            : View<ModelPersonne>(_personne), 
              personne_attribut(_personne->getAttribut())
            {
            }
            
            
            Entier getPersonneAttribut() const
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
          Composition<ModelTete> compTete(new ModelTete()) ;
          Association<ModelTete> tete(compTete) ;
          Composition<ModelPersonne> CompPersonne(new ModelPersonne(compTete.Liberer())) ;
          Association<ModelPersonne> personne(CompPersonne) ;
          
          
          // point de vue
          Composition<ViewPoint> pointDeView(new ViewPoint()) ;          
          
          // Création des vues
          Composition<ViewTete> compViewTete(new ViewTete(tete)) ;
          Association<ViewTete> vueTete(compViewTete) ;
          pointDeView->add(compViewTete.Liberer()) ;


          Composition<DisplayPersonne> compDisplayPersonne(new DisplayPersonne(personne)) ;
          Association<DisplayPersonne> vuePersonne(compDisplayPersonne) ;
          pointDeView->add(compDisplayPersonne.Liberer()) ;
          
          vueTete->raffraichie = FAUX ;
          vuePersonne->raffraichie = FAUX ;
          
          // Utilisation
          
          // changement de personne
          personne->ChangerAttribut(10) ;
          pointDeView->update() ;
          CPPUNIT_ASSERT(vueTete->getTeteAttribut() == 0) ;
          CPPUNIT_ASSERT(vueTete->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie == VRAI) ;
          
          vueTete->raffraichie = FAUX ;
          vuePersonne->raffraichie = FAUX ;

          // aucun changement du modèle
          pointDeView->update() ;
          CPPUNIT_ASSERT(vueTete->raffraichie == FAUX) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie == FAUX) ;

          // changement de tete
          personne->getTete()->ChangerAttribut(20) ;

          pointDeView->update() ;
          CPPUNIT_ASSERT(vueTete->getTeteAttribut() == 20) ;
          CPPUNIT_ASSERT(vueTete->raffraichie == VRAI) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie == FAUX) ;

          // Changement des 2
          personne->ChangerAttribut(100) ;
          personne->getTete()->ChangerAttribut(200) ;
          pointDeView->update() ;
          CPPUNIT_ASSERT(vueTete->getTeteAttribut() == 200) ;
          CPPUNIT_ASSERT(vuePersonne->getPersonneAttribut() == 100) ;
          
          
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
