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
#ifndef PU_KERNEL_CONTROLER_SET_H_
#define PU_KERNEL_CONTROLER_SET_H_

#include <list>
#include <boost/function.hpp>
#include <kernel/helper_macros.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
  
    class Model ;
    class Object ;
    class BaseControler ;
    class ControlerSetRegistration ;
    
    /// A set of coherent controlers.
    class ControlerSet
    {
    public:

      /// Set the simulation time step in seconds. 
      void setTimeStep(const float& timestep) ;
      
      /// Initialise the controler set.
      void init() ;

      /// Change the model.
      void setModel(Model* model) ;
      
      /// Close the controler set.
      void close() ;

      /// Simulate all controlers top down.
      /*!
        Can be overridden for specific purpose. 
      */
      virtual void simulate(const float& seconds) ;

      /// Perform the simulation.
      void update(const float& seconds) ;
      
      /// True iff the controler set has been initialised
      bool isInitialised() const ; 
      
      /// Abstract class means virtual destructor.
      virtual ~ControlerSet() ;

      /// Statistics managment.
      float getStatistics() const ;
      void resetStatistics() ;
      
    protected:
      
      /// Build all the registered controler sets on @c model.
      /*!
        ControlerSets can be registered through RegisterControlerSet macro.
      */
      static void buildRegistered(Model* model) ;
      
      /// called during initialisation before controlers initialisation.
      /*!
        Default implementation does nothing. Specific viewpoint should 
        probably redefine this.
      */
      virtual void onInit() ;

      /// called during closing after controlers closing.
      /*!
        Default implementation does nothing. Specific controler set should 
        probably redefine this.
      */
      virtual void onClose() ;

      /// Should @c i_object should have controlers for that controler set.
      /*!
        Should be redefined for specialised viewpoints. Default implementation 
        returns true.
        
        @invariant
          if !isVisible(object) 
          then 
            whatever child of object !isVisible(child)
      */
      virtual bool isVisible(Object* object) const ;
 
      /// Apply a procedure on all controlers.
      void applyTopDown(boost::function1<void,BaseControler*> procedure) ;
 
      /// Apply a procedure on all controlers.
      void applyBottomUp(boost::function1<void,BaseControler*> procedure) ;
      
      /// Abstract class means protected constructor.
      ControlerSet(Model* model) ;
      
      Model* m_model ;
      bool   m_initialised ;

      /// elapsed time since last simulation
      float m_elapsed ;

      /// Simulation time step.
      float m_timestep ;
      
      /// Performance statistics
      float m_consumed_time ;
      float m_simulation_time ;
      
      /// Function that build a controler set.
      typedef boost::function1<ControlerSet*, Model*> ControlerSetBuilder ;

      /// Static storage
      /*!
        Because static variable dynamic initialisation occurs in an undefined 
        order, we use this hook. By calling : 
        <code>
          StaticStorage::get()->variable...
        </code>
        we are assured that map are dynamically initialised on demand.
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
      
      /// Register a controler set builder.
      static void registerBuilder(ControlerSetBuilder) ;
      
      
      friend class Object ;
      friend class Model ;
      friend class ControlerSetRegistration ;
    };

    /// Register a controler set
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

#endif /*PU_KERNEL_CONTROLER_SET_H_*/
