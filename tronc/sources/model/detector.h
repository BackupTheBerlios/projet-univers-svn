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
#ifndef PU_MODEL_DETECTOR_H_
#define PU_MODEL_DETECTOR_H_

#include <memory>

#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <kernel/reader.h>

#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {

    namespace Implementation {
      class DetectorViewPoint ;
    }
      
    /// Trait for objects that can detect other objects.
    /*!
      Maybe there are kinds of detectors :
      - some that detects massive objects 

      Detected datas are stored in a computer. Detectors do not detect parent 
      objects; for example, a detector does not detect its ship, nor its solar 
      system, nor its galaxy... 
      
    */
    class Detector : public Kernel::Trait
    {
    public:

      /// Constructs with a computer.
      Detector(Kernel::Object* computer) ;
      
      /// Constructs with a computer and a range.
      Detector(Kernel::Object* computer,const Distance& range) ;

      /// Read a Detector trait.
      /*!
        stored as 
          <Detector>
            [<ObjectReference ... [name="computer"]/>]
            [<Distance ... [name="range"]/>]
          </Detector>
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;

      /// Initialisation.
      void init() ;
      
      /// Detector range.
      Distance getRange() const ;
      
      /// Performs detection.
      void detect() ;
      
      /// True iff the object is detected by @c this.
      virtual bool canDetect(const Kernel::Object*) const ;
      
      /// Access to computer.
      Kernel::Object* getComputer() const ;
      
    private:
      
      /// Implementation.
      std::auto_ptr<Implementation::DetectorViewPoint> m_implementation ;
      
      /// detecting range.
      Distance                                         m_range ;
      
      /// The computer in which we store detection data.
      Kernel::ObjectReference                          m_computer ;
      
    };

  }

}

#endif
