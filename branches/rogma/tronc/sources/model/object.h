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

#ifndef _PU_MODEL_OBJECT_H_
#define _PU_MODEL_OBJECT_H_s

#include <typeinfo>

#include <kernel/log.h>
#include <kernel/inherits.h>
#include <kernel/ensemble_composition.h>
#include <kernel/model.h>

#include <model/name.h>

namespace ProjetUnivers {
  namespace Model {
  
    class Trait ;
    
    /// Un objet du jeu.
    class Object : public Kernel::Model {
    public:
  
    /*!
      @name Construction
    */
    // @{
    
      /// Constructeurs.
      Object() ;
      Object(const Name&) ;
    
      ~Object() ;

      /// Ajoute une facette.
      void add(Trait* _trait) ;

      /// Ajoute un objet comme contenu
      /*!
        Les objets peuvent en contenir d'autres.

      */
      Object* add(Object* _content) ;

      /// Supprime un objet.
      void remove(Object*) ;

    // @}
    /*!
      @name Acc�s
    */
    // @{

      Name getName() const ;

      Object* getContener() const ;

      std::set<Object*>::iterator getContent() const ;
  
      /// Le conteneur r�cursif de plus haut niveau.
      Object* getRoot() const ;
      
    // @}
    /*!
      @name Acc�s aux Traits
    */
    // @{

      /// Acc�s r�cursif au plus haut conteneur ayant la facette @ T
      template <class T> Kernel::Association<T> getRoot() const ;

      
      /// Acc�s � la facette T.
      /*!
        T doit �tre une sous classe de Trait.
      */
      template <class T> T* getTrait() const ;

      /// Acc�s r�cursif au premier conteneur ayant la facette @ T
      template <class T> T* getParent() const ;

      /// Acc�s aux facettes de l'objet.
      std::set<Trait*>::iterator getTraits() const ;

    // @}
      

    private:

    
    // @}
    /*!
      @name Attributs
    */
    // @{
       
      /// Name de l'objet.
      /*!
        Pas forc�ment unique.
      */
      Name name ;
    
      /// Les facettes de l'objet
      /*!
        @composite
      */
      std::map<std::string, Trait*> facettes ;

      /// L'�ventuel objet qui contient celui-ci
      Object* contener ;

      /// Les objets contenus dans celui-ci
      /*!
        @composite
      */
      std::set<Object*> content ;

      
    // @}
      
    };  

    template <class T> T* Object::getTrait() const
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
        return NULL ;
    }

    template <class T> T* Object::getParent() const
    {
      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(this) ;
      T* trait(iterator->getTrait<T>()) ;
      
      while((! trait) && iterator)
      {
        iterator = iterator->getContener() ;
        if (iterator)
        {
          trait = iterator->getTrait<T>() ;
        }
      }
      
      return trait ;
      
    }

    template <class T> T* Object::getRoot() const
    {
      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(this) ;
      T* trait(iterator->getTrait<T>()) ;
      
      T* highest_trait_found ;
      
      while(trait && iterator)
      {
        highest_trait_found = trait ;
        
        iterator = iterator->getConteneur() ;
        if (iterator)
        {
          trait = iterator->getTrait<T>() ;
        }
      }
      
      return highest_trait_found ;
      
    }


  } 
  
}


#endif // _PU_MODEL_OBJECT_H_
