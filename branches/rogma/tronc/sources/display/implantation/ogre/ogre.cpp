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

#include <plateforme.h>


#include <base/traceur.h>
#include <base/composition.h>

#include <affichage/implantation/ogre/ogre.h>


// on pr�fixe avec la racine des namespaces pour 
// qu'il n'y ait pas de confusion
using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers {

  using namespace Base ;
  
  namespace Display {
    namespace Implantation {
      namespace Ogre {  
      
        /// le syst�me ogre      
        ::Ogre::Root* racine = NULL ;
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre g�re lui m�me sa m�moire et d�truira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit �tre consid�r� comme une association.
        */
        ::Ogre::RenderWindow* fenetre ;
        


        /// le syst�me ogre      
        Base::Association< ::Ogre::Root > Racine()
        {
          if (racine)
          {
            return *racine ;
          }
          else
          {
            return Base::Association< ::Ogre::Root >() ;
          }
        }
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre g�re lui m�me sa m�moire et d�truira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit �tre consid�r� comme une association.
        */
        ::Ogre::RenderWindow* Fenetre()
        {
          return fenetre ;
        }
        

        size_t DescripteurFenetre()
        {
          size_t windowHnd = 0;

        // Get window handle
#if PU_PLATEFORME == PU_PLATEFORME_WIN32
          fenetre->getCustomAttribute( "HWND", &windowHnd );
        // Uncomment these two lines to allow users to switch keyboards via the language bar
        //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND") ));
        //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE") ));

#elif PU_PLATEFORME == PU_PLATEFORME_LINUX

          fenetre->getCustomAttribute( "GLXWINDOW", &windowHnd );
#endif
          
          return windowHnd ;
        }

        /// Acc�s � la taille de la fen�tre
        void TailleFenetre(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top )
        {
          fenetre->getMetrics( width, height, depth, left, top ) ;
        }
        
        /// Charge les ressources � partir du fichier ressources.cfg
        void loadRessources() 
        {
            
          ConfigFile fichier ;
          fichier.load("ressources.cfg") ;

          // On parcours ses sections
          ConfigFile::SectionIterator section = fichier.getSectionIterator();

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
          ResourceGroupManager::getSingleton().initialiseAllResourceGroups() ;
        }
        
        
        
        Booleen ChoixPiloteDisplay()
        {
          // affiche l'�cran de configuration et demande si on continue
          if(racine->showConfigDialog())
          {
            return VRAI ;
          }
          else
          {
            return FAUX ;
          }
        }
        
        
        
        Booleen init() {
      
          // On se cr�e une application Ogre
          // *******************************
          racine = new Root() ;
          
        
          // On laisse l'utilisateur choisir le pilote d'affichage
          Booleen continuer = ChoixPiloteDisplay() ;
          if (! continuer)
          {
            racine = NULL ;
            return FAUX ;
          }

          // on se cr�e une fenetre par d�faut
          fenetre = racine->initialise(true) ;

          // On charge le fichier de configuration des ressources
          // ****************************************************
          loadRessources() ;
          
          // voila, ca a march�
          return VRAI ;
        }

        void close() 
        {
          if (racine)
          {
            Base::Traceur::MessageInterne("stopping Ogre") ;
            delete racine ;
            racine = NULL ;  
            Base::Traceur::MessageInterne("Ogre stopeed") ;
            
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
          racine->_fireFrameStarted();
          fenetre->update() ;
          racine->_fireFrameEnded();   
        }
         
      }
    }
  }
  
}
