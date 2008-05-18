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
#ifndef PU_MODEL_WITH_LIFETIME_H_
#define PU_MODEL_WITH_LIFETIME_H_

#include <kernel/trait.h>
#include <model/duration.h>

namespace ProjetUnivers {
  namespace Model {
      
    /// For objects that have a lifetime.
    /*!
      When their lifetime reaches zero : the object is destroyed.
    */
    class WithLifetime : public Kernel::Trait
    {
    public:
    
      /// Constructs.
      WithLifetime(const Duration& lifetime) ;

      /// Access to life time.
      float getLifeTimeInSeconds() const ;
      
      /// Reduce life time.
      void removeLifeTime(const Duration&) ;
      
    private:
      
      /// Time remaining before the beam fades out.
      Duration m_life_time ;
      
    };
  }
}

#endif /*PU_MODEL_WITH_LIFETIME_H_*/
