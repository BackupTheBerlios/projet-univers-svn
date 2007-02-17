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
  namespace Display {
    
    class ViewPoint ;
    
    /// Vue d'affichage d'un objet.
    /*!

    */
    class Object : public Base::Vue<Model::Object>
    {
    public:

    /*!
      @name Construction
    */
    // @{

      /// Construction d'une vue de @c _objet relative à @c _pointDeVe
      Object(const Base::Association<Model::Object>& _objet, 
            const Base::Association<ViewPoint>& _pointDeVue) ;
          
      /// Initialise la vue
      virtual void init() ;

      /// Termine la vue
      virtual void close() ;

      /// Mise à jour de la vue.
      virtual void update(const Base::Evenement&) ;

      /// Ajoute une vue comme contenu
      /*!
        Les vues peuvent en contenir d'autres.

      */
      Base::Association<Object> add(Object* _contenu) ;
      
      /// Ajoute une facette.      
      Base::Association<Trait> add(Trait* _facette) ;
      
      /// Enleve et détruit un objet.      
      void remove(const Base::Association<Object>& _objet) ;
      
      /// Enleve et détruit une facette.      
      void remove(const Base::Association<Trait>& _facette) ;



    // @}
    /*!
      @name Accès
    */
    // @{
      
      /// Accès à la facette T.
      /*!
        T doit être une sous classe de Trait.
      */
      template <class T> operator Base::Association<T>() const ;

      /// Acces au conteneur de la vue
      Base::Association<Object> AccesConteneur() const ;
  
      /// Accès récursif au premier conteneur ayant la facette @ T
      template <class T> Base::Association<T> AccesParent() const ;
  
      Base::Association<ViewPoint> AccesViewPoint() const ;

      /// Retrouver une vue dans les fils du modèle
      Base::Association<Object> RechercherFils
        (const Base::Association<Model::Object>& _objet) const ;


    // @}


    private:

      /// Traits d'affichage de l'objet
      /*!
        Associe les nom des classes de facettes aux facettes.
      */
      Base::FonctionCompositionValeurObject<std::string, Trait> facettes ;          

      /// Redondant, mais pour simplifier le travail
      /*!
        @todo 
          supprimer
      */
      Base::EnsembleAssociation<Trait> ensembleTraits ;
      
      /// L'éventuel objet qui contient celui-ci
      Base::Association<Object> conteneur ;

      /// Les objets contenus dans celui-ci
      Base::EnsembleComposition<Object> contenu ;
      
    };


    template <class T>  Object::operator Base::Association<T>() const
    {
      /// T doit être une sous classe de Trait
      Base::DeriveDe<T,Trait>() ;
      
      /// on attrape la facette 
      Base::Association<Trait> facette = facettes[typeid(T).name()] ;
      
      /// si elle existe on effectue la conversion :
      if (facette)
      {
        Trait* pTrait = facette.operator->() ;
        T* t = static_cast<T*>(pTrait) ; 
        return *t ;
      }
      else
        return Base::Association<T>() ;
    }

    template <class T> Base::Association<T> Object::AccesParent() const
    {
      /// T doit être une sous classe de Trait
      Base::DeriveDe<T,Trait>() ;
      
      Base::Association<Object> iterateur(*this) ;
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
