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


#ifndef _PU_AFFICHAGE_IMPLANTATION_OGRE_PLANETOIDE_H_
#define _PU_AFFICHAGE_IMPLANTATION_OGRE_PLANETOIDE_H_

#include <Ogre.h>

#include <base/association.h>


namespace ProjetUnivers {
   
  namespace Affichage 
  {

    namespace Implantation 
    {

      namespace Ogre 
      {
      

        /// Partie affichage d'un planetoide dans lme moteur Ogre3d.
        /*!
          
        
        */
        class Planetoide : public Base::Vue<Modele::Planetoide>
        {
        public:

        
          /// Constructeur.
          Planetoide(const Base::Association< Modele::Planetoide>& _planetoide) ;
          
          /*!
            @name Raffraichissement
            
                        
          */  
          // @{
          
          
          /// Le modèle a changé, on réactualise la vue.
          virtual void Raffraichir() ;
          
            
          // @}
          
         
        private:
          
          /// Modèle 3D du planetoide
          ::Ogre::Mesh* modele ;
          
          /// entité 3D
          ::Ogre::Entity entite ;
          
          
        };
  
        /// Construction.
//        Planetoide* Construire(
//          const Base::Association< Modele::Planetoide>& _planetoide) ;
  
      }
    }    

  }
}

#endif //_AFFICHAGE_IMPLANTATION_PLANETOIDE_H_
