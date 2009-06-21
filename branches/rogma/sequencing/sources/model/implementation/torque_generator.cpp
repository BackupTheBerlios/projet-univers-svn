/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <model/torque_generator.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(TorqueGenerator) ;
    
    TorqueGenerator::TorqueGenerator() 
    : Kernel::Trait(), 
      m_torque(0,0,0)
    {}

    Kernel::Trait* TorqueGenerator::read(Kernel::Reader* reader)
    {
      TorqueGenerator* result = new TorqueGenerator() ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("x") ;
      if (finder != reader->getAttributes().end())
      {
        result->m_torque.x = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::TorqueGenerator::read required attribute : x") ;
      }

      finder = reader->getAttributes().find("y") ;
      if (finder != reader->getAttributes().end())
      {
        result->m_torque.y = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::TorqueGenerator::read required attribute : y") ;
      }

      finder = reader->getAttributes().find("z") ;
      if (finder != reader->getAttributes().end())
      {
        result->m_torque.z = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::TorqueGenerator::read required attribute : z") ;
      }

      finder = reader->getAttributes().find("unit") ;
      if (finder != reader->getAttributes().end())
      {
        if (finder->second == "NewtonMeter")
        {
        }
        else 
        {
          ErrorMessage("Model::TorqueGenerator::read invalid unit : " + finder->second) ;
        }
      }
      else
      {
        ErrorMessage("Model::TorqueGenerator::read required attribute : unit") ;
      }
      
      while (!reader->isEndNode() && reader->processNode())
      {}

      reader->processNode() ;

      return result ;
    }
    
    TorqueGenerator::~TorqueGenerator()
    {}

    void TorqueGenerator::setNewtonMeter(const float& i_x,  
                                         const float& i_y,
                                         const float& i_z)
    {
      m_torque[0] = i_x ;
      m_torque[1] = i_y ;
      m_torque[2] = i_z ;
    }
    
    Ogre::Vector3 TorqueGenerator::NewtonMeter() const
    {
      return m_torque ;
    }
  }
}
