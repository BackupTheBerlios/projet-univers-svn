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
#include <kernel/trait.h>
#include <kernel/object.h>
#include <kernel/model.h>

#include <model/exception.h>
#include <model/observer.h>
#include <model/massive.h>
#include <model/mobile.h>
#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/positionned.h>
#include <model/stellar_system.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/torque_generator.h>
#include <model/universe.h>

#include <model/model.h>

namespace ProjetUnivers {
  namespace Model 
  {

  /*!
    @name Module data.
  */
  // @{
    
    /// our real world.
    std::auto_ptr<Kernel::Model> model(new Kernel::Model("real world")) ;    

  // @}


    Kernel::Object* getObject(const std::string& i_name)
    {
      return model->getObject(i_name) ;
    }
      
    Kernel::Object* createObject(const std::string& i_name)
    {
      return model->createObject(i_name) ;
    }
    
    Kernel::Object* createObject(const std::string& i_name, 
                                 Kernel::Object* i_parent)
    {
      return model->createObject(i_name,i_parent) ;
    } 

    void destroyObject(const std::string& i_name)
    {
      model->destroyObject(i_name) ;
    }
    
    void destroyObject(Kernel::Object* i_object)
    {
      model->destroyObject(i_object) ;
    }

    void changeParent(Kernel::Object* i_object, 
                      Kernel::Object* i_new_parent)
    {
      model->changeParent(i_object,i_new_parent) ;
    }

    void addTrait(Kernel::Object* i_object, 
                  Kernel::Trait* i_new_trait) 
    {
      model->addTrait(i_object,i_new_trait) ;
    }

    void destroyTrait(Kernel::Object* i_object, 
                      Kernel::Trait* i_trait) 
    {
      model->destroyTrait(i_object,i_trait) ;
    }
    
    /*!
      @par Etat 
        minimal
    */
    void init()
    {
      model.reset(new Kernel::Model("real world")) ;
    }

    /*!
      @par Etat 
        minimal
    */
    void close()
    {
      InternalMessage("Deleting objects") ;
      model.reset() ;      
      InternalMessage("Module Model terminated") ;
      
    }


    /*!
      @par Etat 
        Test codé en dur
    */
    void load(const std::string& _name)
    {
     
      if (_name == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        InternalMessage("building Universe...") ;
        Kernel::Object* universe = model->createObject("Univers") ;
        
        /// ses facettes
        model->addTrait(universe,new Universe()) ;
        model->addTrait(universe,new Positionned()) ;
        
        InternalMessage("construction de Univers terminée") ;

        /// 1.4 Une galaxie
        
        /// 1.5 Un système stellaire
        InternalMessage("building stellar system...") ;

        Kernel::Object* system = model->createObject("Systeme#1",universe) ;
        model->addTrait(system,new StellarSystem()) ;
        model->addTrait(system,new Positionned()) ;
        
        InternalMessage("building stellar system done") ;
        
        
        
        /// 2. Ajout d'objects planetes
        InternalMessage("building planet...") ;
        Kernel::Object* planet1 = model->createObject("Planete#1",system) ;
        model->addTrait(planet1,new Positionned()) ;

        InternalMessage("building planet done") ;

        /// add(new Solide(planete1, 
        
        /// 3. Ajout d'un vaisseau
        {
          InternalMessage("building ship...") ;
          Kernel::Object* ship = model->createObject("Vaisseau",system) ;
          model->addTrait(ship,new Positionned(Position::Meter(0,
                                                               0,
                                                               -500000))) ;
          
          model->addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
          model->addTrait(ship,new Mobile()) ;
          model->addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
          
          InternalMessage("building ship done") ;
        }
        {
          InternalMessage("building ship...") ;
          Kernel::Object* ship = model->createObject("Vaisseau#3",system) ;
          model->addTrait(ship,new Positionned(Position::Meter(0,
                                                               100000,
                                                               -500000))) ;
          
          model->addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
          model->addTrait(ship,new Mobile()) ;
          model->addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
          model->addTrait(ship,new Stabilizer(0,1,0)) ;
          
          InternalMessage("building ship done") ;
        }

                
        /// 4. Ajout d'un observateur
        InternalMessage("building observer...") ;
        Kernel::Object* observer = model->createObject("Observer",system) ;
        model->addTrait(observer,new Positionned(Position::Meter(0,
                                                             0,
                                                             0))) ;

        /// Il a la faculté d'observer
        model->addTrait(observer,new Observer()) ;

        InternalMessage("building observer done") ;
      
      }
            
    }
    
    Kernel::Model* getRealWorlModel()
    {
      return model.get() ;
    }
  }
}


