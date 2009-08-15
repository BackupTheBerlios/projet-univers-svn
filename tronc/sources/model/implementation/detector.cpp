/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <OgreStringConverter.h>

#include <kernel/object.h>

#include <model/positionned.h>
#include <model/detector.h>
#include <model/data_connection.h>

namespace ProjetUnivers
{
  namespace Model
  {

    RegisterTrait(Detector) ;
    
    Detector::Detector()
    : m_range(Distance::_Meter,1000)
    {}
    
    Detector::Detector(const Distance& range)
    : m_range(range)
    {}

    void Detector::connect(Kernel::Object* detector,Kernel::Object* computer)
    {
      Kernel::Link<DataConnection>(detector,computer) ;
    }

    Kernel::Trait* Detector::read(Kernel::Reader* reader)
    {
      Detector* result = new Detector() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && reader->getTraitName() == "Distance")
        {
          result->m_range = Distance::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      reader->processNode() ;
      
      return result ;
    }
    
    Distance Detector::getRange() const
    {
      // temp
      return m_range ;
    }
    
    bool Detector::canDetect(const Kernel::Object* object) const
    {
      // we do not detect parent objects :
      if (object->isAncestor(getObject()))
      {
        InternalMessage("Model","Model::Detector::canDetect does not detect parent") ;
        return false ;
      }
      
      // range check 
      Position position = getRelativePosition(object,getObject()) ;
      InternalMessage("Model","Model::Detector::canDetect relative position=" + Ogre::StringConverter::toString(position.Meter()) ) ;
      bool in_range = position.calculateDistance(Position()) <=  getRange() ; 

      InternalMessage("Model","Model::Detector::canDetect range test") ;
      // @todo add structure checks

      return in_range ;      
    }


  }     
}
