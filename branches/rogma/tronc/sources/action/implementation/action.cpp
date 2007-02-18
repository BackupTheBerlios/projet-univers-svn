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
#include <kernel/log.h>

#include <model/model.h>
#include <model/object.h>
#include <model/positionned.h>
#include <model/solid.h>
#include <model/stellar_system.h>

#include <action/action.h>

using namespace ProjetUnivers::Model ;
using namespace ::Ogre ;

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
      if (_action.nom == "Sortie")
      {
        finished = true ;
      }
      else if (_action.nom == "Haut")
      {
        Kernel::Association<Model::Object> observateur(Model::getObject("Observer")) ;
        Kernel::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::NEGATIVE_UNIT_X))) ;
            
        
      }
      else if (_action.nom == "Bas")
      {
        Kernel::Association<Model::Object> observateur(Model::getObject("Observer")) ;
        Kernel::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::UNIT_X))) ;
        
      }
      else if (_action.nom == "Droite")
      {
        Kernel::Association<Model::Object> observateur(Model::getObject("Observer")) ;
        Kernel::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::NEGATIVE_UNIT_Y))) ;
        
      }
      else if (_action.nom == "Gauche")
      {
        Kernel::Association<Model::Object> observateur(Model::getObject("Observer")) ;
        Kernel::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->getOrientation().getQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::UNIT_Y))) ;
        
        
      }
      else if (_action.nom == "RegarderVaisseau")
      {
        /*!
          @par Etat 
            planning...
        */
        Kernel::Association<Model::Object> observateur(Model::getObject("Observer")) ;
        Kernel::Association<Model::Positionne> observateurPositionne(*observateur) ;

        Kernel::Association<Model::Object> vaisseau(Model::getObject("Vaisseau")) ;
        Kernel::Association<Model::Positionne> vaisseauPositionne(*vaisseau) ;
        
      }
      else if (_action.nom == "CreerObject")
      {
        Kernel::Association<Model::Object> observateur(Model::getObject("Observer")) ;
        
        Kernel::Association<Model::Object> systeme(
          observateur->getParent<Model::SystemeStellaire>()->getObject()) ;
        
        Kernel::Association<Object> vaisseau = systeme->add(new Object(Name("Vaisseau2"))) ;
        vaisseau->add(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                  Distance(Distance::_Metre, 500000),
                                                  Distance(Distance::_Metre, 0)) )) ;
        
        vaisseau->add(new Solide(Model3D("razor.mesh"))) ;
        
      }
      else if (_action.nom == "destroyObject")
      {
        Kernel::Association<Model::Object> vaisseau(Model::getObject("Vaisseau2")) ;
        Kernel::Log::InternalMessage("perparing to destroy object") ;
        Model::remove(vaisseau) ;
      }
    }
    
    
    void init()
    {
      actions.clear() ;
      finished = false ;
    }

    void close()
    {
      actions.Vider() ;
    }

    void update()
    {
      for(std::list<Action>::iterator action = actions.begin() ;
          action =! actions.end() ;
          ++action)
      {
        perfom(*action) ;
      }
      
      actions.clear() ;
    }

    void add(const std::string& _nomAction)
    {
      Action temp ;
      temp.name = _nomAction ;
      actions.push_back(temp) ;
    }

    bool finished()
    {
      return is_finished ;
    }


  }
}

