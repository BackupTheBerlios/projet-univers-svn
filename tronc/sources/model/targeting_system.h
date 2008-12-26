/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_MODEL_TARGETING_SYSTEM_H_
#define PU_MODEL_TARGETING_SYSTEM_H_

#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <kernel/reader.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    
    namespace Implementation
    {
      class DetectorObjectView ;
    }
    
    /// System that handle targets.
    class TargetingSystem : public Kernel::Trait
    {
    public:
    
    /*!
      @name Construction
    */
    // @{
    
      /// Constructs.
      TargetingSystem() ;

      /// Connect a targeting system to a computer.
      static void connect(Kernel::Object* targeting_system,
                          Kernel::Object* computer) ;

      /// Read a TargetingSystem trait.
      /*!
        stored as 
        @code
          <TargetingSystem>
            [<ObjectReference ... [name="computer"]/>]
          </TargetingSystem>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to selected target.
      Kernel::Object* getTarget() const ;

      /// Access to computer model.
      Kernel::Model* getComputerModel() const ;

      /// Access to computer.
      Kernel::Object* getComputer() const ;
      
    // @}  
    /*!
      @name Commands
    */
    // @{

      void selectNextTarget() ;
      void selectPreviousTarget() ;
      void selectNearestTarget() ;
      void selectNearestEnemy() ;
      
    // @}  
      
      
    private:
      
      /// Select an object as a target.
      void selectTarget(Kernel::Object*) ;
      
      /// Unselect an object as a target.
      void unSelectTarget(Kernel::Object*) ;

      /// The DetectionData targeted.
      Kernel::ObjectReference m_target ;
      
      /// The computer that is ancestor of detection data.
      Kernel::ObjectReference m_computer ;
      
      friend class Implementation::DetectorObjectView ;
    };
  }
}

#endif /*PU_MODEL_TARGETING_SYSTEM_H_*/
