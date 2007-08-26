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
#ifndef PU_MODEL_GUIDANCE_CONTROL_H_
#define PU_MODEL_GUIDANCE_CONTROL_H_

#include <kernel/trait.h>
#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Model {
    
    class GuidanceSystem ;
    
    /// Computer part that control orientation.
    /*!
      @see GuidanceSystem 
    */
    class GuidanceControl : public Kernel::Trait
    {
    public:

      /// Constructor.
      GuidanceControl(Oriented* i_stick,GuidanceSystem* i_system) ;
      
      /// Access to stick orientation.
      Orientation getStickOrientation() const ;
      
    private:
      
      /// the stick 
      /*!
        it is a normalised orientation of a stick.
      */ 
      Oriented* m_stick ;
      
      /// The system controled.
      GuidanceSystem* m_guidance_system ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_GUIDANCE_CONTROL_H_*/
