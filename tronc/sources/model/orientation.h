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

#ifndef PU_MODEL_ORIENTATION_H_
#define PU_MODEL_ORIENTATION_H_

#include <OgreQuaternion.h>


namespace ProjetUnivers {
  namespace Kernel
  {
    class Object ;
  }
  namespace Model {

    /// Une orientation d'un objet dans l'espace.
    /*!
    C'est un vecteur.
      
      
    */
    class Orientation {
    public:
    
    /// @name Constructeurs
    // @{  

     
      /// Orientation.
      Orientation() ;

      /// Constructeur de copie.
      Orientation(const Orientation&) ;

      Orientation(const Ogre::Quaternion& _orientation) ; 
      
    // @}
      
      Ogre::Quaternion getQuaternion() const ;


    
    private:
    

      /// Origine 
      Kernel::Object* origin ;

      // orientation par rapport à origine.
      Ogre::Quaternion orientation ;
 

  
    };
  }
}



#endif
