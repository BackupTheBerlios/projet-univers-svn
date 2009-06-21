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
namespace ProjetUnivers 
{
  namespace Kernel 
  {
 
    template <class _View> _View* Object::getView(ViewPoint* i_viewpoint)
    {
      CHECK(i_viewpoint,"Object::getView error") ;
      TypeIdentifier trait_type = 
        Trait::getTraitTypeOfView(
                    getClassTypeIdentifier(_View), 
                    getObjectTypeIdentifier(i_viewpoint)) ;
      
      if (trait_type != VoidTypeIdentifier)
      {
        Trait* trait = _get(trait_type) ;
        
        if (trait)
        {
          return trait->getView<_View>(i_viewpoint) ;
        }
      }
      
      return NULL ;
    }

    template <class T> T* Object::getTrait() const
    {
      Kernel::Inherits<T,Trait>() ;
      
      Trait* trait = _get(getClassTypeIdentifier(T)) ;
      
      /// if trait exist convert :
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
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* trait(iterator->getTrait<T>()) ;
      
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

    template <class T> T* Object::getAncestor() const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(getParent()) ;
      T* trait = NULL ;
      
      while((! trait) && iterator)
      {
        trait = iterator->getTrait<T>() ;
        iterator = iterator->getParent() ;
      }
      
      return trait ;
    }

    template <class T> T* Object::getParentUpTo(const Object* i_object) const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* trait(iterator->getTrait<T>()) ;
      
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

    template <class T> T* Object::getRoot() const
    {
      // T must be a subclass of Trait
      Kernel::Inherits<T,Trait>() ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      T* highest_trait_found(iterator->getTrait<T>()) ;
      
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
    void Object::apply(const TypeIdentifier& i_trait_name,
                       ViewPoint* i_viewpoint,
                       boost::function1<void,_View*> i_operation)
    {
      Trait* trait = _get(i_trait_name) ;
      
      if (trait)
      {
        _View* view = trait->getView<_View>(i_viewpoint) ;
        if (view)
        {
          i_operation(view) ;
        }
      }

      /// recursive
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->apply<_View>(i_trait_name,i_viewpoint,i_operation) ;
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
    
    template <typename ReturnType>
    ReturnType Object::callFunction(const std::string& function_name) const
    throw (boost::bad_any_cast,std::exception)
    {
      for(std::map<TypeIdentifier,Trait*>::const_iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        std::pair<bool,boost::any> temp(
          trait->second->callFunction(trait->first,function_name)) ;
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

  }
}
