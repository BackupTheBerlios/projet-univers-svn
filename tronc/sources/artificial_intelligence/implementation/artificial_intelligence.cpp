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
#include <artificial_intelligence/implementation/ai_system.h>
#include <artificial_intelligence/artificial_intelligence.h>

namespace ProjetUnivers {
  namespace ArtificialIntelligence {

    void start()
    {
      
    }
    
    std::auto_ptr<Implementation::AISystem> m_viewPoint ;
    
    bool init()
    {
      if(m_viewPoint.get())
      {
        m_viewPoint->init() ;
      }
    }
    
    void close()
    {
      if(m_viewPoint.get())
      {
        m_viewPoint->close() ;
      }
    }
  
    void build(Kernel::Object* observer)
    {
      m_viewPoint.reset(new Implementation::AISystem(observer->getModel())) ;
    }
    
    void update(const Model::Duration& duration)
    {
      if (m_viewPoint.get())
      {
        m_viewPoint->simulate(duration.Second()) ;
      }
    }
    
    namespace Implementation {
      
      AISystem* getAISystem()
      {
        return m_viewPoint.get() ;
      }
    }
    
  }
}
