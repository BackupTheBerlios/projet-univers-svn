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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_TARGET_DISPLAYER_VIEWPOINT_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_TARGET_DISPLAYER_VIEWPOINT_H_

#include <Ogre.h>

#include <kernel/object.h>
#include <kernel/view_point.h>
#include <display/implementation/ogre/real_world_view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        /// Technical part for head up displays.
        namespace HeadUpDisplay {

           /// Viewpoint managing target displaying.
          class TargetDisplayerViewPoint : public Kernel::ViewPoint 
          {
          public:
          
          /*!
            @name Construction 
          */
          // @{
            
            
            /// Constructor.
            /*!
              @param[in] target_display 
                object that display the targets
              @param[in] real_world the real world viewpoint containing the 
                displaying object
            */
            TargetDisplayerViewPoint(Kernel::Object*     target_display,
                                     RealWorldViewPoint* real_world) ;
            
            /// Maybe the model should be changed.
            virtual void update(const float&) ;
            
          // @}
          /*
            @name Access 
          */
          // @{
            
            /// Access to the targeting system.
            Kernel::Object* getTargetingSystem() const ;
            
            /// Access to the "real observer".
            Kernel::Object* getObserver() const ;
            
            /// Access to camera. 
            ::Ogre::Camera* getCamera() const ;
            
            /// Access to the real world root.
            Kernel::Object* getWorldRoot() const ;
             
          // @}
          
          private:
          
          /*!
            @name Attributes
          */
          // @{
            
            /// 
            Kernel::Object* m_target_displayer ;
            
            RealWorldViewPoint* m_real_world ;  

          // @}
            
          };
        } 
      }
    }
  }
}

#endif /*PU_DISPLAY_IMPLEMENTATION_OGRE_TARGET_DISPLAYER_VIEWPOINT_H_*/
