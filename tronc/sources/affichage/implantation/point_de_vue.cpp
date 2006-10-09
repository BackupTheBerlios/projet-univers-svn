/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#include <base/traceur.h>

#include <modele/facette.h>
#include <modele/objet.h>

#include <affichage/point_de_vue.h>
#include <affichage/implantation/ogre/point_de_vue.h>


namespace ProjetUnivers {

  namespace Affichage {

    /// Stockage de la variable statique
    Base::FonctionValeurValeur<
        std::pair<Base::Chaine,Base::Chaine>, 
        ConstructeurVue> PointDeVue::constructeurs ;
 

    /*!
      La partie commune à tous les points de vues.
    
    */

    PointDeVue::PointDeVue(const Base::Association<Modele::Objet>& _observateur)
    : Base::PointDeVue(), observateur(_observateur)
    {}

    PointDeVue::~PointDeVue()
    {}

   
//    Base::Association<Objet> 
//    PointDeVue::AccesVue(const Base::Association<Modele::Objet>& _modele) const
//    {
//      for(Base::IterateurEnsembleComposition<
//    }
//   
    

    void PointDeVue::Construire()
    {
      /*! 
        On parcours tous les objets du modèle en partant de l'ancètre de 
        l'observateur et on ne construit que ce qui est visible.
        
        Dès qu'un objet est invisible, on ne parcours pas ses fils.
      */

      Base::Traceur::MessageInterne("Entering Affichage::PointDeVue::Construire") ;
      
      Base::Association<Modele::Objet> ancetre = 
                                              this->observateur->AccesRacine() ;
      this->Ajouter(ConstruireVue(ancetre)) ;
      
      Base::Traceur::MessageInterne("Leaving Affichage:PointDeVue::Construire") ;
      
      
    }

    Objet* 
    PointDeVue::ConstruireVue(const Base::Association<Modele::Objet>& _modele)
    {

      Base::Traceur::MessageInterne("Entering Affichage::PointDeVue::ConstruireVue") ;
      
      Base::Composition<Objet> resultat ;
      
      if (this->EstVisible(_modele) == Base::VRAI)
      {
        /// On construit l'objet
        resultat = new Objet(_modele,*this) ;
        
        /// ses facettes
        for (Base::IterateurEnsembleAssociation<Modele::Facette> 
                facette(_modele->AccesFacettes()) ; 
             facette.Valide() ;
             ++facette)
        {
          Base::Traceur::MessageInterne("searching constructor for " + Base::Chaine(typeid(*this).name()) + " " +  typeid(**facette).name()) ;
          ConstructeurVue constructeur = 
            constructeurs[std::make_pair<Base::Chaine,Base::Chaine>(typeid(*this).name(),typeid(**facette).name())] ;

          if (! constructeur.empty())
          {
            resultat->Ajouter(constructeur(*facette)) ;
          }
          else
          {
            Base::Traceur::MessageInterne("in Affichage::PointDeVue::ConstruireVue : constructeur vide pour " + Base::Chaine(typeid(*this).name()) + " " +  typeid(**facette).name()) ;
          }            
          
          
        }
        
        /// On construit ses composants visibles
        for (Base::IterateurEnsembleAssociation<Modele::Objet> 
                                  fils(_modele->AccesContenu()) ;
             fils.Valide() ;
             ++fils)
        {
          if (this->EstVisible(*fils) == Base::VRAI)
          {
            resultat->Ajouter(this->ConstruireVue(*fils)) ;
          }
        }
      }

      Base::Traceur::MessageInterne("Leaving Affichage::PointDeVue::ConstruireVue") ;
      
      return resultat.Liberer() ;
    }



    PointDeVue* 
      PointDeVue::Construire(const Base::Association<Modele::Objet>& _observateur)
    {
      
      Base::Traceur::MessageInterne("Entering Affichage::PointDeVue::Construire(const Base::Association<Modele::Objet>&)") ;
      
      /// implantation à l'aide de Ogre
      Base::Composition<PointDeVue> resultat(
          new Implantation::Ogre::PointDeVue(_observateur)) ;
      
      resultat->Construire() ;

      Base::Traceur::MessageInterne("Leaving Affichage::PointDeVue::Construire(const Base::Association<Modele::Objet>&)") ;
      
      return resultat.Liberer() ;

    }

    void PointDeVue::EnregistreConstruction(
                          const Base::Chaine& _classeModele,
                          const Base::Chaine& _classePointDeVue,
                          ConstructeurVue _constructeur)
    {
      std::cout << "Registering constructor for " << _classePointDeVue << " " << _classeModele << std::endl ;
      constructeurs.Ajouter(std::make_pair<Base::Chaine,Base::Chaine>(_classePointDeVue,_classeModele),_constructeur) ;
    }

  }
}

