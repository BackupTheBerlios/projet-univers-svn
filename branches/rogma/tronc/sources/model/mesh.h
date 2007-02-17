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

#ifndef _PU_MODELE_MODELE_3D_H_
#define _PU_MODELE_MODELE_3D_H_

#include <base/chaine.h>

namespace ProjetUnivers {
  namespace Model {
    
    
    /// Repr�sente une forme en 3d.
    /*!
    @par Type de classe
    - Valeur
      
    */
    class Model3D
    {
    public:
    
    /*!
      @name Construction
    */
    // @{
    
      /// Constructeur.
      Model3D(const std::string& _nom) ;
      
      /// Constructeur de copie.
      Model3D(const Model3D&) ;
      
            
    // @}
    /*!
      @name Acc�s
    */
    // @{
    
      /// Ac�s au nom.
      std::string AccesNom() const ;
      
            
    // @}

    
    private:
    
      /// Identificateur.
      std::string nom ;
            
    };
    
  }
}

#endif 
