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

// Wild Magic Source Code
// David Eberly
// http://www.geometrictools.com
// Copyright (c) 1998-2007
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// either of the locations:
//     http://www.gnu.org/copyleft/lgpl.html
//     http://www.geometrictools.com/License/WildMagicLicense.pdf
//
// Version: 4.0.0 (2006/06/28)

#ifndef WM4POLYHEDRALMASSPROPERTIES_H
#define WM4POLYHEDRALMASSPROPERTIES_H

#include <OgreVector3.h>
#include <OgreMatrix3.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        // The input triangle mesh must represent a polyhedron.  The triangles are
        // represented as triples of indices <V0,V1,V2> into the vertex array.
        // The connectivity array has iTQuantity such triples.  The Boolean value
        // bBodyCoords is 'true' if you want the inertia tensor to be relative to
        // body coordinates, 'false' if you want it in world coordinates.
        void ComputeMassProperties(
            std::vector< ::Ogre::Vector3> i_vertexes, 
            std::vector<unsigned long> i_indices,
            bool bBodyCoords, 
            float& rfMass,
            Ogre::Vector3& rkCenter, 
            Ogre::Matrix3& rkInertia) ;
      }
    }
  }
}

#endif
