/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_SHOOTING_HELPER_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_SHOOTING_HELPER_H_

#include <memory>
#include <kernel/controler.h>
#include <model/shooting_helper.h>
#include <model/implementation/logic/logic_system.h>
#include <model/implementation/logic/shooting_helper_viewpoint.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        /// Generates the associated ideal target with the selectioned target. 
        /*!
        @dot
        digraph 
        {
          compound=true;
          concentrate=true ;
          root="Model::Computer" ;
          
          "Model::ShootingHelper" [shape=box URL="\ref Model::ShootingHelper"] ;
          object -> "Model::Computer" [arrowhead=diamond] ;
          "Model::ShootingHelper" -> "Model::Computer" [arrowhead=none] ;
          "Model::Positionned" -> object [arrowhead=diamond ltail=cluster_0] ;
        
          subgraph cluster_0
          {
            style="filled";
            label="Model::Implementation::Target" ;
            URL="\ref Model::Implementation::Target" ;
            "Model::Positionned" [shape=box URL="\ref Model::Positionned"] ;
            "Model::Selected" [shape=box URL="\ref Model::Selected"] ;
            "Model::DetectionData" [shape=box URL="\ref Model::DetectionData"] ;
            "Model::Solid" [shape=box URL="\ref Model::Solid"] ;
            "Model::Mobile" [shape=box URL="\ref Model::Mobile"] ;
          }
        
          // logic part
          subgraph cluster_1
          {
            label="Logic" ;
            URL="\ref Logic" ;
            style=dashed ;
            "Logic::ShootingHelperViewPoint" [shape=ellipse URL="\ref Model::Implementation::Logic::ShootingHelperViewPoint"] ;
            "Logic::Target" [shape=ellipse URL="\ref Model::Implementation::Logic::Target"] ;
          }
      
          "Logic::ShootingHelper" [shape=ellipse URL="\ref Logic::ShootingHelper"] ;
          "Logic::ShootingHelper" -> "Model::ShootingHelper" [arrowhead=none] ;
          "Logic::ShootingHelperViewPoint" -> "Logic::ShootingHelper" [arrowhead=diamond] ;
          "Logic::ShootingHelperViewPoint" -> "Logic::Target" [arrowtail=diamond arrowhead=none] ;
      
          "Logic::Target" -> "Model::Positionned" [arrowhead=none lhead=cluster_0] ;
      
          object [shape=point label=""] ;
          "Model::Computer" [shape=box URL="\ref Model::Computer"] ;
    
        }
        @enddot
        */
        class ShootingHelper : public Kernel::Controler<Model::ShootingHelper,
                                                        LogicSystem>
        {
        public:
        
        /*! 
          @name Construct
        */ 
        // @{

          /// Constructor.
          ShootingHelper(Model::ShootingHelper* object,
                         LogicSystem* system) ;
        // @}
          
      protected:
        /*!
          @name Updates
        */
        // @{
        
          /// Create ShootingHelperViewPoint.
          virtual void onInit() ;
          
          /// Destroy ShootingHelperViewPoint.
          virtual void onClose() ;
          
          /// Update ShootingHelperViewPoint.
          virtual void onUpdate() ;
          
        // @}
        private:

          ShootingHelperViewPoint* m_implementation ;
        };
      }
    }
  }
}

#endif /*PU_MODEL_IMPLEMENTATION_LOGIC_SHOOTING_HELPER_H_*/
