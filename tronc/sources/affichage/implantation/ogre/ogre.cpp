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

#include <affichage/implantation/ogre/ogre.h>
#include <base/composition.h>
#include <Ogre.h>

// on préfixe avec la racine des namespaces pour 
// qu'il n'y ait pas de confusion
using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers {

  using namespace Base ;
  
  namespace Affichage {

    namespace Implantation {
      
      namespace Ogre {  
      
        
        /// Charge les ressources à partir du fichier ressources.cfg
        void ChargerRessources() 
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
          
        }
        
        
        
        Booleen ChoixPiloteAffichage()
        {
          // affiche l'écran de configuration et demande si on continue
          if(racine->showConfigDialog())
          {
            return VRAI ;
          }
          else
          {
            return FAUX ;
          }
        }
        
        
        
        Booleen Initialiser() {
      
          // On se crée une application Ogre
          // *******************************
          racine = new Root() ;
          
          // On charge le fichier de configuration des ressources
          // ****************************************************
          ChargerRessources() ;
        
          // On laisse l'utilisateur choisir le pilote d'affichage
          Booleen continuer = ChoixPiloteAffichage() ;
          if (! continuer)
          {
            racine = NULL ;
            return FAUX ;
          }
          
          // on se crée une fenetre par défaut
          fenetre = racine->initialise(true) ;
          
          // un manager
          gestionnaire = racine->createSceneManager(ST_GENERIC) ;
          
          // voila, ca a marché
          return VRAI ;
        }

        void Terminer() 
        {
          racine = NULL ;  
        }

        /// Raffraichi l'affichage
        /*!
          Met à jour tout ce qui doit être affiché. On se sert de cette méthode 
          pour ne pas passer par la boucle standard de Ogre.
        */
        void Raffraichir()
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
