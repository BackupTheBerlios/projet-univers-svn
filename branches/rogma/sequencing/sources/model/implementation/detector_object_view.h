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
#ifndef PU_MODEL_IMPLEMENTATION_DETECTOR_OBJECT_VIEW_H_
#define PU_MODEL_IMPLEMENTATION_DETECTOR_OBJECT_VIEW_H_

#include <kernel/trait_view.h>
#include <kernel/object_reference.h>

#include <model/implementation/detectable.h>
#include <model/implementation/detector_view_point.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      
      /// An object that is potentially detected by a detector.
      class DetectorObjectView : public Kernel::TraitView<Detectable,
                                                          DetectorViewPoint>
      {
      public:
        
        /// Construct.
        DetectorObjectView(Detectable*,DetectorViewPoint*) ;

        /// Check if object is detectable.
        void check() ;
        
      protected:
        
        virtual void onInit() ;

        /// Called just before the view is destroyed.
        virtual void onClose() ;
        
      private:
        
        /// Object representing detection information
        /*!
          Placed under the detector object.
          Remove and added when necessary.
        */
        Kernel::ObjectReference m_detection_information ;

      };
    }
  }
}


#endif /*PU_MODEL_IMPLEMENTATION_DETECTOR_OBJECT_VIEW_H_*/
