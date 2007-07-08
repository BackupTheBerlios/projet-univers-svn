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
#include <OgreVector3.h>

#include <kernel/log.h>

#include <model/solid.h>

#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/solid.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au mod�le dans ce point de vue
        RegisterView(Ogre::Solid,Model::Solid,Ogre::RealWorldViewPoint) ;


        /// Constructeur.
        Solid::Solid(Model::Solid* i_object,
                     RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Solid,RealWorldViewPoint>(i_object,i_viewpoint), 
          mesh(NULL)
        {}


      //@}
      /*!
        @name Mise � jour
      */
      // @{
      
        /// Cr�e une entit�.
        void Solid::onInit()
        {
          InternalMessage("Entering Solid::onInit") ;

          Positionned* positionned(getView<Positionned>()) ;
          positionned->_init() ;
          
          // build 3D object
          mesh = this->getViewPoint()->getManager()
                  ->createEntity(Utility::getUniqueName(),
                                 getModel()->getMesh().getName()) ;
          
          // put it on the node
          positionned->getNode()->attachObject(mesh) ;
          
          // reset scale factor
          positionned->getNode()->setScale(::Ogre::Vector3(1.0/conversion_factor,
                                                         1.0/conversion_factor,
                                                         1.0/conversion_factor)) ;
          
          InternalMessage("Leaving Solid::onInit") ;
        }
        
        /// D�truit l'entit�.
        void Solid::onClose()
        {
          InternalMessage("Display::Solid::onClose Entering") ;
          /// Positionne doit avoir �t� termin�
          /*!
            @why ???
              try without...
          */
          Positionned* positionned(getView<Positionned>()) ;
          if (positionned)
          {
            positionned->_close() ;
          }  
          
          this->getViewPoint()->getManager()
               ->destroyEntity(mesh) ;

          InternalMessage("Display::Solid::onClose Leaving") ;
        }
      
        /// 
        /*!
        @par Etat
          stub vide
        */
        void Solid::onUpdate()
        {
          
        }


      // @}
    
      }
    }
  }
}
