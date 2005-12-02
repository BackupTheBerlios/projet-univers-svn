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

#ifndef _PU_MODELE_OBJET_PHYSIQUE_H_
#define _PU_MODELE_OBJET_PHYSIQUE_H_

#include <modele/objet.h>

#include <modele/position.h>
#include <modele/vitesse.h>
#include <modele/acceleration.h>
#include <modele/orientation.h>


namespace ProjetUnivers {

  namespace Modele {

    
    /// Classe des objets physiques du monde.
    
    /*!
      Un objet du monde fait de matière.
      
      Par opposition aux objets abstraits du monde.
        \see ObjetAbstrait.
    */
    class ObjetPhysique : public Objet 
    {
    public:
    
      // **********************
      /// @name Constructeur/Destructeur
      // **********************
      // @{

      /// Classe abstraite donc destructeur virtuel.
      virtual ~ObjetPhysique() ;
    
    protected:
    
      /// Classe abstraite donc constructeur protégé.
      ObjetPhysique(const Position&) ;
      ObjetPhysique() ;
    
    
      // @}
      // **********************
      /// @name Attributs    
      // **********************
      // @{
      
      
      /// Vitesse
      Vitesse vitesse ;
      
      
      /// Vitesse de rotation
      // VitesseRotation vitesseRotation ;
            
      //@}
      
      /// @name Attributs Déduits
      // @{
      
      /// Accélération
      Acceleration acceleration ;
      
      //@}


  
    };
  }
}
#endif
