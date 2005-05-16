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

#ifndef _PU_AFFICHAGE_VUE_PERSONNAGE_H_
#define _PU_AFFICHAGE_VUE_PERSONNAGE_H_

#include <base/association.h>
#include <affichage/point_de_vue.h>
#include <Ogre.h>

namespace ProjetUnivers {

  // D�claration en-avant.
  namespace Modele { 
    class Personnage ;
  }

  namespace Affichage {


    /// Le point de vue subjectif d'un personnage.
    /*!
      C'est la vue � la premi�re personne d'un personnage.
      
      Type de classe :
        - Objet
        - Concret
    */
    class VuePersonnage : public PointDeVue {
    public:
    
      // *******************
      /// @name Construction 
      // *******************
      // @{
      
      
      /// Constructeur.
      
      /*!
        Construit tout ce qu'il ya � construire.
      */
      VuePersonnage(const Base::Association< Modele::Personnage >& _personnage) ;
      
      
      // @}
      // *******************
      /// @name ??? 
      // *******************
      // @{
      
      
      /// Notification du changement du mod�le.
      virtual void NotifierChangement() ;
      
      /// Afficher la vue.
      void Afficher() ;
        
    
      // @}
    
    private:
    
      /// construit le point de vue.
      
      /*!
      */
      void Construire() ;
    
      /// Le personnage qui voit.
      Base::Association< Modele::Personnage > personnage ;
      
      
    };
  }
}


#endif
