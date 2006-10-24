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

#ifndef _PU_MODELE_OBJET_H_
#define _PU_MODELE_OBJET_H_

#include <typeinfo>

#include <base/traceur.h>
#include <base/derive_de.h>
#include <base/chaine.h>
#include <base/ensemble_composition.h>
#include <base/modele.h>

#include <base/fonction_composition_valeur_objet.h>

#include <modele/nom.h>
#include <modele/identificateur.h>

namespace ProjetUnivers {

  namespace Modele {
  
    class Facette ;
    
    /// Un objet du jeu.
    class Objet : public Base::Modele {
    public:
  
    /*!
      @name Construction
    */
    // @{
    
      /// Constructeurs.
      Objet() ;
      Objet(const Nom&) ;
    
      ~Objet() ;

      /// Ajoute une facette.
      void Ajouter(Facette* _facette) ;

      /// Ajoute un objet comme contenu
      /*!
        Les objets peuvent en contenir d'autres.

      */
      Base::Association<Objet> Ajouter(Objet* _contenu) ;

    // @}
    /*!
      @name Affichage
      
      Construit une chaine XML représentant l'objet.
    */
    // @{

      /// Chaine représentant une référence à l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;


    // @}
    /*!
      @name Accès
    */
    // @{

      Nom AccesNom() const ;

      Base::Association<Objet> AccesConteneur() const ;

      Base::EnsembleAssociation<Objet> AccesContenu() const ;
  
      /// Le conteneur récursif de plus haut niveau.
      Base::Association<Objet> AccesRacine() const ;
      
    // @}
    /*!
      @name Accès aux Facettes
    */
    // @{

      /// Accès récursif au plus haut conteneur ayant la facette @ T
      template <class T> Base::Association<T> AccesRacine() const ;

      
      /// Accès à la facette T.
      /*!
        T doit être une sous classe de Facette.
      */
      template <class T> operator Base::Association<T>() const ;

      /// Accès récursif au premier conteneur ayant la facette @ T
      template <class T> Base::Association<T> AccesParent() const ;

      /// Accès aux facettes de l'objet.
      Base::EnsembleAssociation<Facette> AccesFacettes() const ;

    // @}
      

    private:

    
    // @}
    /*!
      @name Attributs
    */
    // @{
       
      /// Identificateur de l'objet.
      Identificateur identificateur ;

      /// Nom de l'objet.
      /*!
        Pas forcément unique.
      */
      Nom nom ;
    
      /// Les facettes de l'objet
      Base::FonctionCompositionValeurObjet<Base::Chaine, Facette> facettes ;

      /// Redondant, mais pour simplifier le travail
      /*!
        @todo 
          supprimer
      */
      Base::EnsembleAssociation<Facette> ensembleFacettes ;

      /// L'éventuel objet qui contient celui-ci
      Base::Association<Objet> conteneur ;

      /// Les objets contenus dans celui-ci
      Base::EnsembleComposition<Objet> contenu ;

      
    // @}
      
    };  

    template <class T> Objet::operator Base::Association<T>() const
    {
      /// T doit être une sous classe de Facette
      Base::DeriveDe<T,Facette>() ;
      
      /// on attrape la facette 
      Base::Association<Facette> facette = facettes[typeid(T).name()] ;
      
      /// si elle existe on effectue la conversion :
      if (facette)
      {
        Facette* pFacette = facette.operator->() ;
        T* t = static_cast<T*>(pFacette) ; 
        return *t ;
      }
      else
        return Base::Association<T>() ;
    }

    template <class T> Base::Association<T> Objet::AccesParent() const
    {
      /// T doit être une sous classe de Facette
      Base::DeriveDe<T,Facette>() ;
      
      Base::Association<Objet> iterateur(*this) ;
      Base::Association<T> facette(*iterateur) ;
      
      while((! facette) && iterateur)
      {
        iterateur = iterateur->AccesConteneur() ;
        if (iterateur)
        {
          facette = *iterateur ;
        }
      }
      
      return facette ;
      
    }

    template <class T> Base::Association<T> Objet::AccesRacine() const
    {
      /// T doit être une sous classe de Facette
      Base::DeriveDe<T,Facette>() ;
      
      Base::Association<Objet> iterateur(*this) ;
      Base::Association<T> facette(*iterateur) ;
      
      Base::Association<T> plus_haute_facette_trouvee ;
      
      while(facette && iterateur)
      {
        plus_haute_facette_trouvee = facette ;
        
        iterateur = iterateur->AccesConteneur() ;
        if (iterateur)
        {
          facette = *iterateur ;
        }
      }
      
      return plus_haute_facette_trouvee ;
      
    }


  } 
  
}


#endif // _PU_MODELE_OBJET_H_
