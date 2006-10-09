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


#ifndef _PU_AFFICHAGE_EXCEPTION_H_
#define _PU_AFFICHAGE_EXCEPTION_H_

#include <base/chaine.h>

namespace ProjetUnivers {

  namespace Affichage {

    /// Erreurs dans Affichage.
    class Exception
    {
    public:
    
      /// Constructeur de copie.
      Exception(const Exception&) ;
      
      /// Construction.
      Exception(const Base::Chaine&) ;
      
      virtual ~Exception() ;
    
    protected:
    
      /// Message de l'erreur.
      Base::Chaine message ;
    

    };

  }
}

#endif /*_PU_AFFICHAGE_EXCEPTION_H_*/
