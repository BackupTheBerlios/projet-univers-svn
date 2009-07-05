/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#pragma once

#include <string>
#include <map>

#include <libxml/xmlwriter.h>

#include <kernel/writer.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    class Trait ;
    
    /// Write a model or an object to a string.
    class XMLWriter : public Writer
    {
    public:
      
      /// Constructor to a file.
      static XMLWriter* getFileWriter(const std::string&) ; 
      
      /// Constructor to a memory content.
      static XMLWriter* getStringWriter() ;
    
      std::string getContent() const ;
      
    protected:
      
      virtual void startTrait(const std::string&) ;
      virtual void endTrait() ;
      virtual void addAttribute(const std::string&,const std::string&) ;
      
      virtual void startModel() ;
      virtual void endModel() ;
      
      virtual void startObject(Object*) ;
      virtual void endObject() ;
      
    private:

      /// Constructor.
      XMLWriter() ;
    
      xmlTextWriterPtr m_writer ;
      xmlBufferPtr     m_buffer ;
      /// Current object
      Object* m_object ;
      Trait*  m_trait ;
    };
  }
}
