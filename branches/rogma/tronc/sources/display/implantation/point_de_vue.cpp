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

#include <base/traceur.h>
#include <base/iterateur_ensemble_composition.h>

#include <modele/facette.h>
#include <modele/objet.h>
#include <modele/positionne.h>

#include <affichage/exception.h>
#include <affichage/objet.h>
#include <affichage/point_de_vue.h>
#include <affichage/implantation/ogre/point_de_vue.h>


namespace ProjetUnivers {
  namespace Display {


    /// Stockage de la variable statique
    Base::FonctionValeurValeur<
        std::pair<std::string,std::string>, 
        ConstructeurVue> ViewPoint::constructeurs ;
 

    /*!
      La partie commune à tous les points de vues.
    
    */

    ViewPoint::ViewPoint(const Base::Association<Model::Object>& _observateur)
    : Base::ViewPoint(), observateur(_observateur), initialise(Base::FAUX)
    {}

    ViewPoint::~ViewPoint()
    {}


    void ViewPoint::Construire()
    {
      /*! 
        On parcours tous les objets du modèle en partant de l'ancètre de 
        l'observateur et on ne construit que ce qui est visible.
        
        Dès qu'un objet est invisible, on ne parcours pas ses fils.
      */

      Base::Traceur::MessageInterne("Entering Display::ViewPoint::Construire") ;
      
      Base::Association<Model::Positionne> ancetrePositionne = 
                  this->observateur->AccesRacine<Model::Positionne>() ;

      if (ancetrePositionne)
      {
        this->add(ConstruireVue(ancetrePositionne->AccesObject())) ;
      }
      
      Base::Traceur::MessageInterne("Leaving Display:ViewPoint::Construire") ;
      
      
    }

    Object* 
    ViewPoint::ConstruireVue(const Base::Association<Model::Object>& _modele)
    {

      Base::Traceur::MessageInterne("Entering Display::ViewPoint::ConstruireVue") ;
      
      Base::Composition<Object> resultat ;
      
      if (this->EstVisible(_modele))
      {
        Base::Traceur::MessageInterne("building View Object") ;

        /// On construit l'objet
        resultat = new Object(_modele,*this) ;

        Base::Traceur::MessageInterne("built View Object") ;
        
        /// On mémorise l'observateur
        if (_modele == this->observateur)
        {
          this->vueObservateur = resultat ;
        }

        Base::Traceur::MessageInterne("building View Traits") ;
        
        /// ses facettes
        for (Base::IterateurEnsembleAssociation<Model::Trait> 
                facette(_modele->AccesTraits()) ; 
             facette.Valide() ;
             ++facette)
        {
          Base::Traceur::MessageInterne("searching constructor for " + std::string(typeid(*this).name()) + " " +  typeid(**facette).name()) ;
          ConstructeurVue constructeur = 
            constructeurs[std::make_pair<std::string,std::string>(typeid(*this).name(),typeid(**facette).name())] ;

          if (! constructeur.empty())
          {
            resultat->add(constructeur(*facette)) ;
          }
          else
          {
            Base::Traceur::MessageInterne("in Display::ViewPoint::ConstruireVue : constructeur vide pour " + std::string(typeid(*this).name()) + " " +  typeid(**facette).name()) ;
          }            
          
          
        }
        
        /// On construit ses composants visibles
        for (Base::IterateurEnsembleAssociation<Model::Object> 
                                  fils(_modele->AccesContenu()) ;
             fils.Valide() ;
             ++fils)
        {
          if (this->EstVisible(*fils) == Base::VRAI)
          {
            resultat->add(this->ConstruireVue(*fils)) ;
          }
        }
      }

      Base::Traceur::MessageInterne("Leaving Display::ViewPoint::ConstruireVue") ;
      
      return resultat.Liberer() ;
    }



    ViewPoint* 
      ViewPoint::Construire(const Base::Association<Model::Object>& _observateur)
    {
      
      Base::Traceur::MessageInterne("Entering Display::ViewPoint::Construire(const Base::Association<Model::Object>&)") ;
      
      /// implantation à l'aide de Ogre
      Base::Composition<ViewPoint> resultat(
          new Implantation::Ogre::ViewPoint(_observateur)) ;
      
      resultat->Construire() ;

      Base::Traceur::MessageInterne("Leaving Display::ViewPoint::Construire(const Base::Association<Model::Object>&)") ;
      
      return resultat.Liberer() ;

    }

    void ViewPoint::EnregistreConstruction(
                          const std::string& _classeModel,
                          const std::string& _classeViewPoint,
                          ConstructeurVue _constructeur)
    {
      std::cout << "Registering constructor for " << _classeViewPoint << " " << _classeModel << std::endl ;
      constructeurs.add(std::make_pair<std::string,std::string>(_classeViewPoint,_classeModel),_constructeur) ;
      std::cout << "Registered constructor" << std::endl ;
    }

    Base::Association<Object> ViewPoint::AccesVueObservateur() const
    {
      return this->vueObservateur ;
    }


    void ViewPoint::destroy(const Base::Association<Base::Implantation::BaseVue>& _vue)
    {
      Base::Traceur::MessageInterne("ViewPoint::destroy removing view element") ;

      Object* object = dynamic_cast<Object*>(&*_vue) ;
      if (object)
      {
        Base::Traceur::MessageInterne("element is object") ;

        Base::Association<Object> element(*object) ;
        Base::Association<Object> conteneur(object->AccesConteneur()) ;
        if (conteneur)
        {
          conteneur->remove(element) ;
          Base::Traceur::MessageInterne("removed element from object") ;
        }
        else
        {
          this->vues.remove(_vue) ;
          Base::Traceur::MessageInterne("removed element from view point") ;
        }
      }
      else
      {

        Trait* facette = dynamic_cast<Trait*>(&*_vue) ;
        if (facette)
        {
          Base::Traceur::MessageInterne("element is facette") ;
          
          Base::Association<Trait> element(*facette) ;
          facette->AccesObject()->remove(element) ;
          Base::Traceur::MessageInterne("removed element") ;
          
        }
        else
        {
          /// error
          throw Exception("internal error") ;
        }
      }
    }

    Base::Association<Object> ViewPoint::RechercherVue
      (const Base::Association<Model::Object>& _objet) const
    {
      Base::Association<Model::Positionne> parent(*_objet->AccesConteneur()) ;
      if (! parent)
      {
        for(Base::IterateurEnsembleComposition<Base::Implantation::BaseVue> vue(this->vues) ;
            vue.Valide() ;
            ++vue)
        {
          if (vue->AccesObserve() == _objet)
          {
            Object* result = dynamic_cast<Object*>(vue.operator->()) ;
            return *result ;
          }
        }
      }
      else
      {
        return RechercherVue(_objet->AccesConteneur())->RechercherFils(_objet) ;
      }
    }


  }
}

