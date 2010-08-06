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

#include <iostream>

#include <physic/implementation/ode/mass_property.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        void ComputeMassProperties(
            std::vector< ::Ogre::Vector3> i_vertexes, 
            std::vector<unsigned long> i_indices,
            bool bBodyCoords, 
            float& rfMass,
            Ogre::Vector3& rkCenter, 
            Ogre::Matrix3& rkInertia)
        {
            const float fOneDiv6 = (float)(1.0/6.0);
            const float fOneDiv24 = (float)(1.0/24.0);
            const float fOneDiv60 = (float)(1.0/60.0);
            const float fOneDiv120 = (float)(1.0/120.0);
        
            // order:  1, x, y, z, x^2, y^2, z^2, xy, yz, zx
            float afIntegral[10] = { (float)0.0, (float)0.0, (float)0.0, (float)0.0,
                (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0 };
        
            int index =0 ;            
            for (unsigned int i = 0; i < i_indices.size()/3; i++)
            {
                // get vertices of triangle i
                Ogre::Vector3 kV0 = i_vertexes[i_indices[index++]];
                Ogre::Vector3 kV1 = i_vertexes[i_indices[index++]];
                Ogre::Vector3 kV2 = i_vertexes[i_indices[index++]];
        
                // get cross product of edges
                Ogre::Vector3 kV1mV0 = kV1 - kV0;
                Ogre::Vector3 kV2mV0 = kV2 - kV0;
                Ogre::Vector3 kN = kV1mV0.crossProduct(kV2mV0);
        
                // compute integral terms
                float fTmp0, fTmp1, fTmp2;
                float fF1x, fF2x, fF3x, fG0x, fG1x, fG2x;
                fTmp0 = kV0.x + kV1.x;
                fF1x = fTmp0 + kV2.x;
                fTmp1 = kV0.x*kV0.x;
                fTmp2 = fTmp1 + kV1.x*fTmp0;
                fF2x = fTmp2 + kV2.x*fF1x;
                fF3x = kV0.x*fTmp1 + kV1.x*fTmp2 + kV2.x*fF2x;
                fG0x = fF2x + kV0.x*(fF1x + kV0.x);
                fG1x = fF2x + kV1.x*(fF1x + kV1.x);
                fG2x = fF2x + kV2.x*(fF1x + kV2.x);
        
                float fF1y, fF2y, fF3y, fG0y, fG1y, fG2y;
                fTmp0 = kV0.y + kV1.y;
                fF1y = fTmp0 + kV2.y;
                fTmp1 = kV0.y*kV0.y;
                fTmp2 = fTmp1 + kV1.y*fTmp0;
                fF2y = fTmp2 + kV2.y*fF1y;
                fF3y = kV0.y*fTmp1 + kV1.y*fTmp2 + kV2.y*fF2y;
                fG0y = fF2y + kV0.y*(fF1y + kV0.y);
                fG1y = fF2y + kV1.y*(fF1y + kV1.y);
                fG2y = fF2y + kV2.y*(fF1y + kV2.y);
        
                float fF1z, fF2z, fF3z, fG0z, fG1z, fG2z;
                fTmp0 = kV0.z + kV1.z;
                fF1z = fTmp0 + kV2.z;
                fTmp1 = kV0.z*kV0.z;
                fTmp2 = fTmp1 + kV1.z*fTmp0;
                fF2z = fTmp2 + kV2.z*fF1z;
                fF3z = kV0.z*fTmp1 + kV1.z*fTmp2 + kV2.z*fF2z;
                fG0z = fF2z + kV0.z*(fF1z + kV0.z);
                fG1z = fF2z + kV1.z*(fF1z + kV1.z);
                fG2z = fF2z + kV2.z*(fF1z + kV2.z);
        
                // update integrals
                afIntegral[0] += kN.x*fF1x;
                afIntegral[1] += kN.x*fF2x;
                afIntegral[2] += kN.y*fF2y;
                afIntegral[3] += kN.z*fF2z;
                afIntegral[4] += kN.x*fF3x;
                afIntegral[5] += kN.y*fF3y;
                afIntegral[6] += kN.z*fF3z;
                afIntegral[7] += kN.x*(kV0.y*fG0x + kV1.y*fG1x + kV2.y*fG2x);
                afIntegral[8] += kN.y*(kV0.z*fG0y + kV1.z*fG1y + kV2.z*fG2y);
                afIntegral[9] += kN.z*(kV0.x*fG0z + kV1.x*fG1z + kV2.x*fG2z);
            }
        
            afIntegral[0] *= fOneDiv6;
            afIntegral[1] *= fOneDiv24;
            afIntegral[2] *= fOneDiv24;
            afIntegral[3] *= fOneDiv24;
            afIntegral[4] *= fOneDiv60;
            afIntegral[5] *= fOneDiv60;
            afIntegral[6] *= fOneDiv60;
            afIntegral[7] *= fOneDiv120;
            afIntegral[8] *= fOneDiv120;
            afIntegral[9] *= fOneDiv120;
        
            // mass
            rfMass = afIntegral[0];
            
//            std::cout <<" rfMass =" <<  rfMass << std::endl ;
            // center of mass
            if (rfMass != 0)
            {
              rkCenter =
                  Ogre::Vector3(afIntegral[1],afIntegral[2],afIntegral[3])/rfMass;
            }        
            // inertia relative to world origin
            rkInertia[0][0] = afIntegral[5] + afIntegral[6];
            rkInertia[0][1] = -afIntegral[7];
            rkInertia[0][2] = -afIntegral[9];
            rkInertia[1][0] = rkInertia[0][1];
            rkInertia[1][1] = afIntegral[4] + afIntegral[6];
            rkInertia[1][2] = -afIntegral[8];
            rkInertia[2][0] = rkInertia[0][2];
            rkInertia[2][1] = rkInertia[1][2];
            rkInertia[2][2] = afIntegral[4] + afIntegral[5];
        
            // inertia relative to center of mass
            if ( bBodyCoords )
            {
                rkInertia[0][0] -= rfMass*(rkCenter.y*rkCenter.y +
                    rkCenter.z*rkCenter.z);
                rkInertia[0][1] += rfMass*rkCenter.x*rkCenter.y;
                rkInertia[0][2] += rfMass*rkCenter.z*rkCenter.x;
                rkInertia[1][0] = rkInertia[0][1];
                rkInertia[1][1] -= rfMass*(rkCenter.z*rkCenter.z +
                    rkCenter.x*rkCenter.x);
                rkInertia[1][2] += rfMass*rkCenter.y*rkCenter.z;
                rkInertia[2][0] = rkInertia[0][2];
                rkInertia[2][1] = rkInertia[1][2];
                rkInertia[2][2] -= rfMass*(rkCenter.x*rkCenter.x +
                    rkCenter.y*rkCenter.y);
            }
        }
      }
    }
  }
}
