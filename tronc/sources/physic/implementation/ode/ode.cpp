/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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

#include <physic/implementation/ode/physical_object.h>
#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/mass_property.h>
#include <physic/implementation/ode/ode.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {


        std::string printReal(const dReal& i_real)
        {
          return toString((float)i_real) ;
        }

        std::string printVector3(const dVector3& i_vector) 
        {
          std::string result ;          
          result = "Vector3(x=" + toString(i_vector[0]) 
                   + ",y=" + toString(i_vector[1])
                   + ",z=" + toString(i_vector[2]) + ")" ;
          return result ;
        }

        std::string printVector4(const dVector4& i_vector) 
        {
          std::string result ;          
          result = "Vector4(x=" + toString(i_vector[0]) 
                   + ",y=" + toString(i_vector[1])
                   + ",z=" + toString(i_vector[2]) 
                   + ",z'=" + toString(i_vector[3]) + ")" ;
          return result ;
        }

        std::string printMatrix3(const dMatrix3& i_matrix) 
        {
          std::string result ;          
          result = "Matrix3(" 
                   + toString(i_matrix[0]) + "," 
                   + toString(i_matrix[1]) + "," 
                   + toString(i_matrix[2]) + ","
                   + toString(i_matrix[3]) + "|"

                   + toString(i_matrix[4]) + "," 
                   + toString(i_matrix[5]) + "," 
                   + toString(i_matrix[6]) + ","
                   + toString(i_matrix[7]) + "|"

                   + toString(i_matrix[8]) + "," 
                   + toString(i_matrix[9]) + "," 
                   + toString(i_matrix[10]) + ","
                   + toString(i_matrix[11]) + ")" ;
          
          return result ;
        }

        std::string printMass(const dMass& i_mass)
        {
          std::string result ;          
          result = "Mass(mass=" + printReal(i_mass.mass) 
                   +",center=" + printVector3(i_mass.c)
                   +",intertia=" + printMatrix3(i_mass.I) +")" ;
                   
          return result ;
        }

        void meshToMass(const Model::Mesh& i_mesh,dMass* io_mass)
        {
          std::vector< ::Ogre::Vector3> vertices ;
          std::vector<unsigned long>    indices ;
          Ogre::Vector3                 scale(1,1,1) ;        
  
          i_mesh.getMeshInformation(vertices,indices,scale) ;

          float mass ;
          Ogre::Vector3 center ;
          Ogre::Matrix3 inertia ;
          ComputeMassProperties(vertices,indices,true,mass,center,inertia) ;
        
          std::cout << "center = " << center 
                    << " inertia= " 
                    << inertia.GetColumn(0) << " "  
                    << inertia.GetColumn(1) << " "
                    << inertia.GetColumn(2) 
                    << std::endl ;

          io_mass->mass = (dReal) mass ;
          io_mass->c[0] = (dReal) center.x ; 
          io_mass->c[1] = (dReal) center.y ; 
          io_mass->c[2] = (dReal)center.z ; 

          io_mass->I[0] = (dReal) inertia[0][0] ;
          io_mass->I[1] = (dReal) inertia[0][1] ;
          io_mass->I[2] = (dReal) inertia[0][2] ;
          io_mass->I[3] = (dReal) 0 ;

          io_mass->I[4] = (dReal) inertia[1][0] ;
          io_mass->I[5] = (dReal) inertia[1][1] ;
          io_mass->I[6] = (dReal) inertia[1][2] ;
          io_mass->I[7] = (dReal) 0 ;
          
          io_mass->I[8] = (dReal) inertia[2][0] ;
          io_mass->I[9] = (dReal) inertia[2][1] ;
          io_mass->I[10] = (dReal) inertia[2][2] ;
          io_mass->I[11] = (dReal) 0 ;
          
        }

        PhysicalObject* getPhysicalObject(const Kernel::BaseControler* controler)
        {
          Model::PhysicalObject* 
              object = controler->getObject()->getParent<Model::PhysicalObject>() ; 
          
          if (object)
          {
            return object->getControler<PhysicalObject>(controler->getControlerSet()) ;
          }
          
          return NULL ;
        }
        
        PhysicalWorld* getPhysicalWorld(const Kernel::BaseControler* controler)
        {
          PhysicalObject* object = getPhysicalObject(controler) ;
          Kernel::Object* parent = object ? object->getObject()->getParent() : NULL ;

          if (parent)
          {
            Model::PhysicalWorld* 
                world = parent->getParent<Model::PhysicalWorld>() ;
            
            return world ? world->getControler<PhysicalWorld>(controler->getControlerSet()) : NULL ;
          }
          
          return NULL ;
          
        }
      }
    }
  }
}
