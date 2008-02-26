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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_TARGET_DISPLAYER_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_HUD_TARGET_DISPLAYER_H_

#include <kernel/trait_view.h>
#include <model/target_displayer.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/head_up_display/target_displayer_viewpoint.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Display targets.
        /*!
        @dot
        digraph 
        {
          compound=true;
          concentrate=true ;
          // model part
          "Model::TargetDisplayer" [shape=box URL="\ref Model::TargetDisplayer"] ;
          object -> "Model::Computer" [arrowhead=diamond] ;
          "Model::TargetDisplayer" -> "Model::Computer" [arrowhead=none] ;
          "Model::Positionned" -> object [arrowhead=diamond ltail=cluster_0] ;
        
          subgraph cluster_0
          {
            style="filled";
            label="Display::Implementation::Target" ;
            URL="\ref Display::Implementation::Target" ;
            "Model::Positionned" [shape=box URL="\ref Model::Positionned"] ;
            "Model::Selected" [shape=box URL="\ref Model::Selected"] ;
            "Model::DetectionData" [shape=box URL="\ref Model::DetectionData"] ;
            "Model::Solid" [shape=box URL="\ref Model::Solid"] ;
          }
        
          // ogre part
      
          "Ogre::TargetDisplayer" [shape=ellipse URL="\ref Ogre::TargetDisplayer"] ;
          "Ogre::TargetDisplayer" -> "Model::TargetDisplayer" [arrowhead=none] ;
          "HeadUpDisplay::TargetDisplayerViewPoint" -> "Ogre::TargetDisplayer" [arrowhead=diamond] ;
      
          "Model::Selected" -> "HeadUpDisplay::Target" [arrowhead=none ltail=cluster_0] ;
      
          // hud viewpoint
          subgraph cluster2
          {
            style="invis";
            object [shape=point label=""] ;
            "Model::Computer" [shape=box URL="\ref Model::Computer"] ;
    
            subgraph cluster_viewogre
            {
              label="Ogre::HeadUpDisplay" ;
              URL="\ref Ogre::HeadUpDisplay" ;
              style=dashed ;
  
              "HeadUpDisplay::TargetDisplayerViewPoint" [shape=ellipse URL="\ref HeadUpDisplay::TargetDisplayerViewPoint"] ;
              "HeadUpDisplay::Target" [shape=ellipse URL="\ref HeadUpDisplay::Target"] ;
              "HeadUpDisplay::Target" -> "HeadUpDisplay::TargetDisplayerViewPoint" [arrowhead=diamond] ;
            }
          }
        }
        @enddot
        */
        class TargetDisplayer : public Kernel::TraitView<Model::TargetDisplayer,
                                                         RealWorldViewPoint>
        {
        public:
        
        // **********************
        /// @name Construct
        // **********************
        // @{

          /// Constructeur.
          TargetDisplayer(Model::TargetDisplayer* i_object,
                          RealWorldViewPoint* i_viewpoint) ;

        //@}
          

        protected:

        /*!
          @name Updates
        */
        // @{
        
          /// create a Ogre::Entity.
          void onInit() ;
          
          /// Destroy the Ogre::Entity.
          void onClose() ;
        

        // @}
        private:
          
          Kernel::ViewPoint* m_implementation ;
        };
      }
    }
  }
}
#endif
