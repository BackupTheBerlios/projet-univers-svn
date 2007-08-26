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
#ifndef PU_MODEL_THROTTLE_H_
#define PU_MODEL_THROTTLE_H_

#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that are a throttle.
    /*!
      Throttle have exactly one axis.
      usage : getOrientation().getPitch()
    */
    class Throttle : public Oriented
    {
    public:
    
      /// Constructor.
      Throttle() ;

      /// Modify the pitch.
      void modify(const int& i_delta) ;

      /// Set the pitch.
      void set(const int& i_delta) ;
    
    private:

      int m_y ;
    };
  }
}

#endif /*PU_MODEL_THROTTLE_H_*/
