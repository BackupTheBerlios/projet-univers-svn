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
#include <iostream>
#include <libxml/encoding.h>
#include <kernel/object.h>
#include <kernel/string.h>
#include <kernel/xml_writer.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    #define MY_ENCODING "ISO-8859-1"
    
    XMLWriter::~XMLWriter()
    {
      xmlFreeTextWriter(m_writer) ;
      xmlBufferFree(m_buffer) ;
    }

    XMLWriter* XMLWriter::getFileWriter(const std::string& file)
    {
      XMLWriter* result = new XMLWriter() ;
      result->m_writer = xmlNewTextWriterFilename(file.c_str(),0) ;
      xmlTextWriterSetIndent(result->m_writer,2) ;
      result->m_buffer = NULL ;
      return result ;
    }
    
    XMLWriter* XMLWriter::getStringWriter()
    {
      XMLWriter* result = new XMLWriter() ;
      result->m_buffer = xmlBufferCreate() ;
      result->m_writer = xmlNewTextWriterMemory(result->m_buffer,0) ;
      return result ;
    }
    
    std::string XMLWriter::getContent() const
    {
      return (const char *) m_buffer->content ;
    }
    
    void XMLWriter::startTrait(const std::string& trait_name)
    {
      xmlTextWriterStartElement(m_writer,BAD_CAST trait_name.c_str());
    }
    
    void XMLWriter::endTrait()
    {
      xmlTextWriterEndElement(m_writer) ;
    }
    
    void XMLWriter::addAttribute(const std::string& name,const std::string& value)
    {
      xmlTextWriterWriteAttribute(m_writer,BAD_CAST name.c_str(),BAD_CAST value.c_str()) ;
    }
    
    void XMLWriter::startModel()
    {
      xmlTextWriterStartDocument(m_writer,NULL,MY_ENCODING,NULL) ;
      xmlTextWriterStartElement(m_writer,BAD_CAST "model");
    }
    
    void XMLWriter::endModel()
    {
      xmlTextWriterEndElement(m_writer) ;
      xmlTextWriterEndDocument(m_writer);

    }
    
    void XMLWriter::startObject(Object* object)
    {
      xmlTextWriterStartElement(m_writer,BAD_CAST "object") ;
      xmlTextWriterWriteAttribute(m_writer,BAD_CAST "id",BAD_CAST toString(object->getIdentifier()).c_str()) ;
    }
    void XMLWriter::endObject()
    {
      xmlTextWriterEndElement(m_writer) ;
    }
    
    XMLWriter::XMLWriter()
    : m_writer(NULL),
      m_object(NULL),
      m_trait(NULL)
    {}
  }
}
