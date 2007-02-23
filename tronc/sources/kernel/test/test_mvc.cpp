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


#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/view.h>
#include <kernel/view_point.h>


CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Implementation::Test::TestMVC) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Implementation {
      namespace Test {

        /// un espace de nom local
        namespace
        {
          class ModelTete : public Model
          {
          public:
          
            ModelTete()
            : Model(), attribut(0)
            {}
          
            void ChangerAttribut(const int& nouvelleValeur) 
            {
              attribut = nouvelleValeur ;
              notify() ;
            }  
            
            int getAttribut() const
            {
              return attribut ;
            }
            
          private:
          
            /// un attribut qui va etre modifié
            int attribut ;
            
          };
          
          
          class ModelPersonne : public Model
          {
          public:
          
            ModelPersonne(ModelTete* _tete)
            : Model(), attribut(0), tete(_tete)
            {}
          
            void ChangerAttribut(const int& nouvelleValeur) 
            {
              attribut = nouvelleValeur ;
              notify() ;
            }  
            
            int getAttribut() const
            {
              return attribut ;
            }
            
            ModelTete* getTete() const
            {
              return tete ;
            }
            
            ~ModelPersonne()
            {
              delete tete ;
            }
            
          private:
          
            /// un attribut qui va etre modifié
            int attribut ;
            
            ModelTete* tete ; 
            
          };


          
          
          /// Une vue sur une tete
          class ViewTete : public View<ModelTete>
          {
          public:
  
            void update(const Event& _evenement)
            {
              tete_attribut = View<ModelTete>::observed->getAttribut() ;
              raffraichie = true ;
            }
  
            ViewTete(ModelTete* _tete)
            : View<ModelTete>(_tete),
              tete_attribut(_tete->getAttribut())
            {
            }
            
            /// Suppression.
            virtual void Supprimer()
            {
              
            }
            
            
            int getTeteAttribut() const 
            {
              return tete_attribut ;
            }
            
            bool raffraichie ;
            
          private:
            
            int tete_attribut ;
            
          };
          
          /// Une vue sur personne
          class DisplayPersonne : public View<ModelPersonne>
          {
          public:
  
            void update(const Event& _evenement)
            {
              personne_attribut = View<ModelPersonne>::observed->getAttribut() ;
              raffraichie = true ;
            }
  
            DisplayPersonne(ModelPersonne* _personne)
            : View<ModelPersonne>(_personne), 
              personne_attribut(_personne->getAttribut())
            {
            }
            
            
            int getPersonneAttribut() const
            {
              return personne_attribut ;
            }
            
            bool raffraichie ;
            
          private:
            int personne_attribut ;
          };
          
          
        }


        void TestMVC::TesteObservation()
        {
          
          
          try {
          // Création du modèle
          std::auto_ptr<ModelTete> head(new ModelTete()) ;
          ModelTete* tempHead = head.get() ;
          std::auto_ptr<ModelPersonne> CompPersonne(new ModelPersonne(head.release())) ;
          ModelPersonne* personne = CompPersonne.get() ;
          
          // point de vue
          std::auto_ptr<ViewPoint> viewPoint(new ViewPoint()) ;          
          
          // Création des vues
          std::auto_ptr<ViewTete> compViewTete(new ViewTete(tempHead)) ;
          ViewTete* vueTete = compViewTete.get() ;
          viewPoint->add(compViewTete.release()) ;


          std::auto_ptr<DisplayPersonne> compDisplayPersonne(new DisplayPersonne(CompPersonne.get())) ;
          DisplayPersonne* vuePersonne(compDisplayPersonne.get()) ;
          viewPoint->add(compDisplayPersonne.release()) ;
          
          vueTete->raffraichie = false ;
          vuePersonne->raffraichie = false ;
          
          // Utilisation
          
          // changement de personne
          personne->ChangerAttribut(10) ;
          viewPoint->update() ;
          CPPUNIT_ASSERT(vueTete->getTeteAttribut() == 0) ;
          CPPUNIT_ASSERT(! vueTete->raffraichie) ;
          CPPUNIT_ASSERT(vuePersonne->raffraichie) ;
          
          vueTete->raffraichie = false ;
          vuePersonne->raffraichie = false ;

          // aucun changement du modèle
          viewPoint->update() ;
          CPPUNIT_ASSERT(! vueTete->raffraichie) ;
          CPPUNIT_ASSERT(! vuePersonne->raffraichie) ;

          // changement de tete
          personne->getTete()->ChangerAttribut(20) ;

          viewPoint->update() ;
          CPPUNIT_ASSERT(vueTete->getTeteAttribut() == 20) ;
          CPPUNIT_ASSERT(vueTete->raffraichie) ;
          CPPUNIT_ASSERT(! vuePersonne->raffraichie) ;

          // Changement des 2
          personne->ChangerAttribut(100) ;
          personne->getTete()->ChangerAttribut(200) ;
          viewPoint->update() ;
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
