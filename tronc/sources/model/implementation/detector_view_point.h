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
#ifndef PU_MODEL_IMPLEMENTATION_DETECTOR_VIEW_POINT_H_
#define PU_MODEL_IMPLEMENTATION_DETECTOR_VIEW_POINT_H_

#include <kernel/view_point.h>
#include <kernel/object.h>
#include <model/detector.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      
      /// Implementation of detection.
      /*!
        @todo 
          We could share the same viewpoint for all detectors of the scene. 
          Each potential detected object would be tested against each detector 
          objects.
          This development should be preceed by a specific test with two 
          detectors. 
      */
      class DetectorViewPoint : public Kernel::ViewPoint
      {
      public:
        
        /// Construct.
        DetectorViewPoint(Detector* observer) ;
        
        /// Access to observer object.
        Detector* getObserver() const ;
        
      /*!
        @name Functionnal methods
      */
      // @{

        
        void addDetectedObject(Kernel::Object*) ; 
        void removeDetectedObject(Kernel::Object*) ; 
        
      // @}
        
      private:
      
        Detector* m_detector ;
                
        
      };
    }
  }
}

#endif /*PU_MODEL_IMPLEMENTATION_DETECTOR_VIEW_POINT_H_*/
