/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef PU_EXCEPTION_H
#define PU_EXCEPTION_H



#include "chaine.h"


namespace ProjetUnivers {
  
  namespace Base {
  
  
    /*
    CLASS
      Exception
    
      Classe de base des exceptions utilis�es dans le Projet Univers.
    
    
    NOTE
      Il me semble que c'est bisarre d'avoir une classe de valeur abstraite. 
      Eventuellement, s�parer la hi�rarchie � part et mettre une m�thode 
      de copie abstraite.
    */
    class Exception {
    public:
    
      ////////////////
      // Constructeur de copie, le constructeur de copie est obligatoire
      // pour les exceptions.
      Exception(const Exception& x) ;
    
      ////////////////
      // Classe abstraite donc destructeur virtuel.
      virtual ~Exception() ;
    
      ////////////////
      // Message d'erreur correspondant � l'exception.
      Chaine Message() const ;
    
    
    protected:
    
      ////////////////
      // Message associ� � l'exception.
      Chaine		message ;
    
      //////////////////
      // num�ro de l'erreur.
      Entier		numeroErreur ;
    
      ////////////////
      // Classe virtuelle, donc constructeur protected.
      Exception(const Chaine& _message,const EntierNonSigne& numero) ;
    
    };

  }
}

#endif
