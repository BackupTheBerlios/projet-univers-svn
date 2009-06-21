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
#include <model/solid.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(Solid) ;
     
    Solid::Solid(const Mesh& i_mesh) 
    : Sized(Distance(Distance::_Meter,i_mesh.getBoundingSphereRadius())), 
      m_mesh(i_mesh)
    {}

    Kernel::Trait* Solid::read(Kernel::Reader* reader)
    {
      Solid* result = NULL ;
      Mesh mesh("") ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "Mesh")
        {
          mesh = Mesh::read(reader) ;
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      
      if (mesh.getName() == "")
      {
        ErrorMessage("Model::Solid::read must provide a mesh") ;
      }
      else
      {
        result = new Solid(mesh) ;
      }
      
      reader->processNode() ;

      return result ;
    }

    Mesh Solid::getMesh() const
    {
      return m_mesh ;
    }

    float Solid::getDragCoefficient(const Orientation&) const
    {
      /*!
        @todo find a rapid way to calculate 
      */
      return 1.0 ;
    }
    
    Distance Solid::getBoundingSphereRadius() const
    {
      return Distance(Distance::_Meter,m_mesh.getBoundingSphereRadius()) ;
    }
  }
}
