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
#define _PU_MODEL_OBJECT_H_

#include <typeinfo>
#include <map>
#include <set>

#include <kernel/string.h>
#include <kernel/log.h>
#include <kernel/inherits.h>
#include <kernel/model.h>

#include <model/name.h>

namespace ProjetUnivers {
  namespace Model {

    class Observer ;
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

      const std::set<Object*>& getContent() const ;
  
      /// Le conteneur r�cursif de plus haut niveau.
      Object* getRoot() const ;
      
    // @}
    /*!
      @name Acc�s aux Traits
    */
    // @{

      /// Acc�s r�cursif au plus haut conteneur ayant la facette @ T
      template <class T> T* getRoot() const ;

      
      /// Acc�s � la facette T.
      /*!
        T doit �tre une sous classe de Trait.
      */
      template <class T> T* getTrait() ;

      /// Acc�s r�cursif au premier conteneur ayant la facette @ T
      template <class T> T* getParent() const ;

      /// Acc�s aux facettes de l'objet.
      const std::map<std::string, Trait*>& getTraits() const ;

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
      std::map<std::string, Trait*> traits ;

      /// L'�ventuel objet qui contient celui-ci
      Object* contener ;

      /// Les objets contenus dans celui-ci
      /*!
        @composite
      */
      std::set<Object*> content ;

      
    // @}
      
    };  

    template <class T> T* Object::getTrait() 
    {

      Kernel::Log::InternalMessage("Object::getTrait()") ;

      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;

      Kernel::Log::InternalMessage("Asking :") ;
      Kernel::Log::InternalMessage(typeid(T).name()) ;

      /// on attrape la facette 
      Trait* trait = traits[typeid(T).name()] ;
      
      /// si elle existe on effectue la conversion :
      if (trait)
      {
        Kernel::Log::InternalMessage("Trait found") ;
        
        return static_cast<T*>(trait) ;
      }
      else
      {
        Kernel::Log::InternalMessage("Trait not found") ;
        return NULL ;
      }
    }

    template <class T> T* Object::getParent() const
    {
      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
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
      Kernel::Log::InternalMessage("Object::getRoot()") ;

      /// T doit �tre une sous classe de Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* highest_trait_found(iterator->getTrait<T>()) ;
      
      while(highest_trait_found && iterator)
      {
        Kernel::Log::InternalMessage(
          (std::string("highest_trait_found=") 
           + toString((int)highest_trait_found)
           + std::string(" iterator=")
           + toString((int)iterator)).c_str()) ;
          

        highest_trait_found = highest_trait_found ;
        
        iterator = iterator->getContener() ;
        if (iterator)
        {
          highest_trait_found = iterator->getTrait<T>() ;
        }
      }
      
      return highest_trait_found ;
      
    }


  } 
  
}


#endif // _PU_MODEL_OBJECT_H_
