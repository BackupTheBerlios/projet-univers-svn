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

#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positionned.h>

using namespace ::Ogre ;

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        RegisterView(Ogre::Positionned,Model::Positionned, Ogre::RealWorldViewPoint) ;
      
      
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
        Positionned::Positionned(Model::Positionned* i_object,
                                 RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Positionned,RealWorldViewPoint>(i_object,i_viewpoint), 
          node(NULL)
        {
          InternalMessage("Entering Ogre::Positionned::Positionned") ;
          InternalMessage("Leaving Ogre::Positionned::Positionned") ;
        }
      
        /// Initialise la vue.
        /*!
        @pre
          La vue correspondant au conteneur à déjà été initialisée.
        */
        void Positionned::onInit()
        {
          InternalMessage("Entering Positionned::init") ;
          
          /*! 
            on crée un noeud qu'on rattache en dessous du conteneur
          */
            
          /// On récupère le connteneur et son noeud
          Kernel::Object* contener(getObject()->getParent()) ;
          
          if (contener)
          {
            
            Positionned* parent(contener->getView<Positionned>(viewpoint)) ;
      
            node = static_cast<SceneNode*>(parent->node->createChild()) ;

            InternalMessage(
              "creating scene node " + node->getName() + 
              " with parent " + parent->node->getName() +
              " with position " + 
              ::Ogre::StringConverter::toString(node->getPosition()) + 
              " with orientation " + 
              ::Ogre::StringConverter::toString(node->getOrientation())
              ) ;

            node->setPosition(convert(getModel()->getPosition())) ;
            node->setOrientation(getModel()->getOrientation().getQuaternion()) ;

            InternalMessage(
              "modification of scene node " + node->getName() + 
              " with position " + 
              ::Ogre::StringConverter::toString(node->getPosition()) + 
              " with orientation " + 
              ::Ogre::StringConverter::toString(node->getOrientation())
              ) ;


          }
          else
          {
            InternalMessage("root node") ;
            
            /// on est à la racine.
            node = this->getViewPoint()->getManager()->getRootSceneNode() ;
          }
          

          InternalMessage("Leaving Positionned::init") ;

        }

        /// Termine la vue.
        void Positionned::onClose()
        {
          InternalMessage("Display::Positionned::onClose Entering") ;
          
          /*!
            Ogre seams to refuse destroying root node !
          */
          if (getObject()->getParent())
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->node->getName()) ;
          }
          InternalMessage("Display::Positionned::onClose Leaving") ;
        }
        
        /// La position à changé
        /*!
        @par Etat actuel
          terminé
        */
        void Positionned::onUpdate()
        {
          /// on le replace par rapport à son parent
          node->setPosition(convert(getModel()->getPosition())) ;
          node->setOrientation(getModel()->getOrientation().getQuaternion()) ;

          InternalMessage(
            "modification of scene node " + node->getName() + 
            " with position " + 
            ::Ogre::StringConverter::toString(node->getPosition()) + 
            " with orientation " + 
            ::Ogre::StringConverter::toString(node->getOrientation())
            ) ;
        }

        void Positionned::onChangeParent(Kernel::Object* i_old_parent)
        {
          if (i_old_parent)
          {
            Positionned* parent = i_old_parent->getView<Positionned>(viewpoint) ;
            parent->getNode()->removeChild(node) ;
          }

          if (getObject()->getParent())
          {
            Positionned* parent = getObject()->getParent()->getView<Positionned>(viewpoint) ;
            parent->getNode()->addChild(node) ;
          }
          else
          {
            /// error cannot create another root scene node
            ErrorMessage("cannot create another root node") ;
          }
        }
        ::Ogre::SceneNode* Positionned::getNode()
        {
          if (node == NULL)
          {
            this->_init() ;
          }
          
          return node ;
        }


      }      
    }
  }
}
