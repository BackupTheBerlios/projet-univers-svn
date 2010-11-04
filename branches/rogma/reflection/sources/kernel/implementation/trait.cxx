/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <boost/bind.hpp>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    /// For static registration of readers. 
    class TraitReaderRegistration
    {
    public:
      
      TraitReaderRegistration(const std::string& name,Trait::ReaderFunction reader) 
      {
        Trait::_registerReader(name,reader) ;
      }
    };

    /// Register a view.
    template <class _Trait,class _ViewPoint,class _View> 
    class ViewRegistration
    {
    public:
      
      /// Constructor.
      /*!
        This constructor is called at the module init because of the variable 
        declaration in macro RegisterView. 
        
        The internal C++ classes names is used as a registering key for 
        builder.
        
        It also register mapping from ViewXViewPoint to Trait
      */
      ViewRegistration(Trait::ViewBuilder builder)
      {
        
        Kernel::Trait::registerBuilder(getClassTypeIdentifier(_Trait),
                                       getClassTypeIdentifier(_ViewPoint),
                                       builder) ;
        Kernel::Trait::registerMapping(getClassTypeIdentifier(_View),
                                       getClassTypeIdentifier(_ViewPoint),
                                       getClassTypeIdentifier(_Trait)) ;
                                        
      }
    };
    
    /// Register a controler.
    template <class _Trait, class _ControlerSet, class _Controler> 
    class ControlerRegistration
    {
    public:
      
      /// Constructor.
      /*!
        This constructor is called at the module init because of the variable 
        declaration in macro RegisterControler. 
        
        The internal C++ classes names is used as a registering key for 
        builder.
        
        It also register mapping from ControlerXControlerSet to Trait
      */
      ControlerRegistration(Trait::ControlerBuilder builder)
      {
        
        Kernel::Trait::registerControler(getClassTypeIdentifier(_Trait),
                                         getClassTypeIdentifier(_ControlerSet),
                                         builder) ;

        Kernel::Trait::registerControlerMapping(
                                       getClassTypeIdentifier(_Controler),
                                       getClassTypeIdentifier(_ControlerSet),
                                       getClassTypeIdentifier(_Trait)) ;
                                        
      }
    };
    

    /// Register a command.
    template <class _Trait> class CommandRegistration
    {
    public:
      
      /// Constructor.
      CommandRegistration(const std::string&             i_command_name,
                          boost::function1<void,_Trait*> i_operation)
      {
        
        Kernel::Trait::addCommand<_Trait>(i_command_name,
                                          i_operation) ;
      }
    };
    
    /// Register an axis.
    template <class _Trait> class AxisRegistration
    {
    public:
      
      /// Constructor.
      AxisRegistration(const std::string&                 axis_name,
                       const std::string&                 axis_group_name,
                       boost::function2<void,_Trait*,int> operation)
      {
        
        Kernel::Trait::addAxis<_Trait>(axis_name,
                                       axis_group_name,
                                       operation) ;
      }
    };
    
    /// Register a function.
    template <class _Trait> class FunctionRegistration
    {
    public:
      
      /// Constructor.
      FunctionRegistration(const std::string&                   function_name,
                           boost::function1<boost::any,_Trait*> function)
      {
        
        Kernel::Trait::addFunction<_Trait>(function_name,
                                           function) ;
      }
    };
    
    
    template<class View> View* Trait::getView(ViewPoint* i_viewpoint)
    {
      std::multimap<ViewPoint*,BaseTraitView*>::const_iterator
        finder = m_views.lower_bound(i_viewpoint) ;
      
      if (finder != m_views.end() && finder->first == i_viewpoint) 
      {
        std::multimap<ViewPoint*,BaseTraitView*>::const_iterator
          last = m_views.upper_bound(i_viewpoint) ;
        
        while(finder != last)
        {
          View* candidate = dynamic_cast<View*>(finder->second) ;
          if (candidate)
          {
            return candidate ;
          }
          ++finder ;
        }
      }
      return NULL ;
    }

    template<class _Controler> 
    _Controler* Trait::getControler(ControlerSet* controler_set)
    {
      std::multimap<ControlerSet*,BaseControler*>::const_iterator 
        finder = m_controlers.lower_bound(controler_set) ;
      
      if (finder != m_controlers.end()) 
      {
        std::multimap<ControlerSet*,BaseControler*>::const_iterator
          end = m_controlers.upper_bound(controler_set) ;
        for (std::multimap<ControlerSet*,BaseControler*>::const_iterator controller = finder ; controller != end ; ++controller)
        {
          _Controler* result = dynamic_cast<_Controler*>(controller->second) ;
          if (result)
            return result ;
        }
      }
      return NULL ;
    }

    template <class SpecializedTrait> 
    SpecializedTrait* convert(Trait* i_trait)
    {
      return dynamic_cast<SpecializedTrait*>(i_trait) ;
    }

    template <class SpecializedTrait>
    void Trait::addCommand(
      const std::string&                       i_command_name,
      boost::function1<void,SpecializedTrait*> i_operation)
    {
      StaticStorage::get()
      ->m_void_commands[getClassTypeIdentifier(SpecializedTrait)]
                       [i_command_name] 
        = boost::bind(i_operation, boost::bind(&convert<SpecializedTrait>, _1)) ;
    }
  
    template <class SpecializedTrait>
    void Trait::addAxis(
      const std::string&                           axis_name,
      const std::string&                           axis_group_name,
      boost::function2<void,SpecializedTrait*,int> axis_update)
    {
      StaticStorage::get()
      ->m_int_commands[getClassTypeIdentifier(SpecializedTrait)][axis_name]
        = boost::bind(axis_update, boost::bind(&convert<SpecializedTrait>, _1),_2) ;
      StaticStorage::get()->m_axes_group_to_axes.insert(std::pair<std::string,std::string>(axis_group_name,axis_name)) ;
    }

    template <class SpecializedTrait> void Trait::addFunction(
          const std::string&                             function_name,
          boost::function1<boost::any,SpecializedTrait*> function)
    {
      StaticStorage::get()
      ->m_functions[getClassTypeIdentifier(SpecializedTrait)][function_name]
        = boost::bind(function, boost::bind(&convert<SpecializedTrait>, _1)) ;
    }

  }
}
