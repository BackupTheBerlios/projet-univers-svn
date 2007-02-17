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

#ifndef _PU_AFFICHAGE_OBJET_H_
#define _PU_AFFICHAGE_OBJET_H_


#include <base/fonction_composition_valeur_objet.h>
#include <base/vue.h>

#include <modele/objet.h>

#include <affichage/facette.h>

namespace ProjetUnivers {
  namespace Affichage {
    
    class PointDeVue ;
    
    /// Vue d'affichage d'un objet.
    /*!

    */
    class Objet : public Base::Vue<Modele::Objet>
    {
    public:

    /*!
      @name Construction
    */
    // @{

      /// Construction d'une vue de @c _objet relative à @c _pointDeVe
      Objet(const Base::Association<Modele::Objet>& _objet, 
            const Base::Association<PointDeVue>& _pointDeVue) ;
          
      /// Initialise la vue
      virtual void Initialiser() ;

      /// Termine la vue
      virtual void Terminer() ;

      /// Mise à jour de la vue.
      virtual void Rafraichir(const Base::Evenement&) ;

      /// Ajoute une vue comme contenu
      /*!
        Les vues peuvent en contenir d'autres.

      */
      Base::Association<Objet> Ajouter(Objet* _contenu) ;
      
      /// Ajoute une facette.      
      Base::Association<Facette> Ajouter(Facette* _facette) ;
      
      /// Enleve et détruit un objet.      
      void Enlever(const Base::Association<Objet>& _objet) ;
      
      /// Enleve et détruit une facette.      
      void Enlever(const Base::Association<Facette>& _facette) ;



    // @}
    /*!
      @name Accès
    */
    // @{
      
      /// Accès à la facette T.
      /*!
        T doit être une sous classe de Facette.
      */
      template <class T> operator Base::Association<T>() const ;

      /// Acces au conteneur de la vue
      Base::Association<Objet> AccesConteneur() const ;
  
      /// Accès récursif au premier conteneur ayant la facette @ T
      template <class T> Base::Association<T> AccesParent() const ;
  
      Base::Association<PointDeVue> AccesPointDeVue() const ;

    // @}


    private:

      /// Facettes d'affichage de l'objet
      /*!
        Associe les nom des classes de facettes aux facettes.
      */
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
      
    };


    template <class T>  Objet::operator Base::Association<T>() const
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


  }
}


#endif
