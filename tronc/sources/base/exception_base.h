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


#ifndef PU_EXCEPTION_BASE_H
#define PU_EXCEPTION_BASE_H



#include "chaine.h"

#include "exception.h"


namespace ProjetUnivers {
  
  namespace Base {
  
  
    /*
    CLASS
      ExceptionBase
    
      Classe des exceptions utilis�es dans le module Base.
    
    
    */
    class ExceptionBase : public Exception {
    public:

      ////////////////
      // Constructeur.
      ExceptionBase(const Chaine& _message) ;

      ////////////////
      // Constructeur de copie, le constructeur de copie est obligatoire
      // pour les exceptions.
      ExceptionBase(const ExceptionBase& x) ;
    
      ////////////////
      // Message d'erreur correspondant � l'exception.
      Chaine Message() const ;
    
    
    protected:
    
    
    
    };

  }
}

#endif
