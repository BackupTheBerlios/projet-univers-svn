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
#include <set>


namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    class Object ;
    class Model ;
    
    /// Abstract class for data writing.
    class Writer
    {
    public:
      
      /// Write @c model.
      void write(Model* model) ;

      /// Write a sub model made of a unique object
      void writeSingleObject(Object* object) ;
      
      virtual void startTrait(const std::string&) = 0 ;
      virtual void endTrait() = 0 ;
      virtual void addAttribute(const std::string&,const std::string&) = 0 ;
      
      virtual ~Writer() ;

    protected:
      
      /// Write an object. 
      void write(Object* object) ;
      
      virtual void startModel() = 0 ;
      virtual void endModel() = 0 ;
      
      virtual void startObject(Object*) = 0 ;
      virtual void endObject() = 0 ;
      
      
      Writer() ;
    };


  }
}
