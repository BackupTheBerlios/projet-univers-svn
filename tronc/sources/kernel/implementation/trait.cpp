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
#include <iostream>
#include <kernel/error.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/exception_kernel.h>
#include <kernel/base_trait_reference.h>

#include <kernel/base_controler.h>
#include <kernel/controler_set.h>
#include <kernel/view_point.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/base_trait_view.h>
#include <kernel/deduced_trait.h>
#include <kernel/reader.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Kernel {

    /// static storage
    std::multimap<
        TypeIdentifier,
        std::pair<TypeIdentifier,Trait::ViewBuilder> > Trait::m_view_builders ;
 
    std::map<std::pair<TypeIdentifier,TypeIdentifier>,
             TypeIdentifier>                         Trait::m_trait_of_view ;

    std::multimap<
      TypeIdentifier,
      std::pair<TypeIdentifier,Trait::ControlerBuilder> > Trait::m_controler_builders ;
      
    std::map<std::pair<TypeIdentifier,TypeIdentifier>,
             TypeIdentifier>                 Trait::m_trait_of_controler ;


    Object* Trait::getObject() const
    {
      return object ;
    }

    Trait::~Trait()
    {
      _close() ;
      
      for(std::set<BaseTraitReference*>::iterator reference = m_references.begin() ;
          reference != m_references.end() ;
          ++reference)
      {
        (*reference)->_reset() ;
      }
      
      InternalMessage("Kernel","Trait::~Trait destroying " + toString(m_views.size()) + " views") ;
      m_destroying = true ;
      
      
      for(std::multimap<ViewPoint*,BaseTraitView*>::iterator view = m_views.begin() ;
          view != m_views.end() ;
          ++view)
      {
        InternalMessage("Kernel","Trait::~Trait destroying a view") ;
        CHECK(view->second,"Trait::~Trait no view") ;
        delete view->second ;
      }

      InternalMessage("Kernel","Trait::~Trait destroying controlers") ;

      for(std::multimap<ControlerSet*,BaseControler*>::iterator controler = m_controlers.begin() ;
          controler != m_controlers.end() ;
          ++controler)
      {
        delete controler->second ;
      }

    }
  
    Trait::Trait()
    : object(NULL),
      m_destroying(false),
      m_views(),
      m_controlers()
    {}

    void Trait::_remove_view(ViewPoint* i_viewpoint,BaseTraitView* i_view)
    {
      if (m_destroying)
      {
        return ;
      }
      
      std::multimap<ViewPoint*,BaseTraitView*>::iterator
        finder = m_views.lower_bound(i_viewpoint) ;
      
      while (finder != m_views.end() && finder->first == i_viewpoint)
      {
        if (finder->second == i_view)
        {
          m_views.erase(finder) ;
          return ;
        }
        ++finder ;
      }
    }
    
    void Trait::_remove_controler(ControlerSet* i_controler_set,BaseControler* i_controler)
    {
      if (m_destroying)
      {
        return ;
      }
      
      std::multimap<ControlerSet*,BaseControler*>::iterator
        finder = m_controlers.lower_bound(i_controler_set) ;
      
      while (finder != m_controlers.end() && finder->first == i_controler_set)
      {
        if (finder->second == i_controler)
        {
          m_controlers.erase(finder) ;
          return ;
        }
        ++finder ;
      }
    }

    void Trait::_create_views()
    {
      CHECK(object,ExceptionKernel("Trait::_create_views no object")) ;
      CHECK(object->getModel(),
            ExceptionKernel("Trait::_create_views no object's model")) ;
      
      /// we create corresponding views for all viewpoints
      for(std::set<ViewPoint*>::iterator viewpoint = object->getModel()->m_viewpoints.begin() ;
          viewpoint != object->getModel()->m_viewpoints.end() ;
          ++viewpoint)
      {
        _create_views(*viewpoint) ;
      }
    }
    
    void Trait::_create_views(ViewPoint* i_viewpoint)
    {
      InternalMessage("Kernel",
        "Trait::_create_views " + getObjectTypeIdentifier(i_viewpoint).toString() + " entering") ;
      
      /// nothing to do if we already have views associated with that viewpoint
      if (m_views.find(i_viewpoint) == m_views.end())
      {
        
        TypeIdentifier viewpointType(getObjectTypeIdentifier(i_viewpoint)) ;

        /// search for builders on that viewpoint
        std::multimap<TypeIdentifier,
                      std::pair<TypeIdentifier,ViewBuilder> >::const_iterator
          finder = m_view_builders.lower_bound(viewpointType) ;
        
        
        if (finder != m_view_builders.end() && finder->first == viewpointType)
        {
          std::multimap<TypeIdentifier,
                        std::pair<TypeIdentifier,ViewBuilder> >::const_iterator
            last = m_view_builders.upper_bound(viewpointType) ;
          
          /// apply builder for each trait this belongs
          while(finder != last)
          {
            
            if (finder->second.first.isInstance(this))
            {
              BaseTraitView* view = finder->second.second(this,i_viewpoint) ;
              m_views.insert(std::pair<ViewPoint*,BaseTraitView*>(
                              i_viewpoint,view)) ;

              InternalMessage("Kernel",
                "added trait view for viewpoint : " + viewpointType.toString()
                + " trait : " + getObjectTypeIdentifier(this).toString()
                + " view : " + getObjectTypeIdentifier(view).toString()) ;  

            }
            ++finder ;
          }
        }
      }
      else
      {
          InternalMessage("Kernel",
            (std::string("already has view for viewpoint ") + 
             toString((int)i_viewpoint)).c_str()) ;  
      }
      InternalMessage("Kernel",
        "Trait::_create_views " + getObjectTypeIdentifier(i_viewpoint).toString() + " leaving") ;
    }

    void Trait::_create_controlers(ControlerSet* i_controler_set)
    {
      InternalMessage("Kernel",
        (std::string("Trait::_create_controlers ") + 
         getObjectTypeIdentifier(i_controler_set).toString())) ;

      /// nothing to do if we already have controlers associated with that controler set
      if (m_controlers.find(i_controler_set) == m_controlers.end())
      {
        
        TypeIdentifier controlersetType(getObjectTypeIdentifier(i_controler_set)) ;

        /// search for builders on that controler set
        std::multimap<TypeIdentifier,
                      std::pair<TypeIdentifier,ControlerBuilder> >::const_iterator
          finder = m_controler_builders.lower_bound(controlersetType) ;
        
        
        if (finder != m_controler_builders.end() && finder->first == controlersetType)
        {
          std::multimap<TypeIdentifier,
                        std::pair<TypeIdentifier,ControlerBuilder> >::const_iterator
            last = m_controler_builders.upper_bound(controlersetType) ;
          
          /// apply builder for each trait this belongs
          while(finder != last)
          {
            
            if (finder->second.first.isInstance(this))
            {
              BaseControler* controler = finder->second.second(this,i_controler_set) ;
              m_controlers.insert(std::pair<ControlerSet*,BaseControler*>(
                                     i_controler_set,controler)) ;

              InternalMessage("Kernel",
                "added trait controler for controler set : " + controlersetType.toString()
                + " trait : " + getObjectTypeIdentifier(this).toString()
                + " controelr : " + getObjectTypeIdentifier(controler).toString()) ;  

            }
            ++finder ;
          }
        }
      }
      else
      {
          InternalMessage("Kernel",
            (std::string("already has controler for controelr set ") + 
             toString((int)i_controler_set)).c_str()) ;  
      }
    }
      
    void Trait::_create_controlers()
    {
      CHECK(object,ExceptionKernel("Trait::_create_controlers no object")) ;
      CHECK(object->getModel(),
            ExceptionKernel("Trait::_create_controlers no object's model")) ;
      
      /// we create corresponding controler for all controler sets
      for(std::set<ControlerSet*>::iterator controler_set 
              = object->getModel()->m_controler_sets.begin() ;
          controler_set != object->getModel()->m_controler_sets.end() ;
          ++controler_set)
      {
        _create_controlers(*controler_set) ;
      }
    }
    
    void Trait::_init(ViewPoint* i_viewpoint)
    {
      std::multimap<ViewPoint*,BaseTraitView*>::iterator 
        view = m_views.lower_bound(i_viewpoint) ;
      std::multimap<ViewPoint*,BaseTraitView*>::iterator 
        last = m_views.upper_bound(i_viewpoint) ;
      
      while (view != m_views.end() && view != last && view->first == i_viewpoint)
      {
        view->second->_init() ;
        ++view ;
      }
    }

    void Trait::_init(ControlerSet* i_controler_set)
    {
      std::multimap<ControlerSet*,BaseControler*>::iterator 
        controler = m_controlers.lower_bound(i_controler_set) ;
      std::multimap<ControlerSet*,BaseControler*>::iterator 
        last = m_controlers.upper_bound(i_controler_set) ;
      
      while (controler != m_controlers.end() && controler != last && controler->first == i_controler_set)
      {
        controler->second->_init() ;
        ++controler ;
      }
    }
    
    void Trait::_init()
    {
      CHECK(object,ExceptionKernel("Trait::_init no object")) ;
      
      /// we init all the views not yet initialised
      for(std::multimap<ViewPoint*,BaseTraitView*>::iterator view = m_views.begin() ;
          view != m_views.end() ;
          ++view)
      {
        view->second->_init() ;
      }

      /// we init all the controlers not yet initialised
      for(std::multimap<ControlerSet*,BaseControler*>::iterator controler = m_controlers.begin() ;
          controler != m_controlers.end() ;
          ++controler)
      {
        controler->second->_init() ;
      }

    }
    
    void Trait::_close()
    {
      InternalMessage("Kernel","Trait::_close entering") ;
      InternalMessage("Kernel","Trait::_close closing " + toString(m_views.size()) + " views") ;
      
      for(std::multimap<ViewPoint*,BaseTraitView*>::iterator view = m_views.begin() ;
          view != m_views.end() ;
          ++view)
      {
        view->second->_close() ;
      }

      InternalMessage("Kernel","Trait::_close closing " + toString(m_controlers.size()) + " controlers") ;

      for(std::multimap<ControlerSet*,BaseControler*>::iterator controler = m_controlers.begin() ;
          controler != m_controlers.end() ;
          ++controler)
      {
        controler->second->_close() ;
      }
      
      InternalMessage("Kernel","Trait::_close leaving") ;
    }

    void Trait::_close(ViewPoint* i_viewpoint)
    {
      std::multimap<ViewPoint*,BaseTraitView*>::iterator 
        view = m_views.lower_bound(i_viewpoint) ;
      std::multimap<ViewPoint*,BaseTraitView*>::iterator 
        last = m_views.upper_bound(i_viewpoint) ;
      
      while (view != m_views.end() && view != last && view->first == i_viewpoint)
      {
        view->second->_close() ;
        ++view ;
      }
    }
    
    void Trait::_close(ControlerSet* i_controler_set)
    {
      std::multimap<ControlerSet*,BaseControler*>::iterator 
        controler = m_controlers.lower_bound(i_controler_set) ;
      std::multimap<ControlerSet*,BaseControler*>::iterator 
        last = m_controlers.upper_bound(i_controler_set) ;
      
      while (controler != m_controlers.end() && controler != last && controler->first == i_controler_set)
      {
        controler->second->_close() ;
        ++controler ;
      }
    }
    
    void Trait::_changed_parent(Object* i_old_parent)
    {
      for(std::multimap<ViewPoint*,BaseTraitView*>::iterator view = m_views.begin() ;
          view != m_views.end() ;
          ++view)
      {
        view->second->_changed_parent(i_old_parent) ;
      }

      for(std::multimap<ControlerSet*,BaseControler*>::iterator controler = m_controlers.begin() ;
          controler != m_controlers.end() ;
          ++controler)
      {
        controler->second->_changed_parent(i_old_parent) ;
      }

    }
    
    void Trait::_updated()
    {
      for(std::multimap<ViewPoint*,BaseTraitView*>::iterator view = m_views.begin() ;
          view != m_views.end() ;
          ++view)
      {
        view->second->_updated() ;
      }

      for(std::multimap<ControlerSet*,BaseControler*>::iterator controler = m_controlers.begin() ;
          controler != m_controlers.end() ;
          ++controler)
      {
        controler->second->_updated() ;
      }

    }

    void Trait::registerBuilder(const TypeIdentifier& _trait,
                                const TypeIdentifier& _viewpoint,
                                ViewBuilder _builder)
    {
      m_view_builders.insert(
        std::pair<TypeIdentifier,std::pair<TypeIdentifier,ViewBuilder> >
          (_viewpoint, 
           std::pair<TypeIdentifier,ViewBuilder>(
             _trait,_builder))) ;

    }

    const TypeIdentifier& Trait::getTraitName(const TypeIdentifier& i_view,
                                              const TypeIdentifier& i_viewpoint)
    {
      std::map<std::pair<TypeIdentifier,TypeIdentifier>,
               TypeIdentifier>::const_iterator        
         trait = m_trait_of_view.find(std::make_pair<TypeIdentifier,TypeIdentifier>(
                                                     i_view,i_viewpoint)) ;
      
      if (trait != m_trait_of_view.end())
      {
        return trait->second ;
      }
      
      return VoidTypeIdentifier ;
    }

    void Trait::registerMapping(const TypeIdentifier& i_view,
                                const TypeIdentifier& i_viewpoint,
                                const TypeIdentifier& i_trait)
    {
      m_trait_of_view.insert(
      std::pair<std::pair<TypeIdentifier,TypeIdentifier>,TypeIdentifier>
      (std::pair<TypeIdentifier,TypeIdentifier>(i_view,i_viewpoint),i_trait)) ;
      
    }

    void Trait::registerControler(const TypeIdentifier& i_trait_class,
                                  const TypeIdentifier& i_controler_set_class,
                                  ControlerBuilder      i_builder)
    {
      m_controler_builders.insert(
        std::pair<TypeIdentifier,std::pair<TypeIdentifier,ControlerBuilder> >
          (i_controler_set_class, 
           std::pair<TypeIdentifier,ControlerBuilder>(
             i_trait_class,i_builder))) ;
    }

    void Trait::registerControlerMapping(const TypeIdentifier& i_controler_class,
                                         const TypeIdentifier& i_controler_set_class,
                                         const TypeIdentifier& i_trait_class)
    {
      m_trait_of_controler.insert(
      std::pair<std::pair<TypeIdentifier,TypeIdentifier>,TypeIdentifier>
      (std::pair<TypeIdentifier,TypeIdentifier>(i_controler_class,i_controler_set_class),i_trait_class)) ;
    }
 
    void Trait::notify()
    {
      _updated() ;
      TraitFormula::updateTrait(getObject(),getObjectTypeIdentifier(this)) ;
    }

    void Trait::apply(
      ControlerSet*                         i_controler_set,
      boost::function1<void,BaseControler*> i_operation)
    {
      std::multimap<ControlerSet*,BaseControler*>::iterator 
        finder = m_controlers.find(i_controler_set) ;
      if (finder != m_controlers.end())
      {
        i_operation(finder->second) ;
      }
      
    }

    TypeIdentifier Trait::getTraitTypeOfView(const TypeIdentifier& i_view_type,
                                             const TypeIdentifier& i_viewpoint_type)
    {
      std::map<std::pair<TypeIdentifier,TypeIdentifier>,
               TypeIdentifier>::const_iterator trait_identifier =  
        m_trait_of_view.find(std::pair<TypeIdentifier,TypeIdentifier>(
                   i_view_type, i_viewpoint_type)) ;
      if (trait_identifier != m_trait_of_view.end())
      {
        return trait_identifier->second ;
      }
      return VoidTypeIdentifier ;
    }


    bool Trait::call(const TypeIdentifier& i_trait_type,
                     const std::string&    i_command)
    {
      
      std::map<TypeIdentifier,
               std::map<std::string,
                        boost::function1<void,Trait*> > >::const_iterator 
        group = m_void_commands.find(i_trait_type) ;
      
      if (group != m_void_commands.end())
      {
        std::map<std::string,boost::function1<void,Trait*> >::const_iterator 
          command = group->second.find(i_command) ;
        if (command != group->second.end())
        {
          command->second(this) ;
          return true ;
        }
        else
        {
          return false ;
        }
      }
      else
      {
        return false ;
      }
    }

    bool Trait::call(const TypeIdentifier& i_trait_type,
                     const std::string&    i_command, 
                     const int&            i_parameter)
    {
      std::map<TypeIdentifier,
               std::map<std::string,
                        boost::function2<void,Trait*,int> > >::const_iterator
        group = m_int_commands.find(i_trait_type) ;
      
      if (group != m_int_commands.end())
      {
        std::map<std::string,boost::function2<void,Trait*,int> >::const_iterator 
          command = group->second.find(i_command) ;
        if (command != group->second.end())
        {
          command->second(this,i_parameter) ;
          return true ;
        }
        else
        {
          return false ;
        }
      }
      else
      {
        return false ;
      }
    }

    std::set<std::string> Trait::getCommands() const
    {
      TypeIdentifier trait_type = getObjectTypeIdentifier(this) ;
      std::set<std::string> result ;
      {      
        std::map<TypeIdentifier,
                 std::map<std::string,
                          boost::function1<void,Trait*> > >::const_iterator 
          group = m_void_commands.find(trait_type) ;
        
        if (group != m_void_commands.end())
        {
          for(std::map<std::string,boost::function1<void,Trait*> >::const_iterator
                command = group->second.begin() ;
              command != group->second.end() ;
              ++command)
          {
            result.insert(command->first) ;
          }
        }
      }
      {
        std::map<TypeIdentifier,
                 std::map<std::string,
                          boost::function2<void,Trait*,int> > >::const_iterator
          group = m_int_commands.find(trait_type) ;
        
        if (group != m_int_commands.end())
        {
          
          for(std::map<std::string,boost::function2<void,Trait*,int> >::const_iterator
                command = group->second.begin() ;
              command != group->second.end() ;
              ++command)
          {
            result.insert(command->first) ;
          }
        }
      }      
      return result ;
    }

    std::map<TypeIdentifier,
             std::map<std::string,
                      boost::function1<void,Trait*> > > 
      Trait::m_void_commands ;
  
    std::map<TypeIdentifier,
             std::map<std::string,
                      boost::function2<void,Trait*,int> > > 
      Trait::m_int_commands ;

    void Trait::_registerReference(BaseTraitReference* reference)
    {
      m_references.insert(reference) ;
    }

    void Trait::_unregisterReference(BaseTraitReference* reference)
    {
      m_references.erase(reference) ;
    }

    std::map<std::string,Trait::ReaderFunction> Trait::m_readers ;

    void Trait::_registerReader(const std::string& name,ReaderFunction reader)
    {
      m_readers[name] = reader ;
    }
    
    Trait* Trait::read(Reader* reader)
    {
      if (reader && reader->isBeginNode() && reader->isTraitNode())
      {
        std::map<std::string,Trait::ReaderFunction>::const_iterator 
          finder = m_readers.find(reader->getTraitName()) ;
        
        if (finder != m_readers.end())
        {
          return finder->second(reader) ;
        }
        else
        {
          while (!reader->isEndNode() && reader->processNode())
          {
            if (reader->isTraitNode())
            {
              Trait::read(reader) ;
            }
          }
          reader->processNode() ;
        }
      }
      return NULL ; 
    }
  }
}
