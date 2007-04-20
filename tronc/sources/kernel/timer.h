/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#ifndef PU_KERNEL_TIMER_H_
#define PU_KERNEL_TIMER_H_

#include <boost/timer.hpp>

namespace ProjetUnivers {
  namespace Kernel {

    /// Something that measure time.
    class Timer
    {
    public:
      
      /// Constructor.
      Timer() ;
      
      /// Reset the timer to zero.
      void reset() ;
      
      /// Return the time elapsed in seconds.
      float getSecond() const ; 

    private:
    
      boost::timer m_timer ;
    };
  }
}

#endif /*PU_KERNEL_TIMER_H_*/
