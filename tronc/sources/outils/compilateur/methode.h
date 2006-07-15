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



#ifndef _PU_COMPILATEUR_METHODE_H_
#define _PU_COMPILATEUR_METHODE_H_



#include <outils/compilateur/traitement.h>


namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
  
      /// Repr�sente une m�thode.
      /*!
        Une m�thode est d�clar�e dans une classe.
        
        @remark
        
          Certaines m�thodes (les m�thodes virtuelles) sont en faites d�clar�es 
          sur des profils ayant des "sous-profils"
      */
      class Methode : public Traitement
      {
      public:

        /// Faux constructeur.
        static Methode* Construire(const Member& _membre) ;
        

        /*!
          @name V�rification des r�gles
        */
        //@{
        
        /// Dit si elle v�rifie les r�gles
        virtual bool VerifieRegles() const = 0 ;

        //@}

        /// Destructeur de classe abstraite.
        virtual ~Methode() ;

        
      protected:
      
        /*!
          @name Construction
        */
        //@{
        
        /// Constructeur de classe abstraite.
        Methode(const Member& _membre) ;

        //@}
      
        /// Classe de d�claration de la m�thode.
        Opencxx::Class* Classe() ;
        
      };
    }
  }
}

#endif

