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

#ifndef PU_DISPLAY_OBJECT_H_
#define PU_DISPLAY_OBJECT_H_

#include <map>
#include <kernel/view.h>
#include <model/object.h>
#include <display/trait.h>

namespace ProjetUnivers {
  namespace Display {
    
    class ViewPoint ;
    
    /// View d'affichage d'un objet.
    /*!

    */
    class Object : public Kernel::View<Model::Object>
    {
    public:

    /*!
      @name Construction
    */
    // @{

      /// Construction d'une vue de @c _objet relative � @c _pointDeVe
      Object(Model::Object* _object, 
             ViewPoint* _viewPoint) ;
          
      /// Initialise la vue
      virtual void init() ;

      /// Termine la vue
      virtual void close() ;

      /// Mise � jour de la vue.
      virtual void update(const Kernel::Event&) ;

      /// Ajoute une vue comme contenu
      /*!
        Les vues peuvent en contenir d'autres.

      */
      Object* add(Object* _content) ;
      
      /// Ajoute une facette.      
      Trait* add(Trait* _trait) ;
      
      /// Enleve et d�truit un objet.      
      void remove(Object* _object) ;
      
      /// Enleve et d�truit une facette.      
      void remove(Trait* _trait) ;



    // @}
    /*!
      @name Acc�s
    */
    // @{
      
      /// Acc�s � la facette T.
      /*!
        T doit �tre une sous classe de Trait.
      */
      template <class T> getTrait<T>() const ;

      /// get au conteneur de la vue
      Object* getContener() const ;
  
      /// Acc�s r�cursif au premier conteneur ayant la facette @ T
      template <class T> T* getParent() const ;
  
      ViewPoint* getViewPoint() const ;

      /// Retrouver une vue dans les fils du mod�le
      Object* getSon(Model::Object* _object) const ;


    // @}


    private:

      /// Traits d'affichage de l'objet
      /*!
        Associe les nom des classes de facettes aux facettes.
        @composite
      */
      std::map<std::string, Trait*> traits ;          
      
      /// L'�ventuel objet qui contient celui-ci
      Object* contener ;

      /// Les objets contenus dans celui-ci
      std::set<Object*> content ;
      
    };


    template <class T>  Object::getTrait<T>() const
    {
      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      /// on attrape la facette 
      Trait* trait = traits[typeid(T).name()] ;
      
      /// si elle existe on effectue la conversion :
      if (trait)
      {
        return static_cast<T*>(trait) ;
      }
      else
      {
        return NULL ;
      }
    }

    template <class T> T* Object::getParent() const
    {
      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(this) ;
      T* trait = iterateur->getTrait<T>() ;
      
      while((! trait) && iterator)
      {
        iterator = iterator->getContener() ;
        if (iterator)
        {
          trait = iterateur->getTrait<T>() ;
        }
      }
      
      return trait ;
      
    }


  }
}


#endif
