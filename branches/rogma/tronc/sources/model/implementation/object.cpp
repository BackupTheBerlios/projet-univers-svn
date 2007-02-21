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
#include <kernel/string.h>

#include <model/exception.h>
#include <model/trait.h>
#include <model/model.h>
#include <model/observer.h>

#include <model/object.h>


namespace ProjetUnivers {
  namespace Model {
    
    Object::~Object()
    {
      for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        delete trait->second ;
      }
      
      for(std::set<Object*>::iterator son = content.begin() ;
          son != content.end() ;
          ++son)
      {
        delete *son ;
      }
      
    }
    
    Object::Object()
    : Kernel::Model(),
      contener(NULL)
    {}

    Object::Object(const Name& _name)
    : Kernel::Model(),name(_name),contener(NULL)
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
      delete _object ;
    }


    void Object::add(Trait* _trait)
    {
      
      check(_trait,Exception("Object::add(Trait*) : _trait is NULL")) ;
      
      Kernel::Log::InternalMessage("Model::Object::add(Trait)#1") ;

      /// erreur si l'objet a déjà une facette de ce type là
      check(traits[typeid(*_trait).name()]==NULL, 
                   Exception("trait already exists")) ;

      Kernel::Log::InternalMessage("Registering :") ;
      Kernel::Log::InternalMessage(typeid(*_trait).name()) ;
      Kernel::Log::InternalMessage("with value :") ;
      Kernel::Log::InternalMessage(toString((int)_trait).c_str()) ;

      _trait->object = this ;
      /// on range les facettes en fonction de leur classe
      traits[typeid(*_trait).name()] = _trait ;

#ifdef _DEBUG          
      std::map<std::string, Trait*>::const_iterator it = traits.find(typeid(*_trait).name()) ;
      if (it != traits.end())
      {
        Kernel::Log::InternalMessage("trait found") ;
        std::pair<std::string, Trait*> temp = *it ;
        Kernel::Log::InternalMessage("trait name = ") ;
        Kernel::Log::InternalMessage(temp.first.c_str()) ;
        
        Kernel::Log::InternalMessage("trait value = ") ;
        Kernel::Log::InternalMessage(toString((int)temp.second).c_str()) ;
        
      }
#endif      

      Kernel::Log::InternalMessage("traits number = ") ;
      Kernel::Log::InternalMessage(toString(traits.size()).c_str()) ;

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
    

  }
}

