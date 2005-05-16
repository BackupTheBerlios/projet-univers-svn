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

// on pr�fixe avec la racine des namespaces pour 
// qu'il n'y ait pas de confusion
using namespace ::Ogre ;
using namespace std ;

namespace ProjetUnivers {

  using namespace Base ;
  
  namespace Affichage {

    namespace Implantation {
      
      namespace Ogre {  
      
        
        /// le syst�me ogre      
        Base::Composition<Root> systeme ;
        
        /// la fenetre d'affichage
        /*!
          \remark
            C'est un pointeur, Ogre g�re lui m�me sas m�moire et s�truira 
            l'objet lorsqu'on n'en aura plus besoin. Ce pointeur doit �tre 
            consid�r� comme une association.
        */
        RenderWindow* fenetre ;
        
        /// Charge les ressources � partir du fichier ressources.cfg
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
        
        Booleen ChoixPilote()
        {
          // affiche l'�cran de configuration et demande si on continue
          if(systeme->showConfigDialog())
          {
            return VRAI ;
          }
          else
          {
            return FAUX ;
          }
        }
        
        Booleen Initialiser() {
      
          // On se cr�e une application Ogre
          // *******************************
          systeme = new Root() ;
          
          // On charge le fichier de configuration des ressources
          // ****************************************************
          ChargerRessources() ;
        
          // On laisse l'utilisateur choisir le pilote d'affichage
          Booleen continuer = ChoixPilote() ;
          if (! continuer)
          {
            systeme = NULL ;
            return FAUX ;
          }
          
          // on se cr�e une fenetre par d�faut
          fenetre = systeme->initialise(true) ;
          
          // voila, ca a march�
          return VRAI ;
        }

        void Terminer() 
        {
          systeme = NULL ;  
        }

        /// Raffraichi l'affichage
        /*!
          Met � jour tout ce qui doit �tre affich�
        */
        void Raffraichir()
        {
          /// cf. http://www.ogre3d.org/phpBB2/viewtopic.php?t=2733
          systeme->_fireFrameStarted();
          fenetre->update() ;
          systeme->_fireFrameEnded();   
        }
         
      }
    }
  }
  
}
