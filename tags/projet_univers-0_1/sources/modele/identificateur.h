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
#ifndef _PU_MODELE_IDENTIFICATEUR_H_
#define _PU_MODELE_IDENTIFICATEUR_H_

#include <base/types.h>
#include <base/chaine.h>

namespace ProjetUnivers {
  namespace Modele {
    
    
    /*!
    @par Etat
      planning
    @deprecated ??
    */
    class Identificateur
    {
    public:
      
      /// Construit un nouvel identificateur.
      Identificateur() ;
      
      /// Constructeur de copie.
      Identificateur(const Identificateur&) ;
    
      /// Conversion en entier.
      operator Base::EntierPositif() const ;
      operator Base::Chaine() const ;
      
    private:
      
      Base::EntierPositif valeur ;
      
      static Base::EntierPositif DerniereValeurUtilisee ;
      
    };
    
  }
}


#endif 
