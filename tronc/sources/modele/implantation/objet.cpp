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

  namespace Modele {


    
    Objet::~Objet()
    {}
    
    Objet::Objet()
    {}

    Objet::Objet(const Nom& _nom)
    : nom(_nom)
    {}

    Base::Association<Objet> Objet::Ajouter(Objet* _objet)
    {
      /// Pour le détruire au cas où ca foire
      Base::Composition<Objet> temporaire(_objet) ;
      Base::Association<Objet> resultat(temporaire) ;

      /// on met à jour le lien contenu/contenant
      temporaire->conteneur = *this ;
      contenu.Ajouter(temporaire.Liberer()) ;
      
      /// On enregistre l'objet dans le modèle
      Enregistrer(resultat) ;
      
      return resultat ;
    }


    Base::Chaine Objet::AfficherReference() const
    {
      Base::Chaine resultat ;

      resultat += Base::AfficheEspaces() ;
      resultat += "<objet nom=\"" ;
      resultat += nom ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
      
    }
    
    Base::Chaine Objet::AfficherDefinition() const
    {
      Base::Chaine resultat ;

      resultat += Base::AfficheEspaces() ;
      resultat += "<objet nom=\"" ;
      resultat += nom ;
      resultat += "\">" ;
      resultat += Base::FinDeLigne() ;
      resultat += Base::AfficheEspaces() + "</objet>" + Base::FinDeLigne() ;
      
      return resultat ;
      
    }


    void Objet::Ajouter(Facette* _facette)
    {
      Base::Traceur::MessageInterne("Objet::Ajouter#1") ;
      Base::Composition<Facette> temporaire(_facette) ;

      /// erreur si l'objet a déjà une facette de ce type là
      VerifieCondition(facettes[typeid(*_facette).name()] 
                       == 
                       Base::Association<Facette>(), 
                       Exception("facette déjà existante")) ;

      this->ensembleFacettes.Ajouter(temporaire) ;

      _facette->objet = *this ;
      /// on range les facettes en fonction de leur classe
      facettes.Ajouter(typeid(*_facette).name(), temporaire.Liberer()) ;

      Base::Traceur::MessageInterne("Objet::Ajouter#3") ;

    }

    Nom Objet::AccesNom() const
    {
      return this->nom ;
    }

    Base::Association<Objet> Objet::AccesConteneur() const
    {
      return this->conteneur ;
    }

    Base::EnsembleAssociation<Objet> Objet::AccesContenu() const
    {
      return this->contenu ;
    }

    Base::Association<Objet> Objet::AccesRacine() const
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
    

    Base::EnsembleAssociation<Facette> Objet::AccesFacettes() const
    {
      return this->ensembleFacettes ;
    }

  }
}

