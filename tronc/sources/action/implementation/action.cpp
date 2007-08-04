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

#include <OgreVector3.h>

#include <list>
#include <kernel/error.h>
#include <kernel/log.h>
#include <kernel/object.h>

#include <model/model.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/stellar_system.h>
#include <model/mobile.h>

#include <action/action.h>

using namespace ProjetUnivers::Model ;
using namespace ::Ogre ;
using namespace ProjetUnivers::Kernel ;

namespace ProjetUnivers {
  namespace Action {

    bool is_finished ;

    struct Action
    {
      std::string name ;
      
    };

    std::list<Action> actions ;
    
    
    void perfom(const Action& _action)
    {
      if (_action.name == "Sortie")
      {
        is_finished = true ;
      }
      else if (_action.name == "Haut")
      {
        Object* observateur(Model::getObject("Observer")) ;
        Oriented* oriented(observateur->getTrait<Oriented>()) ;
        
        oriented->setOrientation(
          Model::Orientation(
            oriented->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::NEGATIVE_UNIT_X))) ;
            
        
      }
      else if (_action.name == "Bas")
      {
        Object* observateur(Model::getObject("Observer")) ;
        Oriented* oriented(observateur->getTrait<Oriented>()) ;
        
        oriented->setOrientation(
          Model::Orientation(
            oriented->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::UNIT_X))) ;
        
      }
      else if (_action.name == "Droite")
      {
        Object* observateur(Model::getObject("Observer")) ;
        Oriented* oriented(observateur->getTrait<Oriented>()) ;
        
        oriented->setOrientation(
          Model::Orientation(
            oriented->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::NEGATIVE_UNIT_Y))) ;
        
      }
      else if (_action.name == "Gauche")
      {
        Object* observateur(Model::getObject("Observer")) ;
        Oriented* oriented(observateur->getTrait<Oriented>()) ;
        
        oriented->setOrientation(
          Model::Orientation(
            oriented->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::UNIT_Y))) ;
        
        
      }
      else if (_action.name == "RegarderVaisseau")
      {
        /*!
          @par Etat 
            planning...
        */
        Object* observateur(Model::getObject("Observer")) ;
        Positionned* positionne(observateur->getTrait<Positionned>()) ;

        Object* vaisseau(Model::getObject("Vaisseau")) ;
        Positionned* vaisseauPositionne(vaisseau->getTrait<Positionned>()) ;

        
      }
      else if (_action.name == "CreerObject")
      {
        Object* observateur(Model::getObject("Observer")) ;
        Object* system(observateur->getParent<StellarSystem>()->getObject()) ;
        check(system,std::string("action::creer_objet error")) ;         
        Object* vaisseau = Model::createObject("Asteroid",system) ;
        if (vaisseau)
        {
          Model::addTrait(vaisseau,new Positionned(Position::Meter(0,
                                                                   500,
                                                                   0))) ;
          
          Model::addTrait(vaisseau,new Solid(Model::Mesh("laser.mesh"))) ;
        }
        else
        {
          InternalMessage("Action object already exists") ;
        }
      }
      else if (_action.name == "destroyObject")
      {
        InternalMessage("preparing to destroy object") ;
        Model::destroyObject("Asteroid") ;
      }
      else if (_action.name == "moveObject")
      {
        InternalMessage("preparing to move object") ;
        Kernel::Object* object = Model::getObject("Vaisseau#3") ;
        if (object)
        {
          Model::Mobile* mobile = object->getTrait<Model::Mobile>() ;
          if (mobile)
          {
            InternalMessage("moving object") ;
            Ogre::Vector3 angular_speed = mobile->getAngularSpeed().TurnPerSecond() ;
            angular_speed[1] += 1 ;
            mobile->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(
              angular_speed[0],
              angular_speed[1],
              angular_speed[2])) ;
          }
        }
        
      }

    }
    
    
    void init()
    {
      actions.clear() ;
      is_finished = false ;
    }

    void close()
    {
      actions.clear() ;
    }

    void update()
    {
      for(std::list<Action>::iterator action = actions.begin() ;
          action != actions.end() ;
          ++action)
      {
        perfom(*action) ;
      }
      
      actions.clear() ;
    }

    void add(const std::string& _name)
    {
      Action temp ;
      temp.name = _name ;
      actions.push_back(temp) ;
    }

    bool finished()
    {
      return is_finished ;
    }


  }
}

