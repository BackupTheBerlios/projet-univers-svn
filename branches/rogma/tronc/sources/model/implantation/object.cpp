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
#include <base/erreur.h>
#include <base/joli_affichage.h>

#include <modele/exception.h>
#include <modele/objet.h>
#include <modele/facette.h>
#include <modele/modele.h>

namespace ProjetUnivers {

  namespace Model {


    
    Object::~Object()
    {}
    
    Object::Object()
    {}

    Object::Object(const Nom& _nom)
    : nom(_nom)
    {}

    Base::Association<Object> Object::add(Object* _objet)
    {
      /// Pour le détruire au cas où ca foire
      Base::Composition<Object> temporaire(_objet) ;
      Base::Association<Object> resultat(temporaire) ;

      /// on met à jour le lien contenu/contenant
      temporaire->conteneur = *this ;
      contenu.add(temporaire.Liberer()) ;
      
      /// On enregistre l'objet dans le modèle
      register(resultat) ;
      
      this->Notifier(Base::Evenement(Base::Evenement::Ajout,"fils",resultat)) ;
      
      return resultat ;
    }

    void Object::remove(const Base::Association<Object>& _objet)
    {
      this->contenu.remove(_objet) ;
    }

    std::string Object::AfficherReference() const
    {
      std::string resultat ;

      resultat += Base::AfficheEspaces() ;
      resultat += "<objet nom=\"" ;
      resultat += nom ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
      
    }
    
    std::string Object::AfficherDefinition() const
    {
      std::string resultat ;

      resultat += Base::AfficheEspaces() ;
      resultat += "<objet nom=\"" ;
      resultat += nom ;
      resultat += "\">" ;
      resultat += Base::FinDeLigne() ;
      resultat += Base::AfficheEspaces() + "</objet>" + Base::FinDeLigne() ;
      
      return resultat ;
      
    }


    void Object::add(Trait* _facette)
    {
      Base::Traceur::MessageInterne("Model::Object::add(Trait)#1") ;
      Base::Composition<Trait> temporaire(_facette) ;

      /// erreur si l'objet a déjà une facette de ce type là
      VerifieCondition(facettes[typeid(*_facette).name()] 
                       == 
                       Base::Association<Trait>(), 
                       Exception("facette déjà existante")) ;

      this->ensembleTraits.add(temporaire) ;

      _facette->objet = *this ;
      /// on range les facettes en fonction de leur classe
      facettes.add(typeid(*_facette).name(), temporaire.Liberer()) ;

      Base::Traceur::MessageInterne("Model::Object::add(facette)#3") ;
      
      this->Notifier() ;
    }

    Nom Object::AccesNom() const
    {
      return this->nom ;
    }

    Base::Association<Object> Object::AccesConteneur() const
    {
      return this->conteneur ;
    }

    Base::EnsembleAssociation<Object> Object::AccesContenu() const
    {
      return this->contenu ;
    }

    Base::Association<Object> Object::AccesRacine() const
    {
      if (! this->conteneur)
      {
        return *this ;
      }
      else
      {
        return this->conteneur->AccesRacine() ;
      }
    }
    

    Base::EnsembleAssociation<Trait> Object::AccesTraits() const
    {
      return this->ensembleTraits ;
    }

  }
}

