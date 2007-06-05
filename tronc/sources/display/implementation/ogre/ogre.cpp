/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#include <stddef.h>
#include <Ogre.h>

#include <plateform.h>


#include <kernel/log.h>

#include <display/implementation/ogre/ogre.h>


// on pr�fixe avec la racine des namespaces pour 
// qu'il n'y ait pas de confusion
using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers {

  using namespace Kernel ;
  
  namespace Display {
    namespace Implementation {
      namespace Ogre {  
      
        /// le syst�me ogre      
        ::Ogre::Root* root = NULL ;
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre g�re lui m�me sa m�moire et d�truira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit �tre consid�r� comme une association.
        */
        ::Ogre::RenderWindow* window ;
        


        /// le syst�me ogre      
        ::Ogre::Root* getRoot()
        {
          if (root)
          {
            return root ;
          }
          else
          {
            return NULL ;
          }
        }
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre g�re lui m�me sa m�moire et d�truira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit �tre consid�r� comme une association.
        */
        ::Ogre::RenderWindow* getWindow()
        {
          return window ;
        }
        

        size_t getWindowHandle()
        {
          size_t windowHnd = 0;

        // Get window handle
#if PU_PLATEFORM == PU_PLATEFORM_WIN32
          window->getCustomAttribute( "HWND", &windowHnd );
        // Uncomment these two lines to allow users to switch keyboards via the language bar
        //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND") ));
        //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE") ));

#elif PU_PLATEFORM == PU_PLATEFORM_LINUX

          window->getCustomAttribute( "GLXWINDOW", &windowHnd );
#endif
          
          return windowHnd ;
        }

        /// Acc�s � la taille de la fen�tre
        void getWindowSize(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top )
        {
          window->getMetrics( width, height, depth, left, top ) ;
        }
        
        /// Charge les ressources � partir du fichier ressources.cfg
        void loadRessources() 
        {
            
          ConfigFile file ;
          file.load("ressources.cfg") ;

          // On parcours ses sections
          ConfigFile::SectionIterator section = file.getSectionIterator();

          String nomSection, nomType, nomArchitecture ;
          while (section.hasMoreElements())
          {
            nomSection = section.peekNextKey();
            ConfigFile::SettingsMultiMap* settings = section.getNext();
            
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                nomType = i->first;
                nomArchitecture = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(
                    nomArchitecture, nomType, nomSection);
            }
            
          }
        }
        
        
        
        bool displayPiloteChoice()
        {
          // affiche l'�cran de configuration et demande si on continue
          if(root->showConfigDialog())
          {
            return true ;
          }
          else
          {
            return false ;
          }
        }
        
        
        
        bool init() {

      
          // On se cr�e une application Ogre
          // *******************************
          root = new Root() ;
          
          // On charge le fichier de configuration des ressources
          // ****************************************************
          loadRessources() ;
        
          // On laisse l'utilisateur choisir le pilote d'affichage
          bool go_on = displayPiloteChoice() ;
          if (! go_on)
          {
            root = NULL ;
            return false ;
          }

          // on se cr�e une window par d�faut
          window = root->initialise(true) ;

          ResourceGroupManager::getSingleton().initialiseAllResourceGroups() ;
          
          InternalMessage("Ogre launched") ;
          
          // voila, ca a march�
          return true ;
        }

        void close() 
        {
          if (root)
          {
            InternalMessage("stopping Ogre..") ;
            delete root ;
            root = NULL ;  
            InternalMessage("...Ogre stopped") ;
            
          }
          
        }

        /// Rafraichi l'affichage
        /*!
          Met � jour tout ce qui doit �tre affich�. On se sert de cette m�thode 
          pour ne pas passer par la boucle standard de Ogre.
        */
        void update()
        {
          /// cf. http://www.ogre3d.org/phpBB2/viewtopic.php?t=2733
          ::Ogre::PlatformManager::getSingleton().messagePump(window);
          root->_fireFrameStarted();
          window->update() ;
          root->_fireFrameEnded();   
        }
        
         
      }
    }
  }
  
}
