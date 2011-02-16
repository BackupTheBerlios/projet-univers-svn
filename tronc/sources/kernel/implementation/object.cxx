/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/relation.h>
namespace ProjetUnivers 
{
  namespace Kernel 
  {
 
    template <class _View> _View* Object::getView(ViewPoint* viewpoint)
    {
      CHECK(viewpoint,"Object::getView error") ;
      TypeIdentifier trait_type = 
        Trait::getTraitTypeOfView(
                    getClassTypeIdentifier(_View), 
                    getObjectTypeIdentifier(viewpoint)) ;
      
      if (trait_type != VoidTypeIdentifier)
      {
        Trait* trait = getTrait(trait_type) ;
        
        if (trait)
        {
          return trait->getView<_View>(viewpoint) ;
        }
      }
      
      return NULL ;
    }

    template <class T> TraitReference<T> Object::getTrait() const
    {
      Kernel::Inherits<T,Trait>() ;
      
      Trait* trait = getTrait(getClassTypeIdentifier(T)) ;
      
      /// if trait exist convert :
      if (trait)
      {
        return TraitReference<T>(static_cast<T*>(trait)) ;
      }
      else
      {
        return TraitReference<T>() ;
      }
    }

    template <class T> TraitReference<T> Object::getParent() const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      TraitReference<T> trait(iterator->getTrait<T>()) ;
      
      while((! trait) && iterator)
      {
        iterator = iterator->getParent() ;
        if (iterator)
        {
          trait = iterator->getTrait<T>() ;
        }
      }
      
      return trait ;
      
    }

    template <class T> TraitReference<T> Object::getAncestor() const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(getParent()) ;
      TraitReference<T> trait ;
      
      while((! trait) && iterator)
      {
        trait = iterator->getTrait<T>() ;
        iterator = iterator->getParent() ;
      }
      
      return trait ;
    }

    template <class T> TraitReference<T> Object::getParentUpTo(const Object* i_object) const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      TraitReference<T> trait(iterator->getTrait<T>()) ;
      
      while((! trait) && iterator && iterator != i_object)
      {
        iterator = iterator->getParent() ;
        if (iterator)
        {
          trait = iterator->getTrait<T>() ;
        }
      }
      
      return trait ;
      
    }

    template <class T> TraitReference<T> Object::getRoot() const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      TraitReference<T> highest_trait_found(iterator->getTrait<T>()) ;
      
      while(highest_trait_found && iterator)
      {
        highest_trait_found = highest_trait_found ;
        
        iterator = iterator->getParent() ;
        if (iterator)
        {
          highest_trait_found = iterator->getTrait<T>() ;
        }
      }
      
      return highest_trait_found ;
      
    }

    template <class _View>
    void Object::apply(const TypeIdentifier& trait_name,
                       ViewPoint* viewpoint,
                       boost::function1<void,_View*> operation)
    {
      Trait* trait = getTrait(trait_name) ;
      
      if (trait)
      {
        _View* view = trait->getView<_View>(viewpoint) ;
        if (view)
        {
          operation(view) ;
        }
      }

      /// recursive
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->apply<_View>(trait_name,viewpoint,operation) ;
      }
      
    }
    
    template <class T> std::set<T*> Object::getDescendants() const
    {
      std::set<T*> result ;
      // get the children
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        T* trait = (*child)->getTrait<T>() ;
        if (trait)
        {
          result.insert(trait) ;
        }      
        // recursive call
        
        std::set<T*> temp = (*child)->getDescendants<T>() ;
        
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    template <class T> std::set<T*> Object::getChildren() const
    {
      std::set<T*> result(getDescendants<T>()) ;

      Object* iterator(const_cast<Object*>(this)) ;
      T* trait(iterator->getTrait<T>()) ;
      
      if (trait)
        result.insert(trait) ;

      return result ;
    }
    
    template <class T> std::set<Object*> Object::getChildrenObjects() const
    {
      std::set<Object*> result ;
      std::set<T*> traits(getChildren<T>()) ;

      for(typename std::set<T*>::const_iterator trait = traits.begin() ; trait != traits.end() ; ++trait)
      {
        result.insert((*trait)->getObject()) ;
      }

      return result ;
    }

    template <class T> TraitReference<T> Object::getChild() const
    {
      std::set<T*> temp(getChildren<T>()) ;
      if (temp.size() == 1)
        return TraitReference<T>(*temp.begin()) ;
      return TraitReference<T>() ;
    }

    template <typename ReturnType>
    ReturnType Object::callFunction(const std::string& function_name) const
    throw (boost::bad_any_cast,std::exception)
    {
      for(std::set<Trait*>::const_iterator trait = m_traits.begin() ;
          trait != m_traits.end() ;
          ++trait)
      {
        std::pair<bool,boost::any> temp(
          (*trait)->callFunction(getObjectTypeIdentifier(*trait),function_name)) ;
        if (temp.first)
        {
          return boost::any_cast<ReturnType>(temp.second) ;
        }
      }
      
      // no function...
      throw std::exception() ;
    }
    
    /// An order on objects. 
    class ObjectOrder : public std::binary_function<const Object*,const Object*,bool> 
    {
    public:
      /// true if x i less than y.
      bool operator()(const Object* x,const Object* y) const
      { 
        if (!x && !y)
          return false ;
        
        if (!x)
          return true ;
          
        if (!y)
          return false ;
        
        return x->getIdentifier() < y->getIdentifier() ;
      }
    };

    template <class _Relation> ObjectReference Object::getUniqueLinked()
    {
      return Relation::getUniqueLinked<_Relation>(this) ;
    }

  }
}
