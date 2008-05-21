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
#include <OgreResourceGroupManager.h>

#include <kernel/log.h>
#include <kernel/parameters.h>
 
#include <model/model.h>
#include <sound/implementation/openal/manager.h>
#include <sound/implementation/openal/wav_reader.h>
#include <sound/implementation/openal/ogg_reader.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        std::string findFilePath(const std::string& filename)
        {
          // on demand init
          Model::initRessources() ;
          
          std::string foundPath = filename;
          Ogre::ResourceGroupManager* groupManager = Ogre::ResourceGroupManager::getSingletonPtr() ;
          Ogre::String group = groupManager->findGroupContainingResource(filename) ;
          Ogre::FileInfoListPtr fileInfos = groupManager->findResourceFileInfo(group,foundPath);
          Ogre::FileInfoList::iterator it = fileInfos->begin();
          if(it != fileInfos->end())
          {
            foundPath = it->archive->getName() + "/" + foundPath;
            foundPath;
          }
          else
            foundPath = "";

          return foundPath;
        }
        
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
          Reader* result = NULL ;
          //Query a buffer a little bigger to evite the case 
          //where openal thread try to use the buffer when we load it
          if (p_fileName.find(".wav") != std::string::npos)
          {
            result = new WavReader(p_source, findFilePath(p_fileName), p_isEvent, m_updateTime*1.10) ;
          }
          else if (p_fileName.find(".ogg") != std::string::npos)
          {
            result = new OggReader(p_source, findFilePath(p_fileName), p_isEvent, m_updateTime*1.10) ;
          }
          else
          {
            ErrorMessage("[OpenAl::Manager] unsupported file type") ;
            return NULL ;
          }
          
          result->onInit(m_posInFile, m_posInBuffer) ;
          m_readers.push_back(result) ;
          return result ;
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
                InformationMessage("Sound","enter manager update") ;     
                (*iter)->update() ;
                ++iter;
                InformationMessage("Sound","leave manager update") ;     
              }
            }
          }          
        }
      }
    }
  }
}
