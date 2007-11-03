/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                    *
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
#ifndef PU_MODEL_EAR_H_
#define PU_MODEL_EAR_H_

#include <kernel/trait.h>
#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// Player's ears
    //TODO restoring hearing with time
    //TODO Deafening effect after explosion for example
    class Ear : public Kernel::Trait
    {
    public:

      /// Constructor.
      Ear() ;
      
      /// Access to hearing.
      int getHearing() const ;
      
      /// Modify hearing.
      void setHearing(int newHearing);
      
    private:
      
      /// The percentage of hearing 
      int hearing;
      
    };
    
    
  }
}

#endif /*PU_MODEL_EAR_H_*/
