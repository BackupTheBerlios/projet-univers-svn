/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD, Mathieu ROGER                     *
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
#ifndef PU_MODEL_HEARING_H_
#define PU_MODEL_HEARING_H_

#include <kernel/trait.h>
#include <kernel/reader.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// For object that can hear.
    /*!
      @todo Restoring hearing with time
      @todo Deafening effect after explosion for example
    */
    class Hearing : public Kernel::Trait
    {
    public:

      /// Constructor.
      Hearing() ;

      /// Read a Hearing trait.
      /*!
        stored as 
          <Hearing hearing_percentage=".."/>
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to hearing.
      int getHearing() const ;
      
      /// Modify hearing.
      void setHearing(int newHearing);
      
    private:
      
      /// The percentage of hearing 
      /*!
        value in [0,100]
      */
      int m_hearing_percentage ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_HEARING_H_*/
