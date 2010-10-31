/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#pragma once

#include <list>
#include <boost/function.hpp>
#include <kernel/helper_macros.h>
#include <kernel/base_controler.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
  
    class Model ;
    class Object ;
    class ControlerSetRegistration ;
    
    /// A set of coherent controllers.
    class ControlerSet
    {
    public:

      /// Set the simulation time step in seconds.
      /*!
        When one wants a fixed timestep for simulation, e.g. for physics.
        If one does not want a fixed timestep just let it to zero (default).
      */
      void setTimeStep(const float& timestep) ;
      
      /// Access to the simulation time step in seconds.
      float getTimeStep() const ;

      /// Initialize the controller set.
      void init() ;

      /// Change the model.
      void setModel(Model* model) ;
      
      /// Close the controller set.
      void close() ;

      /// Called just before simulation.
      virtual void beforeSimulation(const float& seconds) ;

      /// Simulate all controllers top down.
      /*!
        Can be overridden for specific purpose. 
      */
      virtual void simulate(const float& seconds) ;

      /// Called just before simulation.
      virtual void afterSimulation(const float& seconds) ;

      /// Perform the simulation.
      void update(const float& seconds) ;
      
      /// True iff the controller set has been initialized
      bool isInitialised() const ; 
      
      /// Abstract class means virtual destructor.
      virtual ~ControlerSet() ;

      /// Statistics management.
      float getStatistics() const ;
      void resetStatistics() ;
      
    protected:
      
      /// called during initialization before controllers initialization.
      /*!
        Default implementation does nothing. Specific viewpoint should 
        probably redefine this.
      */
      virtual void onInit() ;

      /// called during closing after controllers closing.
      /*!
        Default implementation does nothing. Specific controller set should
        probably redefine this.
      */
      virtual void onClose() ;

      /// Should @c i_object should have controllers for that controller set.
      /*!
        Should be redefined for specialized viewpoints. Default implementation
        returns true.
        
        @invariant
          if !isVisible(object) 
          then 
            whatever child of object !isVisible(child)
      */
      virtual bool isVisible(Object* object) const ;
 
      /// Apply a procedure on all controllers.
      void applyTopDown(boost::function1<void,BaseControler*> procedure) ;
 
      /// Apply a procedure on all controllers.
      void applyBottomUp(boost::function1<void,BaseControler*> procedure) ;

      /// Abstract class means protected constructor.
      ControlerSet(Model* model) ;
      

    private:

      /// Check some properties on order.
      void checkOrder(const std::list<BaseControler*>& controllers) ;

      /// Reorder controllers for the next round.
      /*!
        We do it at the beginning of the simulation because order change during
        the simulation. With that trick we avoid weird behaviors.
      */
      void orderControlers() ;

      /// Build all the registered controller sets on @c model.
      /*!
        ControlerSets can be registered through RegisterControlerSet macro.
      */
      static void buildRegistered(Model* model) ;
      
      Model* m_model ;
      bool   m_initialised ;

      /// elapsed time since last simulation
      float m_elapsed ;

      /// Simulation time step.
      float m_timestep ;
      
      /// Performance statistics
      float m_consumed_time ;
      float m_simulation_time ;
      

      /// Add an initialized controller.
      void addControler(BaseControler*) ;
      void removeControler(BaseControler*) ;

      /// If called it is an error.
      void destroyController(BaseControler*) ;

      /// Controllers
      /*!
        Only contains initialized controllers.
      */
      std::list<BaseControler*> m_controllers ;

      /// Function that build a controller set.
      typedef boost::function1<ControlerSet*, Model*> ControlerSetBuilder ;

      /// Static storage
      /*!
        Because static variable dynamic initialization occurs in an undefined
        order, we use this hook. By calling : 
        <code>
          StaticStorage::get()->variable...
        </code>
        we are assured that map are dynamically initialized on demand.
      */
      class StaticStorage
      {
      public:
        
        /// Access to singleton.
        static StaticStorage* get() ; 
      
        std::list<ControlerSetBuilder> m_controler_set_builders ;

      private:
        
        StaticStorage()
        {}
        
      };
      
      /// Register a controller set builder.
      static void registerBuilder(ControlerSetBuilder) ;
      
      
      friend class Object ;
      friend class Model ;
      friend class ControlerSetRegistration ;
      friend class BaseControler ;
    };

    /// Register a controller set
    #define RegisterControlerSet(ClassControlerSet) \
      namespace PU_MAKE_UNIQUE_NAME(RegisterControlerSet) {              \
        static ProjetUnivers::Kernel::ControlerSet*                      \
              build(ProjetUnivers::Kernel::Model* model)                 \
        {                                                                \
          return new ClassControlerSet(model) ;                          \
        }                                                                \
        static                                                           \
          ProjetUnivers::Kernel::ControlerSetRegistration temp(&build) ; \
      }
    
  }
}

#include <kernel/implementation/controler_set.cxx>
