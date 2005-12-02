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

#ifndef _PU_MODELE_TYPE_OBJET_H_
#define _PU_MODELE_TYPE_OBJET_H_

#include <base/association.h>

#include <modele/nom.h>


namespace ProjetUnivers {

  namespace Modele {

    class Groupe ;
    
    
    /// Un emsemble d'objets.
    /*!
    @par Type de classe
    - Abstraite
    - Objet
    
    */
    class TypeObjet {
    public:
    
      /// Le nom du type.
      Nom AccesNom() const ;
    
      /// Destructeur de classe abstraite.
      virtual ~TypeObjet() ;  
      
    protected:
      
      /// Constructeur de classe abstraite.
      TypeObjet(const Nom&) ;
      
      Nom nom ;
      
      
      /// pas sûr ???
      /*!
        Dans la perspective d'un "tout objet", donc notre propre modèle de 
        données, il convient peut être de mettre un Objet, ayant la propriété 
        d'être un constructeur de pièces.
      */
      // Base::Association<Groupe> constructeur ;
      
    };

  }
}

#endif /*_PU_MODELE_TYPE_OBJET_H_*/
