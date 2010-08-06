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
#include <Ogre.h>
#include <kernel/string.h>
#include <display/implementation/ogre/utility.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        namespace Utility
        {
          
          namespace {
            
            int m_number = 0 ;
            
          }
          
          std::string getUniqueName()
          {
            return "PU::Display::Name" + Kernel::toString(m_number++) ;
          }
          
          /*!
            code extracted from http://www.ogre3d.org/wiki/index.php/Line3D.
          */
          ::Ogre::MovableObject* createLine(
              const ::Ogre::Vector3& i_end_point,
              ::Ogre::SceneManager*  i_scene_manager)
          {
             ::Ogre::ManualObject* m_object 
              =  i_scene_manager->createManualObject(getUniqueName()); 
             
             ::Ogre::MaterialPtr material = 
              ::Ogre::MaterialManager::getSingleton().create("manual1Material","debugger"); 
             material->setReceiveShadows(false); 
             material->getTechnique(0)->setLightingEnabled(true); 
             material->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
             material->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
             material->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 
             
             m_object->begin("manual1Material", ::Ogre::RenderOperation::OT_LINE_LIST); 
  
             m_object->position(0,0,0) ; 
             m_object->position(i_end_point[0],i_end_point[1],i_end_point[2]) ; 
  
             m_object->end(); 
             
             return m_object ;
          }

          void setColour(::Ogre::OverlayElement* element,
                         const ::Ogre::ColourValue& colour)
          {
            if (element)
            {
              ::Ogre::MaterialPtr material = element->getMaterial();
              ::Ogre::Technique* technique = material->getTechnique(0);
              ::Ogre::Pass* pass = technique->getPass(0);
              ::Ogre::TextureUnitState* texture = pass->getTextureUnitState(0);
            
              texture->setColourOperationEx(
                    ::Ogre::LBX_MODULATE,
                    ::Ogre::LBS_CURRENT,
                    ::Ogre::LBS_MANUAL,
                    ::Ogre::ColourValue::White,
                    colour) ;
            }
          }

        }
      }
    }
  }
}
