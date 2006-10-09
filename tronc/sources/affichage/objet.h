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

      /// Ajoute une vue comme contenu
      /*!
        Les vues peuvent en contenir d'autres.

      */
      Base::Association<Objet> Ajouter(Objet* _contenu) ;
      
      /// Ajoute une facette.      
      Base::Association<Objet> Ajouter(Facette* _facette) ;
      

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
  
    // @}


    private:

      /// Facettes d'affichage de l'objet
      Base::FonctionCompositionValeurObjet<Base::Chaine, Facette> facettes ;          
      
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

  }
}


#endif
