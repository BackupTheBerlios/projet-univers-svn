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

#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_REAL_WORLD_VIEW_POINT_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_REAL_WORLD_VIEW_POINT_H_

#include <Ogre.h>

#include <kernel/object.h>
#include <kernel/view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /*!
          Ogre coordinates are coded on 32 bits, thus half the precision 
          is between 0 and 1.
          
          Here we use the following scale factor : 
          1 Ogre unit = 1000 meters 
        */
        const float conversion_factor = 1000 ;
        
        /// Subjection viewpoint of an observer.
        /*!
          First person view of an observer.
        */
        class RealWorldViewPoint : public Kernel::ViewPoint 
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{
          
          
          /// Constructeur.
          /*!
            @param[in] _observer 
              object that sees (e.g., a character, a camera,...)
          */
          RealWorldViewPoint(Kernel::Object* _observer) ;
          
          /// Initialize view point
          virtual void onInit() ;
          
          /// Terminate view point
          virtual void onClose() ;
          
          /// Change l'observer.
          virtual void onChangeObserver(Kernel::Object* _observer) ;

          /// Make this as the displayed viewpoint. 
          virtual void activate() ;
          
        // @}
        /*
          @name Access 
        */
        // @{

          /// Access to Ogre manager.
          ::Ogre::SceneManager* getManager() const ;
          
          /// Access to observer.
          Kernel::Object* getObserver() const ;

        // @}
        
        private:
        
          /// True iff object must be seen.
          virtual bool isVisible(Kernel::Object* _model) const ;
        /*!
          @name Attributes
        */
        // @{

          /// Manage 3D scene objects          
          ::Ogre::SceneManager* m_manager ;

          Kernel::Object* m_observer ;
          
        // @}
          
        };
      }
    }
  }
}


#endif
