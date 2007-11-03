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
#include <kernel/parameters.h>
 
#include <sound/implementation/openal/manager.h>
#include <sound/implementation/openal/wav_reader.h>
#include <sound/implementation/openal/ogg_reader.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        Manager::Manager(Kernel::Object* listener, Kernel::Object* reference)
        : m_listener(listener), m_reference(reference)
        {
          try
          {
            m_updateTime = Kernel::Parameters::getValue<float>("Sound","UpdateTime") ;
          }
          catch(Kernel::ExceptionKernel e)
          {
          	m_updateTime = 1;
          }
        }
        
        Manager::~Manager()
        {
          for (std::vector<Reader*>::iterator iter = m_readers.begin() ; iter != m_readers.end(); iter++) 
          {
          	(*iter)->onClose() ;
            delete *iter ;
          }
          m_readers.clear() ;
        }
        
        Reader* Manager::createReader(const ALuint& p_source,const std::string& p_fileName, const bool& p_isEvent, const int& m_posInFile, const int& m_posInBuffer)
        {
          //TODO remplacer par une test mime ou au moins extension du fichier et non un choix arbitraite event= wav
          Reader* res ;
          //Query a buffer a little bigger to evite the case 
          //where openal thread try to use the buffer when we load it
          if(!p_isEvent)
          {
          	
            res = new WavReader(p_source, p_fileName, p_isEvent, m_updateTime*1.10) ;
          }
          else
          {
            res = new OggReader(p_source, p_fileName, p_isEvent, m_updateTime*1.10) ;
          }
          res->onInit(m_posInFile, m_posInBuffer) ;
          m_readers.push_back(res) ;
          return res;
        }
        
        Kernel::Object* Manager::getListener()
        {
          return m_listener;	
        }
          
        Kernel::Object* Manager::getReference()
        {
          return m_reference;
        }
        
        void Manager::update()
        {
          if(m_timer.getSecond() > m_updateTime)
          {
            m_timer.reset() ;
            for (std::vector<Reader*>::iterator iter = m_readers.begin() ; iter != m_readers.end(); ) 
            {
              if((*iter)->isFinish())
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
