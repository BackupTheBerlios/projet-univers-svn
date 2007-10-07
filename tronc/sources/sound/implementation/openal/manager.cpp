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

#include <kernel/log.h>
 
#include <sound/implementation/openal/manager.h>
#include <sound/implementation/openal/wav_reader.h>
#include <sound/implementation/openal/ogg_reader.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        Manager::Manager()
        {}
        
        Manager::~Manager()
        {
          for (std::vector<Reader*>::iterator iter = m_readers.begin() ; iter != m_readers.end(); iter++) 
          {
            delete *iter ;
          }
          m_readers.clear() ;
        }
        
        Reader* Manager::createReader(ALuint p_source, std::string p_fileName, bool p_isEvent)
        {
          //TODO remplacer par une test mime ou au moins extension du fichier et non un choix arbitraite event= wav
          Reader* res ;
          if(p_isEvent)
          {
            res = new WavReader(p_source, p_fileName, p_isEvent) ;
          }
          else
          {
            res = new OggReader(p_source, p_fileName, p_isEvent) ;
          }
          res->onInit() ;
          m_readers.push_back(res) ;
          return res;
        }
        
        void Manager::update()
        {
          if(m_timer.getSecond() > 1.0)
          {
            m_timer.reset() ;
            for (std::vector<Reader*>::iterator iter = m_readers.begin() ; iter != m_readers.end(); ) 
            {
              if((*iter)->m_finish)
              {
                (*iter)->onClose() ;
                delete *iter;
                iter = m_readers.erase(iter) ;
              }
              else
              {
                InformationMessage("enter manager update") ;     
                (*iter)->update() ;
                ++iter;
                InformationMessage("leave manager update") ;     
              }
            }
          }          
        }
      }
    }
  }
}
