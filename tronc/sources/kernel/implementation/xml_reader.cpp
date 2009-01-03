/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <libxml/xmlreader.h>
#include <kernel/xml_reader.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    namespace libxml {
      namespace NodeType {
        const int start_element = 1 ;
        const int end_element = 15 ;
        const int attribute = 2 ;
        const int text_node = 3 ;
        const int CData = 4 ;
        const int entity_reference = 5 ;
        const int entity_declaration = 6 ;
        const int PI = 7 ;
        const int comment = 8 ;
        const int document = 9 ;
        const int doctype = 10 ;
        const int fragment = 11 ;
        const int notation = 12 ;
      }
    }

    bool XMLReader::processNode()
    {
      if (m_reader == NULL)
      {
        std::cout << "error" << std::endl ;
      }
      
      if (xmlTextReaderRead(m_reader) != 1)
      {
        return false ;
      }
      
      m_attributes.clear() ;
      
      if (xmlTextReaderHasAttributes(m_reader) == 1)
      {
        int count = xmlTextReaderAttributeCount(m_reader);
        for(int i = 0 ; i < count ; i++)
        {
          xmlTextReaderMoveToAttributeNo(m_reader,i);
          
          m_attributes.insert(std::pair<std::string,std::string>(
            (char*)xmlTextReaderConstLocalName(m_reader),
            (char*)xmlTextReaderConstValue(m_reader))) ;
        }        
        xmlTextReaderMoveToElement(m_reader) ;
      }

//      std::cout << print() << std::endl ;
      
      return true ;
    }

    bool XMLReader::hasNode() const
    {
      return xmlTextReaderReadState(m_reader) != -1 ;
    }
    
    int XMLReader::getNodeDepth() const
    {
      return xmlTextReaderDepth(m_reader) ;
    }
    
    bool XMLReader::isModelNode() const
    {
      const xmlChar* name = xmlTextReaderConstName(m_reader) ;
      
      return isBeginNode() && xmlStrEqual(name,(const xmlChar*)"model") == 1 ;
    }
    
    bool XMLReader::isObjectNode() const
    {
      const xmlChar* name = xmlTextReaderConstName(m_reader) ;
      
      return isBeginNode() && xmlStrEqual(name,(const xmlChar*)"object") == 1 ;
    }

    int XMLReader::getObjectIdentifier() const
    {
      std::map<std::string,std::string>::const_iterator
        finder = m_attributes.find("id") ;
      
      if (finder != m_attributes.end())
      {
        return atoi(finder->second.c_str()) ;
      }
      return 0 ;
    }
    
    bool XMLReader::isTraitNode() const
    {
      return isBeginNode() && !isObjectNode() && !isModelNode() ;
    }
    
    std::string XMLReader::getTraitName() const
    {
      const xmlChar* name = xmlTextReaderConstName(m_reader) ;
      return (char*)name ;
    } 
    
    bool XMLReader::isChild() const
    {
      return false ;
    }

    bool XMLReader::isBeginNode() const
    {
      return xmlTextReaderNodeType(m_reader) == libxml::NodeType::start_element ;
    }

    bool XMLReader::isEndNode() const
    {
      return (xmlTextReaderNodeType(m_reader) == libxml::NodeType::end_element)
             || (isBeginNode() && xmlTextReaderIsEmptyElement(m_reader)) ;
    }

    XMLReader::XMLReader()
    : m_reader()
    {}

    XMLReader* XMLReader::getFileReader(const std::string& file)
    {
      XMLReader* result = new XMLReader() ;
      result->m_reader = xmlReaderForFile(file.c_str(),NULL,0) ;
      result->processNode() ;
      return result ;
    }
      
    XMLReader* XMLReader::getStringReader(const std::string& content)
    {
      XMLReader* result = new XMLReader() ;
      result->m_reader = xmlReaderForDoc((const xmlChar*)content.c_str(),NULL,NULL,0) ;
      result->processNode() ;
      return result ;
    }
    
    const std::map<std::string,std::string>& XMLReader::getAttributes() const
    {
      return m_attributes ;
    }
  }
}

