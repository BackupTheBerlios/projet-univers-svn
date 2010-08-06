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
#include <sound/implementation/openal/reader.h>
#include <sound/implementation/openal/ogg_file_stream.h>
#include <sound/implementation/openal/ogg_cached_stream.h>
#include <sound/implementation/openal/wav_file_stream.h>
#include <sound/implementation/openal/manager.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        std::string findFilePath(const std::string& filename)
        {
          // on demand init
          Model::initRessources() ;

          std::string foundPath = filename;
          Ogre::ResourceGroupManager* groupManager =
              Ogre::ResourceGroupManager::getSingletonPtr() ;
          Ogre::String group =
              groupManager->findGroupContainingResource(filename) ;
          Ogre::FileInfoListPtr fileInfos = groupManager->findResourceFileInfo(
              group, foundPath);
          Ogre::FileInfoList::iterator it = fileInfos->begin();
          if (it != fileInfos->end())
          {
            foundPath = it->archive->getName() + "/" + foundPath;
          }
          else
            foundPath = "";

          return foundPath;
        }

        Manager::Manager()
        {
          try
          {
            m_updateTime = Kernel::Parameters::getValue<float>("Sound","UpdateTime");
          }
          catch(Kernel::ExceptionKernel e)
          {
            m_updateTime = 1;
          }
        }
        
        void Manager::cacheRessource(const std::string& file_name)
        {
          std::string file_path(findFilePath(file_name)) ;
          
          std::map<std::string,Stream*>::const_iterator stream = m_cached_streams.find(file_path) ;
          if (stream == m_cached_streams.end())
          {
            m_cached_streams[file_path] = new OggCachedStream(file_path) ;
          }
        }

        Manager::~Manager()
        {
          for(std::vector<Reader*>::iterator iter = m_readers.begin() ; 
              iter != m_readers.end(); iter++)
          {
            (*iter)->close() ;
            delete *iter;
          }
          m_readers.clear() ;
          
          for(std::map<std::string,Stream*>::iterator stream = m_cached_streams.begin() ; 
              stream != m_cached_streams.end(); stream++)
          {
            delete stream->second ;
          }
          m_cached_streams.clear() ;
          for(std::set<Stream*>::iterator stream = m_streams.begin() ; 
              stream != m_streams.end(); stream++)
          {
            delete *stream ;
          }
          m_streams.clear() ;
        }

        Stream* Manager::getStream(const std::string& file_name)
        {
          /// search for cached streams
          std::string file_path(findFilePath(file_name)) ;
          
          std::map<std::string,Stream*>::const_iterator stream = m_cached_streams.find(file_path) ;
          if (stream != m_cached_streams.end())
          {
            return stream->second ;
          }
          
          Stream* result = NULL ;
          
          if (file_name.find(".ogg") != std::string::npos)
          {
            result = new OggFileStream(file_path) ;
            m_streams.insert(result) ;
          }
          else if (file_name.find(".wav") != std::string::npos)
          {
            result = new WavFileStream(file_path) ;
            m_streams.insert(result) ;
          }
          else
          {
            ErrorMessage("[OpenAl::Manager] unsupported file type") ;
          }
          return result ;
        }
        
        void Manager::releaseStream(Stream* stream)
        {
          std::set<Stream*>::iterator finder = m_streams.find(stream) ;
          if (finder != m_streams.end())
          {
            delete *finder ;
            m_streams.erase(finder) ;
          }
        }

        Reader* Manager::createReader(const std::string& fileName,
                                      const bool& isEvent,
                                      const int& posInFile,
                                      const int& posInBuffer)
        {
          Reader* result = new Reader(getStream(fileName),isEvent) ;
          result->init(posInFile,posInBuffer) ;
          m_readers.push_back(result) ;
          return result;
        }

        void Manager::destroyReader(Reader* reader)
        {
          reader->close() ;
          releaseStream(reader->getStream()) ;
          m_readers.erase(std::find(m_readers.begin(),m_readers.end(),reader)) ;
          delete reader;
        }

        void Manager::update()
        {
          if (m_timer.getSecond() > m_updateTime)
          {
            m_timer.reset() ;
            for (std::vector<Reader*>::iterator reader = m_readers.begin() ; reader != m_readers.end();)
            {
              if ((*reader)->isFinished())
              {
                (*reader)->close() ;
                releaseStream((*reader)->getStream()) ;
                delete *reader;
                reader = m_readers.erase(reader) ;
              }
              else
              {
                InformationMessage("Sound", "enter manager update") ;
                (*reader)->update() ;
                ++reader;
                InformationMessage("Sound", "leave manager update") ;
              }
            }
          }
        }
      }
    }
  }
}
