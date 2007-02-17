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

  namespace Model {
  
    class Trait ;
    
    /// Un objet du jeu.
    class Object : public Base::Model {
    public:
  
    /*!
      @name Construction
    */
    // @{
    
      /// Constructeurs.
      Object() ;
      Object(const Nom&) ;
    
      ~Object() ;

      /// Ajoute une facette.
      void add(Trait* _facette) ;

      /// Ajoute un objet comme contenu
      /*!
        Les objets peuvent en contenir d'autres.

      */
      Base::Association<Object> add(Object* _contenu) ;

      /// Supprime un objet.
      void remove(const Base::Association<Object>&) ;

    // @}
    /*!
      @name Display
      
      Construit une chaine XML représentant l'objet.
    */
    // @{

      /// Chaine représentant une référence à l'objet.
      virtual std::string AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual std::string AfficherDefinition() const ;


    // @}
    /*!
      @name Accès
    */
    // @{

      Nom AccesNom() const ;

      Base::Association<Object> AccesConteneur() const ;

      Base::EnsembleAssociation<Object> AccesContenu() const ;
  
      /// Le conteneur récursif de plus haut niveau.
      Base::Association<Object> AccesRacine() const ;
      
    // @}
    /*!
      @name Accès aux Traits
    */
    // @{

      /// Accès récursif au plus haut conteneur ayant la facette @ T
      template <class T> Base::Association<T> AccesRacine() const ;

      
      /// Accès à la facette T.
      /*!
        T doit être une sous classe de Trait.
      */
      template <class T> operator Base::Association<T>() const ;

      /// Accès récursif au premier conteneur ayant la facette @ T
      template <class T> Base::Association<T> AccesParent() const ;

      /// Accès aux facettes de l'objet.
      Base::EnsembleAssociation<Trait> AccesTraits() const ;

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

      
    // @}
      
    };  

    template <class T> Object::operator Base::Association<T>() const
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

    template <class T> Base::Association<T> Object::AccesRacine() const
    {
      /// T doit être une sous classe de Trait
      Base::DeriveDe<T,Trait>() ;
      
      Base::Association<Object> iterateur(*this) ;
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
