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

#include <kernel/log.h>

#include <display/view_point.h>
#include <display/implementation/ogre/view_point.h>

#include <display/implementation/ogre/positionned.h>

using namespace ::Ogre ;

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        RegisterView(Ogre::Positionned,Model::Positionned, Ogre::ViewPoint) ;
      
      
      /*!
        @name Méthodes locales
      */  
      // @{
      
        /// Convertit une position en position Ogre
        ::Ogre::Vector3 convert(const Model::Position& _position)
        {
          Model::Distance x(_position.getXCoordinate()) ;
          Model::Distance y(_position.getYCoordinate()) ;
          Model::Distance z(_position.getZCoordinate()) ;
          
          /*!
            Les coordonnées ogre sont codées sur 32 bits. 
            
            Il faut être capable d'ajuster l'échèle par un facteur de 
            conversion, ici on pose : 1 unité Ogre = 1000 mètres.
            
            De plus on pourrait changer de système de coordonnées, Ogre utilise 
            le système suivant : 
            +X = right
            -X = left
            +Y = up
            -Y = down
            +Z = going into the screen
            -Z = going away from the screen
            
            On pourrait par exemple, inverser des axes etc...
            
          */
          
          const float facteurDeConversion = 1000 ;
          
          float XMeters = x.Meter() ;
          float YMeters = y.Meter() ;
          float ZMeters = z.Meter() ;
          
          return ::Ogre::Vector3(XMeters/facteurDeConversion,
                                 YMeters/facteurDeConversion,
                                 ZMeters/facteurDeConversion) ;
          
          
          
        }
      
      // @}
      
        /// Constructeur.
        Positionned::Positionned(Model::Positionned* _object)
        : View<Model::Positionned>(_object), node(NULL)
        {
          Kernel::Log::InternalMessage("Entering Ogre::Positionned::Positionned") ;
          Kernel::Log::InternalMessage("Leaving Ogre::Positionned::Positionned") ;
        }
      
        /// Initialise la vue.
        /*!
        @pre
          La vue correspondant au conteneur à déjà été initialisée.
        */
        void Positionned::init()
        {
          Kernel::Log::InternalMessage("Entering Positionned::init") ;
          
          /*! 
            on crée un noeud qu'on rattache en dessous du conteneur
          */
          if (! this->initialised)
          {
            
            /// On récupère le connteneur et son noeud
            Object* contener(this->getObject()->getContener()) ;
            
            if (contener)
            {
              
              Positionned* parent(contener->getTrait<Positionned>()) ;
        
              node = static_cast<SceneNode*>(parent->node->createChild()) ;

              Kernel::Log::InternalMessage(
                "creating scene node " + node->getName() + 
                " with parent " + parent->node->getName() +
                " with position " + 
                ::Ogre::StringConverter::toString(node->getPosition()) + 
                " with orientation " + 
                ::Ogre::StringConverter::toString(node->getOrientation())
                ) ;

              node->setPosition(convert(observed->getPosition())) ;
              node->setOrientation(observed->getOrientation().getQuaternion()) ;

              Kernel::Log::InternalMessage(
                "modification of scene node " + node->getName() + 
                " with position " + 
                ::Ogre::StringConverter::toString(node->getPosition()) + 
                " with orientation " + 
                ::Ogre::StringConverter::toString(node->getOrientation())
                ) ;


            }
            else
            {
              Kernel::Log::InternalMessage("root node") ;
              
              /// on est à la racine.
              node = this->getViewPoint()->getManager()->getRootSceneNode() ;
            }
            
            this->initialised = true ;
          }

          Kernel::Log::InternalMessage("Leaving Positionned::init") ;

        }

        /// Termine la vue.
        void Positionned::close()
        {
          if (this->initialised)
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->node->getName()) ;
           
            this->initialised = true ;
          }          
        }
        
        /// La position à changé
        /*!
        @par Etat actuel
          terminé
        */
        void Positionned::update(const Kernel::Event&)
        {
          /// on le replace par rapport à son parent
          node->setPosition(convert(observed->getPosition())) ;
          node->setOrientation(observed->getOrientation().getQuaternion()) ;

          Kernel::Log::InternalMessage(
            "modification of scene node " + node->getName() + 
            " with position " + 
            ::Ogre::StringConverter::toString(node->getPosition()) + 
            " with orientation " + 
            ::Ogre::StringConverter::toString(node->getOrientation())
            ) ;
        }

        ::Ogre::SceneNode* Positionned::getNode()
        {
          if (node == NULL)
          {
            this->init() ;
          }
          
          return node ;
        }


      }      
    }
  }
}
