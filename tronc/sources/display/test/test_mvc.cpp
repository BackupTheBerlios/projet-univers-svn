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

#include <display/test/test_mvc.h>


#include <kernel/log.h>
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/view.h>
#include <kernel/view_point.h>


CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Display::Test::TestMVC) ;

namespace ProjetUnivers {
  namespace Display {
    namespace Test {

      /// un espace de nom local
      namespace
      {
        class ModelTete : public Kernel::Model
        {
        public:
        
          ModelTete()
          : Kernel::Model(), attribut(0)
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
        
        
        class ModelPersonne : public Kernel::Model
        {
        public:
        
          ModelPersonne(ModelTete* _tete)
          : Kernel::Model(), attribut(0), tete(_tete)
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
        class ViewTete : public Kernel::View<ModelTete>
        {
        public:

          void update(const Kernel::Event& _evenement)
          {
            tete_attribut = Kernel::View<ModelTete>::observed->getAttribut() ;
            raffraichie = true ;
          }

          ViewTete(ModelTete* _tete)
          : Kernel::View<ModelTete>(_tete),
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
        class DisplayPersonne : public Kernel::View<ModelPersonne>
        {
        public:

          void update(const Kernel::Event& _evenement)
          {
            personne_attribut = Kernel::View<ModelPersonne>::observed->getAttribut() ;
            raffraichie = true ;
          }

          DisplayPersonne(ModelPersonne* _personne)
          : Kernel::View<ModelPersonne>(_personne), 
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


      void TestMVC::TestObservation()
      {

        Kernel::Log::InternalMessage("Entering TestMVC::TestObservation") ;

        {
          // Création du modèle
          std::auto_ptr<ModelTete> head(new ModelTete()) ;
          ModelTete* tempHead = head.get() ;
          std::auto_ptr<ModelPersonne> CompPersonne(new ModelPersonne(head.release())) ;
          ModelPersonne* personne = CompPersonne.get() ;
  
          Kernel::Log::InternalMessage("TestMVC::TestObservation#1") ;
          
          // point de vue
          std::auto_ptr<Kernel::ViewPoint> viewPoint(new Kernel::ViewPoint()) ;          
          
          // Création des vues
          std::auto_ptr<ViewTete> compViewTete(new ViewTete(tempHead)) ;
          ViewTete* vueTete = compViewTete.get() ;
          viewPoint->add(compViewTete.release()) ;
  
          Kernel::Log::InternalMessage("TestMVC::TestObservation#2") ;
  
          std::auto_ptr<DisplayPersonne> compDisplayPersonne(new DisplayPersonne(CompPersonne.get())) ;
          DisplayPersonne* vuePersonne(compDisplayPersonne.get()) ;
          viewPoint->add(compDisplayPersonne.release()) ;
          
          vueTete->raffraichie = false ;
          vuePersonne->raffraichie = false ;
  
          Kernel::Log::InternalMessage("TestMVC::TestObservation#3") ;
          
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
        
        Kernel::Log::InternalMessage("Leaving TestMVC::TestObservation") ;
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
