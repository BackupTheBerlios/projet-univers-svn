/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#include <base/joli_affichage.h>
#include <base/fonction_association_valeur_objet.h>
#include <base/ensemble_composition.h>

#include <base/iterateur_ensemble_composition.h>
#include <base/traceur.h>
#include <base/erreur.h>

#include <modele/exception.h>
#include <modele/facette.h>
#include <modele/objet.h>
#include <modele/observateur.h>
#include <modele/positionne.h>
#include <modele/systeme_stellaire.h>
#include <modele/solide.h>
#include <modele/univers.h>

#include <modele/modele.h>

namespace ProjetUnivers {
  namespace Model 
  {

    /*!
      @name Variables du module.
    */
    // @{



      Base::EnsembleComposition<Object> objets ;

      Base::FonctionAssociationValeurObject<std::string,Object> registreObjects ;

    // @}

      Base::Association<Object> add(Object* _objet)
      {
        if (_objet != NULL)
        {
          Object& reference = *_objet ;
          objets.add(_objet) ;
          
          registreObjects.add(_objet->AccesNom(), reference) ;
          
          return reference ;
        }
        
        throw Exception("Model::add appelé sans objet") ;
      }

      Base::Association<Object> register(const Base::Association<Object>& _objet)
      {
        registreObjects.add(_objet->AccesNom(), _objet) ;
      }

      

    
    /*!
      @par Etat 
        minimal
    */
    void init()
    {
      objets.Vider() ;
      registreObjects.Vider() ;
    }

    /*!
      @par Etat 
        minimal
    */
    void close()
    {
      Base::Traceur::MessageInterne("Deleting objects") ;
      objets.Vider() ;

      Base::Traceur::MessageInterne("Deleting object references") ;
      registreObjects.Vider() ;
      
      Base::Traceur::MessageInterne("Module Model terminated") ;
      
    }

    /*!
      @par Etat 
        OK
    */
    Base::Association<Object> AccesObject(const std::string& _nom)
    {
      Base::Association<Object> resultat(registreObjects[_nom]) ;
      VerifieCondition(resultat, Exception("pas d'objet de ce nom")) ;
      return resultat ;
    }

    /*!
      @par Etat 
        Test codé en dur
    */
    void load(const std::string& _nom)
    {
     
      if (_nom == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        Base::Traceur::MessageInterne("construction de Univers...") ;
        Base::Association<Object> univers = add(new Object(Nom("Univers"))) ;
        
        /// ses facettes
        univers->add(new Univers()) ;
        univers->add(new Positionne()) ;

        Base::Traceur::MessageInterne("construction de Univers terminée") ;

        /// 1.4 Une galaxie
        
        /// 1.5 Un système stellaire
        Base::Traceur::MessageInterne("construction d'un système...") ;
        Base::Association<Object> systeme = univers->add(new Object(Nom("Systeme#1"))) ;
        systeme->add(new Positionne(Position())) ;
        systeme->add(new SystemeStellaire()) ;
         
        Base::Traceur::MessageInterne("construction d'un système terminée") ;
        
        
        
        /// 2. Ajout d'objets planetes
        Base::Traceur::MessageInterne("construction d'une planete...") ;
        Base::Association<Object> planete1 = systeme->add(new Object(Nom("Planete#1"))) ;
        planete1->add(new Positionne(Position())) ;

        Base::Traceur::MessageInterne("construction d'une planete terminée") ;

        /// add(new Solide(planete1, 
        
        /// 3. Ajout d'un vaisseau
        {
          Base::Traceur::MessageInterne("construction d'un vaisseau...") ;
          Base::Association<Object> vaisseau = systeme->add(new Object(Nom("Vaisseau"))) ;
          vaisseau->add(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, -500000)) )) ;
          
          vaisseau->add(new Solide(Model3D("razor.mesh"))) ;
  
          Base::Traceur::MessageInterne("construction d'un vaisseau terminée") ;
        }
        {
          Base::Traceur::MessageInterne("construction d'un vaisseau...") ;
          Base::Association<Object> vaisseau = systeme->add(new Object(Nom("Vaisseau3"))) ;
          vaisseau->add(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, 100000),
                                                    Distance(Distance::_Metre, -500000)) )) ;
          
          vaisseau->add(new Solide(Model3D("razor.mesh"))) ;
  
          Base::Traceur::MessageInterne("construction d'un vaisseau terminée") ;
        }

                
        /// 4. Ajout d'un observateur
        Base::Traceur::MessageInterne("construction d'un observateur...") ;
        Base::Association<Object> observateur = systeme->add(new Object(Nom("Observateur"))) ;
        observateur->add(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                     Distance(Distance::_Metre, 0),
                                                     Distance(Distance::_Metre, 0)) )) ;

        /// Il a la faculté d'observer
        observateur->add(new Observateur()) ;

        Base::Traceur::MessageInterne("construction d'un observateur terminée") ;
      
      }
      
            
    }

    void remove(const Base::Association<Object>& _objet)
    {
      if (_objet->AccesConteneur())
      {
        _objet->AccesConteneur()->remove(_objet) ;
      }
      else
      {
        objets.remove(_objet) ;
      }
    }
    
  }
}


