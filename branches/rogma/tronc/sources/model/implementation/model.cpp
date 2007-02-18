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
#include <kernel/joli_affichage.h>
#include <kernel/log.h>
#include <kernel/errorr.h>

#include <model/exception.h>
#include <model/trait.h>
#include <model/object.h>
#include <model/observer.h>
#include <model/positionned.h>
#include <model/stellar_system.h>
#include <model/solid.h>
#include <model/universe.h>

#include <model/model.h>

namespace ProjetUnivers {
  namespace Model 
  {

  /*!
    @name Variables du module.
  */
  // @{
    
    struct LocalMemory
    {
      std::set<Object*> objects ;
      
      void clear()
      {
        for(std::set<Object*>::iterator object = objects.begin() ;
            object != objects.end() ;
            ++object)
        {
          delete *object ;
        }
        
      }

      ~LocalMemory()
      {
        clear() ;
      }
    };
    
    LocalMemory local ;
    
    std::map<std::string,Object*> registeredObjects ;

  // @}

      Object* add(Object* _object)
      {
        check(_object,Exception("Model::add(Object*)")) ;
        
        local.objects.insert(_object) ;
        
        registeredObjects.insert(
          std::pair<std::string,Object*>(_object->getName(), _object)) ;
        
        return _object ;
      }

      Kernel::Association<Object> register(const Kernel::Association<Object>& _object)
      {
        registreObjects.add(_object->getName(), _object) ;
      }

      

    
    /*!
      @par Etat 
        minimal
    */
    void init()
    {
      local.objects.clear() ;
      registeredObjects.clear() ;
    }

    /*!
      @par Etat 
        minimal
    */
    void close()
    {
      Kernel::Log::InternalMessage("Deleting objects") ;
      local.objects.clear() ;

      Kernel::Log::InternalMessage("Deleting object references") ;
      registeredObjects.clear() ;
      
      Kernel::Log::InternalMessage("Module Model terminated") ;
      
    }

    /*!
      @par Etat 
        OK
    */
    Object* getObject(const std::string& _name)
    {
      Object* result(registeredObjects[_name]) ;
      check(result, Exception("no object with such name " + _name)) ;
      return result ;
    }

    /*!
      @par Etat 
        Test cod� en dur
    */
    void load(const std::string& _name)
    {
     
      if (_name == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        Kernel::Log::InternalMessage("building Universe...") ;
        Object* universe = add(new Object(Name("Univers"))) ;
        
        /// ses facettes
        univers->add(new Universe()) ;
        univers->add(new Positionned()) ;

        Kernel::Log::InternalMessage("construction de Univers termin�e") ;

        /// 1.4 Une galaxie
        
        /// 1.5 Un syst�me stellaire
        Kernel::Log::InternalMessage("building stellar system...") ;
        Object* system = universe->add(new Object(Name("Systeme#1"))) ;
        system->add(new Positionned(Position())) ;
        system->add(new StellarSystem()) ;
         
        Kernel::Log::InternalMessage("building stellar system done") ;
        
        
        
        /// 2. Ajout d'objects planetes
        Kernel::Log::InternalMessage("building planet...") ;
        Object* planet1 = system->add(new Object(Name("Planete#1"))) ;
        planet1->add(new Positionned(Position())) ;

        Kernel::Log::InternalMessage("building planet done") ;

        /// add(new Solide(planete1, 
        
        /// 3. Ajout d'un vaisseau
        {
          Kernel::Log::InternalMessage("building ship...") ;
          Object* ship = system->add(new Object(Name("Vaisseau"))) ;
          ship->add(new Positionned(Position(Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, -500000)) )) ;
          
          ship->add(new Solid(Model3D("razor.mesh"))) ;
  
          Kernel::Log::InternalMessage("building ship done") ;
        }
        {
          Kernel::Log::InternalMessage("building ship...") ;
          Object* ship = system->add(new Object(Name("Vaisseau3"))) ;
          ship->add(new Positionned(Position(Distance(Distance::_Metre, 0),
                                                    Distance(Distance::_Metre, 100000),
                                                    Distance(Distance::_Metre, -500000)) )) ;
          
          ship->add(new Solid(Model3D("razor.mesh"))) ;
  
          Kernel::Log::InternalMessage("building ship done") ;
        }

                
        /// 4. Ajout d'un observateur
        Kernel::Log::InternalMessage("building observer...") ;
        Object* observer = system->add(new Object(Name("Observer"))) ;
        observer->add(new Positionned(Position(Distance(Distance::_Metre, 0),
                                                     Distance(Distance::_Metre, 0),
                                                     Distance(Distance::_Metre, 0)) )) ;

        /// Il a la facult� d'observer
        observer->add(new Observer()) ;

        Kernel::Log::InternalMessage("building observer done") ;
      
      }
      
            
    }

    void remove(Object* _object)
    {
      if (_object->getContener())
      {
        _object->getContener()->remove(_object) ;
      }
      else
      {
        local.objects.erase(_object) ;
      }
    }
    
  }
}


