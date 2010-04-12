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
#include <kernel/string.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/model.h>

#include <kernel/writer.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    void Writer::write(Model* model)
    {
      startModel() ;
      
      std::set<ObjectReference> objects ;
      
      for(std::set<Object*>::const_iterator object = model->getRoots().begin() ;
          object != model->getRoots().end() ;
          ++object)
      {
        objects.insert(*object) ;
      }
      
      for(std::set<ObjectReference>::const_iterator object = objects.begin() ;
          object != objects.end() ;
          ++object)
      {
        write(*object) ;
      }
      
      endModel() ;
    }

    void Writer::writeSingleObject(Object* object)
    {
      startModel() ;
      write(object) ;
      endModel() ;
    }
    
    void Writer::write(Object* object)
    {
      startObject(object) ;
      for(std::set<Trait*>::const_iterator trait = object->_getTraits().begin() ;
         trait != object->_getTraits().end() ;
         ++trait)
      {
        (*trait)->write(this) ;
      }

      std::set<ObjectReference> objects ;
      
      for(std::set<Object*>::const_iterator child = object->getChildren().begin() ;
          child != object->getChildren().end() ;
          ++child)
      {
        objects.insert(*child) ;
      }
      
      for(std::set<ObjectReference>::const_iterator created_object = objects.begin() ;
          created_object != objects.end() ;
          ++created_object)
      {
        write(*created_object) ;
      }
      
      endObject() ;
    }
    
    Writer::Writer()
    {}
    
    Writer::~Writer()
    {}
  }
}
