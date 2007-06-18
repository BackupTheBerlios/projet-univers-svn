/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#ifndef PU_MODEL_ENGINE_H_
#define PU_MODEL_ENGINE_H_


#include <model/force_generator.h>
#include <model/force.h>


namespace ProjetUnivers {
  namespace Model {
    
    /// Ship/Other objects engine.
    /*!
    */
    class Engine : public ForceGenerator
    {
    public:

      /// Constructor.
      Engine(const Force& i_force) ;
 
      /// Get the force.
      /*!
        @remark may be null even at full thrust. In order to keep a 
        "standard" gameplay, speed is limitted.
         
      */
      virtual Force getAppliedForce() const ;
      
    private:
      
      /// Thrust axis and "force". 
      /*!
        Relative to parent physical object.
        Norm is 
      */
      Force m_full_thrust ;
      
      /*!
        - 0 --> does not push
        - 100 --> full thrust 
      */
      int m_percentage_thrust ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_ENGINE_H_*/
