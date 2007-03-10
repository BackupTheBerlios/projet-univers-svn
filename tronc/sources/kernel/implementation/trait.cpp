/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#include <iostream>
#include <kernel/error.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/exception_kernel.h>

#include <kernel/view_point.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/base_trait_view.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Kernel {

    /// static storage
    std::map<std::pair<std::string,std::string>,
             Trait::ViewBuilder>                  Trait::builders ;
 
    std::map<std::pair<std::string,std::string>,
             std::string>                         Trait::m_trait_of_view ;

    Object* Trait::getObject() const
    {
      return object ;
    }

    Trait::~Trait()
    {
      _close() ;
      
      for(std::map<ViewPoint*,BaseTraitView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        delete view->second ;
      }
    }
  
    Trait::Trait()
    : object(NULL)
    {}

    void Trait::_create_views()
    {
      check(object,ExceptionKernel("Trait::_create_views no object")) ;
      check(object->model,
            ExceptionKernel("Trait::_create_views no object's model")) ;
      
      /// we create corresponding views for all viewpoints
      for(std::set<ViewPoint*>::iterator viewpoint = object->model->viewpoints.begin() ;
          viewpoint != object->model->viewpoints.end() ;
          ++viewpoint)
      {
        _create_views(*viewpoint) ;
      }
    }
    
    void Trait::_create_views(ViewPoint* i_viewpoint)
    {
      Log::InternalMessage(
        (std::string("Trait::_create_views ") + typeid(*i_viewpoint).name()).c_str()) ;
      
      if (views.find(i_viewpoint) == views.end())
      {
        /// get the trait's view builder for viewpoint 
        ViewBuilder builder = builders[
                                std::make_pair<std::string,std::string>(
                                  typeid(*i_viewpoint).name(),
                                  typeid(*this).name())] ;
        
        if (! builder.empty())
        {
          /// create the view
          views[i_viewpoint] = builder(this,i_viewpoint) ;
          
          Log::InternalMessage(
            (std::string("added trait view for ") + 
             toString((int)i_viewpoint)).c_str()) ;  
        }
        else
        {
          Log::InternalMessage(
            (std::string("found empty builder for ") + 
            typeid(*i_viewpoint).name() + " " + 
            typeid(*this).name()
            ).c_str()) ;  
          
        }
      }
      else
      {
          Log::InternalMessage(
            (std::string("already has view for viewpoint ") + 
             toString((int)i_viewpoint)).c_str()) ;  
      }
    }
    
    void Trait::_init(ViewPoint* i_viewpoint)
    {
      if (views.find(i_viewpoint) != views.end())
      {
        views[i_viewpoint]->_init() ;
      }
    }
    
    void Trait::_init()
    {
      check(object,ExceptionKernel("Trait::_init no object")) ;
      
      /// 2. we init all the views not yet initialised
      for(std::map<ViewPoint*,BaseTraitView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        view->second->_init() ;
      }
    }
    
    void Trait::_close()
    {
      for(std::map<ViewPoint*,BaseTraitView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        view->second->_close() ;
      }
    }

    void Trait::_close(ViewPoint* i_viewpoint)
    {
      if (views.find(i_viewpoint) != views.end())
      {
        views[i_viewpoint]->_close() ;
      }
    
    }
    
    void Trait::_changed_parent(Object* i_old_parent)
    {
      for(std::map<ViewPoint*,BaseTraitView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        view->second->_changed_parent(i_old_parent) ;
      }
    }
    
    void Trait::_updated()
    {
      for(std::map<ViewPoint*,BaseTraitView*>::iterator view = views.begin() ;
          view != views.end() ;
          ++view)
      {
        view->second->_updated() ;
      }
    }

    void Trait::registerBuilder(const std::string& _trait,
                                const std::string& _viewpoint,
                                ViewBuilder _builder)
    {
      std::cout << "Registering constructor for " 
                << _viewpoint << " " << _trait << std::endl ;

      builders[std::make_pair<std::string,std::string>
                (_viewpoint,_trait)] = _builder ;

      std::cout << "Registered constructor" << std::endl ;
      
    }

    void Trait::registerMapping(const std::string& i_view,
                                const std::string& i_viewpoint,
                                const std::string& i_trait)
    {
      m_trait_of_view[
        std::make_pair<std::string,std::string>(
          i_view,i_viewpoint)]
        = i_trait ;
    }
 

    void Trait::notify()
    {
      _updated() ;
    }

  }
}
