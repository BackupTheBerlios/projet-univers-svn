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
#ifndef PU_KERNEL_XML_READER_H
#define PU_KERNEL_XML_READER_H

#include <string>
#include <map>

#include <libxml/xmlreader.h>

#include <kernel/reader.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    /// Read an xml file containing a model.
    class XMLReader : public Reader
    {
    public:
      
      /// Constructor from a file.
      static XMLReader* getFileReader(const std::string&) ; 
      
      /// Constructor from a memory content.
      static XMLReader* getStringReader(const std::string&) ;

      /// Move to next node return true iff there is another.
      virtual bool processNode() ; 

      /// True iff there are nodes.
      virtual bool hasNode() const ;

      /// Get the current node depth.
      virtual int getNodeDepth() const ;
      
      /// True iff current node is a model one.
      virtual bool isModelNode() const ;
      
      /// True iff current node is an object one.
      virtual bool isObjectNode() const ;

      /// Access to object identifier.
      virtual int getObjectIdentifier() const ;

      /// True iff current node is a trait one.
      virtual bool isTraitNode() const ;
      
      /// In case current node is a trait : get trait's name.
      virtual std::string getTraitName() const ; 
      
      /// True iff current node is deeper that previous.
      virtual bool isChild() const ;

      /// True iff the node is the beginning. 
      virtual bool isBeginNode() const ;

      /// True iff the node is the end. 
      virtual bool isEndNode() const ;

      /// Access to attribute values.
      virtual const std::map<std::string,std::string>& getAttributes() const ;
    
    private:

      /// Constructor.
      XMLReader() ;
    
      xmlTextReaderPtr m_reader ;
      
      /// current node attributes.
      std::map<std::string,std::string> m_attributes ;
    };
  }
}

#endif
