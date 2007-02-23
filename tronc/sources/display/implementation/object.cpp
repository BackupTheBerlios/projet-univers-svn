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


#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/string.h>

#include <display/exception.h>
#include <display/view_point.h>

#include <display/object.h>


namespace ProjetUnivers {
  namespace Display {


    /*!
      @name Construction
    */
    // @{

      /// Constructeur.
      Object::Object(Model::Object* _object, 
                     ViewPoint* _viewPoint)
      : Kernel::View<Model::Object>(_object),contener(NULL)
      {
        Kernel::Log::InternalMessage("Entering Display::Object::Object") ;
        _object->addView((Kernel::Implementation::BaseView*)this) ;
        this->viewPoint = _viewPoint ;

        Kernel::Log::InternalMessage("Leaving Display::Object::Object") ;
      }
          
      /// Initialise les facettes de la vue puis ses fils
      void Object::init() 
      {

        Kernel::Log::InternalMessage(
            (std::string("Entering Object::init for ") 
             + std::string(this->observed->getName())).c_str()) ;
             
        Kernel::Log::InternalMessage(
            (std::string("Initialising ") 
             + toString(traits.size())
             + std::string(" traits")).c_str()) ; 

        for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          (*trait).second->init() ;
        }

        Kernel::Log::InternalMessage(
            (std::string("Initialising ") 
             + toString(content.size())
             + std::string(" sub-objects")).c_str()) ; 
        
        for(std::set<Object*>::iterator son = content.begin() ;
            son != content.end() ;
            ++son)
        {
          (*son)->init() ;
        }
        Kernel::Log::InternalMessage("Leaving Object::init") ;
      }
      
      void Object::close()
      {
        
      }


      Object::~Object()
      {
        for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          delete (*trait).second ;
        }
        
      }
    
      void Object::update(const Kernel::Event& _event)
      {
        /// il faut voir si de nouvelles facettes sont apparues

        /// il faut regarder si les liens de parentés ont changés
        if (_event.name == "son") 
        {
          switch(_event.action)
          {
          case Kernel::Event::Add :
          {
            Model::Object* new_object = 
                dynamic_cast<Model::Object*>(_event.parameter) ;
            
            Object* new_view(  
              this->add(this->getViewPoint()->buildView(new_object))) ;
            
            new_view->init() ;
                          
          }          
          break ;
          case Kernel::Event::Delete :
          {
            /// le paramètre a déjà été supprimé...
            Model::Object* suppressed(
              dynamic_cast<Model::Object*>(_event.parameter)) ;

            /// récupérer la vue correspondant à cet
            /// .... todo.... 
          }          
          break ;
          default:
            break ;
          }
        }
      }


      Object* Object::add(Object* _content)
      {
        if (_content)
        {
          _content->contener = this ;
          this->content.insert(_content) ;
        }

        return _content ;
      }
    
      Trait* Object::add(Trait* _trait)
      {
        
        /// erreur si l'objet a déjà une facette de ce type là
        check(traits[typeid(*_trait).name()]==NULL, 
              Exception("facette déjà existante")) ;
        
        Kernel::Log::InternalMessage(std::string("registering facette ") + 
            typeid(*_trait).name()) ;
        
        _trait->object = this ;
        _trait->viewPoint = this->viewPoint ;
        
        
        /// on range les facettes en fonction de leur classe
        traits[typeid(*_trait).name()] = _trait ;
        
        return _trait ;
      }
      
      void Object::remove(Object* _object)
      {
        if (content.erase(_object) != 0)
        {
          delete _object ;
        }
      }
      
      void Object::remove(Trait* _trait)
      {
        if (_trait)
        {
          Kernel::Log::InternalMessage(typeid(*_trait).name()) ;
          _trait->close() ;
          this->traits.erase(typeid(*_trait).name()) ;
          delete _trait ;
        }
      }
      
 
 
      /// get au conteneur de la vue
      Object* Object::getContener() const
      {
        return this->contener ;
      }
 
      ViewPoint* Object::getViewPoint() const
      {
        return static_cast<ViewPoint*>(viewPoint);
      }

      Object* Object::getSon(Model::Object* _object) const
      {
        for(std::set<Object*>::iterator son = content.begin() ;
            son != content.end() ;
            ++son)
        {
          if ((*son)->getModel() == _object)
          {
            return *son ;
          }
        }
        
        throw Exception("Object::getSon : not found") ;        
       }

      std::string Object::print() const
      {
        Kernel::Log::InternalMessage("Entering Display::Object::print") ;
        std::string result("\n") ;
        result = "Object " + std::string(this->observed->getName()) + "=\n" ;
        
        result += "number of traits:" ;
        result += toString(traits.size()) ;
        result += "=\n" ;
        
        result += "number of sons:" ;
        result += toString(content.size()) ;
        result += "=\n" ;
        
        for(std::set<Object*>::iterator son = content.begin() ;
            son != content.end() ;
            ++son)
        {
          result += (*son)->print() ;
        }        
        
        result += "End object" ;
        result += std::string(this->observed->getName()) ;
        result += "\n" ;

        Kernel::Log::InternalMessage("Leaving Display::Object::print") ;
        
        return result ;
      }

 
  }
}

