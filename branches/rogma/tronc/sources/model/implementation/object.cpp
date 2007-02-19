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


#include <kernel/log.h>
#include <kernel/error.h>

#include <model/exception.h>
#include <model/object.h>
#include <model/trait.h>
#include <model/model.h>

#include <model/observer.h>


namespace ProjetUnivers {
  namespace Model {
    
    Object::~Object()
    {}
    
    Object::Object()
    : Kernel::Model()
    {}

    Object::Object(const Name& _name)
    : Kernel::Model(),name(_name)
    {}

    Object* Object::add(Object* _object)
    {
      check(_object,Exception("Object::add(Object*) : _object is NULL")) ;

      /// on met à jour le lien contenu/contenant
      _object->contener = this ;
      content.insert(_object) ;
      
      /// On enregistre l'objet dans le modèle
      registerObject(_object) ;
      
      this->notify(Kernel::Event(Kernel::Event::Add,"son",_object)) ;
      
      return _object ;
    }

    void Object::remove(Object* _object)
    {
      this->content.erase(_object) ;
    }


    void Object::add(Trait* _trait)
    {
      
      check(_trait,Exception("Object::add(Trait*) : _trait is NULL")) ;
      
      Kernel::Log::InternalMessage("Model::Object::add(Trait)#1") ;

      /// erreur si l'objet a déjà une facette de ce type là
      check(traits[typeid(*_trait).name()]==NULL, 
                   Exception("trait already exists")) ;


      _trait->object = this ;
      /// on range les facettes en fonction de leur classe
      traits.insert(std::pair<std::string,Trait*>(
                        typeid(*_trait).name(), _trait)) ;

      Kernel::Log::InternalMessage("Model::Object::add(facette)#3") ;
      
      this->notify() ;
    }

    Name Object::getName() const
    {
      return this->name ;
    }

    Object* Object::getContener() const
    {
      return this->contener ;
    }

    const std::set<Object*>& Object::getContent() const
    {
      return this->content ;
    }

    Object* Object::getRoot() const
    {
      if (! this->contener)
      {
        return const_cast<Object*>(this) ;
      }
      else
      {
        return this->contener->getRoot() ;
      }
    }
    
    const std::map<std::string, Trait*>& Object::getTraits() const
    {
      return this->traits ;
    }
    
    /// temp debug
    Observer* Object::getObserverTrait() const
    {
      /// T doit être une sous classe de Trait
      Kernel::Inherits<Observer,Trait>() ;
      
      /// on attrape la facette 
      Trait* trait = (traits.find(typeid(Observer).name()))->second ;
      
      /// si elle existe on effectue la conversion :
      if (trait)
      {
        return static_cast<Observer*>(trait) ;
      }
      else
        return NULL ;
    }


  }
}

