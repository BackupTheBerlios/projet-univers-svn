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
    
    class EngineControl ;
    
    /// Ship/Other objects engine.
    /*!
    */
    class Engine : public ForceGenerator
    {
    public:

      /// Constructor.
      Engine(const Force& i_force) ;
      
      /// Set the 
      void setControler(EngineControl*) ;
      
      /// Get the force.
      virtual Force getAppliedForce() const ;
      
    private:
      
      /// Maximal "force". 
      /*!
        Orientation is relative to parent physical object.
        Thus normally a ship force is : (0,0,100) or something.
      */
      Force m_full_thrust ;
      
      /// Controler of this engine
      EngineControl* m_controler ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_ENGINE_H_*/
