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

#include <model/trait.h>
#include <model/object.h>
#include <model/positionned.h>

#include <display/exception.h>
#include <display/object.h>
#include <display/view_point.h>
#include <display/implementation/ogre/view_point.h>


namespace ProjetUnivers {
  namespace Display {


    /// Stockage de la variable statique
    std::map<std::pair<std::string,std::string>,
             ViewBuilder> ViewPoint::builders ;
 

    /*!
      La partie commune à tous les points de vues.
    
    */

    ViewPoint::ViewPoint(Model::Object* _observer)
    : Kernel::ViewPoint(), observer(_observer), initialised(false)
    {}

    ViewPoint::~ViewPoint()
    {}


    void ViewPoint::build()
    {
      /*! 
        On parcours tous les objets du modèle en partant de l'ancètre de 
        l'observateur et on ne construit que ce qui est visible.
        
        Dès qu'un objet est invisible, on ne parcours pas ses fils.
      */

      Kernel::Log::InternalMessage("Entering Display::ViewPoint::build()") ;
      
      Model::Positionned* ancetrePositionne = 
                  this->observer->getRoot<Model::Positionned>() ;

      if (ancetrePositionne)
      {
        this->add(buildView(ancetrePositionne->getObject())) ;
      }
      
      Kernel::Log::InternalMessage("Leaving Display:ViewPoint::build()") ;
      
      
    }

    Object* ViewPoint::buildView(Model::Object* _model)
    {

      Kernel::Log::InternalMessage("Entering Display::ViewPoint::buildView(Model::Object*)") ;
      
      Object* result ;
      
      if (this->isVisible(_model))
      {
        Kernel::Log::InternalMessage("building View Object") ;

        /// On construit l'objet
        result = new Object(_model,this) ;

        Kernel::Log::InternalMessage("built View Object") ;
        
        /// On mémorise l'observateur
        if (_model == this->observer)
        {
          this->observerView = result ;
        }

        Kernel::Log::InternalMessage("building View Traits") ;
        
        /// ses facettes
        for (std::map<std::string, Model::Trait*>::const_iterator trait
                =_model->getTraits().begin() ; 
             trait != _model->getTraits().end() ;
             ++trait)
        {
          Kernel::Log::InternalMessage("searching constructor for " + std::string(typeid(*this).name()) + " " +  typeid(*trait->second).name()) ;
                
          ViewBuilder builder = 
            builders[std::make_pair<std::string,std::string>(
                typeid(*this).name(),typeid(*trait->second).name())] ;

          if (! builder.empty())
          {
            result->add(builder(trait->second)) ;
          }
          else
          {
            Kernel::Log::InternalMessage(
              "in Display::ViewPoint::buildView : empty builder for " 
              + std::string(typeid(*this).name()) + " " 
              +  typeid(*trait->second).name()) ;
          }            
          
          
        }
        
        /// On construit ses composants visibles
        for (std::set<Model::Object*>::iterator 
                                  son = _model->getContent().begin() ;
             son != _model->getContent().end() ;
             ++son)
        {
          if (this->isVisible(*son) == true)
          {
            result->add(this->buildView(*son)) ;
          }
        }
      }

      Kernel::Log::InternalMessage("Leaving Display::ViewPoint::buildView(Model::Object*)") ;
      
      return result ;
    }



    ViewPoint* ViewPoint::build(Model::Object* _observer)
    {
      
      Kernel::Log::InternalMessage("Entering Display::ViewPoint::build(Model::Object*)") ;
      
      /// implantation à l'aide de Ogre
      ViewPoint* result(
          new Implementation::Ogre::ViewPoint(_observer)) ;
      
      result->build() ;

      Kernel::Log::InternalMessage("Leaving Display::ViewPoint::build(Model::Object*)") ;
      
      return result ;

    }

    void ViewPoint::registerBuilder(
                          const std::string& _classModel,
                          const std::string& _classViewPoint,
                          ViewBuilder _builder)
    {
      std::cout << "Registering constructor for " 
                << _classViewPoint << " " << _classModel << std::endl ;

      builders[std::make_pair<std::string,std::string>
                (_classViewPoint,_classModel)] = _builder ;
//                
//      builders.insert(std::pair<std::pair<std::string,std::string>, ViewBuilder>(
//                        std::make_pair<std::string,std::string>(
//                          _classViewPoint,_classModel),_builder)) ;

      std::cout << "Registered constructor" << std::endl ;
    }

    Object* ViewPoint::getObserverView() const
    {
      return this->observerView ;
    }


    void ViewPoint::destroy(Kernel::Implementation::BaseView* _view)
    {
      Kernel::Log::InternalMessage("ViewPoint::destroy removing view element") ;
      check(_view, Exception("ViewPoint::destroy")) ;
      Object* object = dynamic_cast<Object*>(_view) ;
      if (object)
      {
        Kernel::Log::InternalMessage("element is object") ;

        Object* contener(object->getContener()) ;
        if (contener)
        {
          contener->remove(object) ;
          Kernel::Log::InternalMessage("removed element from object") ;
        }
        else
        {
          this->views.erase(_view) ;
          Kernel::Log::InternalMessage("removed element from view point") ;
        }
      }
      else
      {

        Trait* trait = dynamic_cast<Trait*>(_view) ;
        if (trait)
        {
          Kernel::Log::InternalMessage("element is facette") ;
          trait->getObject()->remove(trait) ;
          Kernel::Log::InternalMessage("removed element") ;
          
        }
        else
        {
          /// error
          throw Exception("internal error") ;
        }
      }
    }

    Object* ViewPoint::getView(Model::Object* _object) const
    {
      Model::Positionned* parent(_object->getContener()
                                 ->getTrait<Model::Positionned>()) ;
      if (! parent)
      {
        for(std::set<Kernel::Implementation::BaseView*>::iterator 
            view = views.begin() ;
            view != views.end() ;
            ++view)
        {
          if ((*view)->getModel() == _object)
          {
            Object* result = dynamic_cast<Object*>(*view) ;
            return result ;
          }
        }
      }
      else
      {
        return getView(_object->getContener())->getSon(_object) ;
      }
    }


  }
}

