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
#include <model/engine_control.h>

namespace ProjetUnivers {
  namespace Model {
    
    EngineControl::EngineControl(Oriented* i_throttle,Engine* i_engine)
    : Kernel::Trait(),
      m_engine(i_engine),
      m_throttle(i_throttle)
    {
      if (m_engine)
      {
        m_engine->setControler(this) ;
      }
    }

    int EngineControl::getPowerPercentage() const
    {
      int percentage = 0 ;

      /// get throttle pitch
      if (m_throttle)
      {
        float pitch 
          = m_throttle->getOrientation().getQuaternion().getPitch().valueDegrees() ;
        
        percentage = (int)(pitch/0.9) ;
      }
      
      return percentage ;      
    }
    
  }
}
