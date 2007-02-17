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
  namespace Modele 
  {

    /*!
      @name Variables du module.
    */
    // @{



      Base::EnsembleComposition<Objet> objets ;

      Base::FonctionAssociationValeurObjet<Base::Chaine,Objet> registreObjets ;

    // @}

      Base::Association<Objet> Ajouter(Objet* _objet)
      {
        if (_objet != NULL)
        {
          Objet& reference = *_objet ;
          objets.Ajouter(_objet) ;
          
          registreObjets.Ajouter(_objet->AccesNom(), reference) ;
          
          return reference ;
        }
        
        throw Exception("Modele::Ajouter appel� sans objet") ;
      }

      Base::Association<Objet> Enregistrer(const Base::Association<Objet>& _objet)
      {
        registreObjets.Ajouter(_objet->AccesNom(), _objet) ;
      }

      

    
    /*!
      @par Etat 
        minimal
    */
    void Initialiser()
    {
      objets.Vider() ;
      registreObjets.Vider() ;
    }

    /*!
      @par Etat 
        minimal
    */
    void Terminer()
    {
      Base::Traceur::MessageInterne("Deleting objects") ;
      objets.Vider() ;

      Base::Traceur::MessageInterne("Deleting object references") ;
      registreObjets.Vider() ;
      
      Base::Traceur::MessageInterne("Module Modele terminated") ;
      
    }

    /*!
      @par Etat 
        OK
    */
    Base::Association<Objet> AccesObjet(const Base::Chaine& _nom)
    {
      Base::Association<Objet> resultat(registreObjets[_nom]) ;
      VerifieCondition(resultat, Exception("pas d'objet de ce nom")) ;
      return resultat ;
    }

    /*!
      @par Etat 
        Test cod� en dur
    */
    void Charger(const Base::Chaine& _nom)
    {
     
      if (_nom == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        Base::Traceur::MessageInterne("construction de Univers...") ;
        Base::Association<Objet> univers = Ajouter(new Objet(Nom("Univers"))) ;
        
        /// ses facettes
        univers->Ajouter(new Univers()) ;
        univers->Ajouter(new Positionne()) ;

        Base::Traceur::MessageInterne("construction de Univers termin�e") ;

        /// 1.4 Une galaxie
        
        /// 1.5 Un syst�me stellaire
        Base::Traceur::MessageInterne("construction d'un syst�me...") ;
        Base::Association<Objet> systeme = univers->Ajouter(new Objet(Nom("Systeme#1"))) ;
        systeme->Ajouter(new Positionne(Position())) ;
        systeme->Ajouter(new SystemeStellaire()) ;
         
        Base::Traceur::MessageInterne("construction d'un syst�me termin�e") ;
        
        
        
        /// 2. Ajout d'objets planetes
        Base::Traceur::MessageInterne("construction d'une planete...") ;
        Base::Association<Objet> planete1 = systeme->Ajouter(new Objet(Nom("Planete#1"))) ;
        planete1->Ajouter(new Positionne(Position())) ;

        Base::Traceur::MessageInterne("construction d'une planete termin�e") ;

        /// Ajouter(new Solide(planete1, 
        
        /// 3. Ajout d'un vaisseau
        {
          Base::Traceur::MessageInterne("construction d'un vaisseau...") ;
          Base::Association<Objet> vaisseau = systeme->Ajouter(new Objet(Nom("Vaisseau"))) ;
          vaisseau->Ajouter(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, -500000)) )) ;
          
          vaisseau->Ajouter(new Solide(Modele3D("razor.mesh"))) ;
  
          Base::Traceur::MessageInterne("construction d'un vaisseau termin�e") ;
        }
        {
          Base::Traceur::MessageInterne("construction d'un vaisseau...") ;
          Base::Association<Objet> vaisseau = systeme->Ajouter(new Objet(Nom("Vaisseau3"))) ;
          vaisseau->Ajouter(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, 100000),
                                                    Distance(Distance::_Metre, -500000)) )) ;
          
          vaisseau->Ajouter(new Solide(Modele3D("razor.mesh"))) ;
  
          Base::Traceur::MessageInterne("construction d'un vaisseau termin�e") ;
        }

                
        /// 4. Ajout d'un observateur
        Base::Traceur::MessageInterne("construction d'un observateur...") ;
        Base::Association<Objet> observateur = systeme->Ajouter(new Objet(Nom("Observateur"))) ;
        observateur->Ajouter(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                     Distance(Distance::_Metre, 0),
                                                     Distance(Distance::_Metre, 0)) )) ;

        /// Il a la facult� d'observer
        observateur->Ajouter(new Observateur()) ;

        Base::Traceur::MessageInterne("construction d'un observateur termin�e") ;
      
      }
      
            
    }

    void Enlever(const Base::Association<Objet>& _objet)
    {
      if (_objet->AccesConteneur())
      {
        _objet->AccesConteneur()->Enlever(_objet) ;
      }
      else
      {
        objets.Enlever(_objet) ;
      }
    }
    
  }
}


