/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <string>

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
      
            
    // @}
    /*!
      @name Access
    */
    // @{
    
      /// Access to name.
      std::string getName() const ;
      
            
    // @}

    
    private:
    
      /// Mesh name.
      std::string name ;
            
    };
    
  }
}

#endif 
