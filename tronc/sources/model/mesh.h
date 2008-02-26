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
#ifndef PU_MODEL_MESH_H_
#define PU_MODEL_MESH_H_

#include <Ogre.h>
#include <string>
#include <kernel/reader.h>

namespace ProjetUnivers {
  namespace Model {
    
    
    /// A 3d mesh.
    /*!
      
    */
    class Mesh
    {
    public:
    
    /*!
      @name Construct
    */
    // @{
    
      /// Construct.
      Mesh(const std::string& _name) ;
      
      /// Copy.
      Mesh(const Mesh&) ;
      
      /// Read a Mesh.
      /*!
        stored as 
        @code
          <Mesh ogre_ressource=".."/>
        @endcode
      */          
      static Mesh read(Kernel::Reader* reader) ;

    // @}
    /*!
      @name Access
    */
    // @{
    
      /// Access to name.
      std::string getName() const ;

      /// Access to vertex and triangles
      void getMeshInformation(
        std::vector< ::Ogre::Vector3>& o_vertices,
        std::vector<unsigned long>&    o_indices,
        const ::Ogre::Vector3&         i_scale) const ;
      
      /// The radius of an englobing sphere.
      float getBoundingSphereRadius() const ;
            
    // @}

    
    private:
    
      /// Mesh name.
      std::string m_name ;
            
    };
    
  }
}

#endif 
