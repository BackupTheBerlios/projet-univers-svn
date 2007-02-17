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
#ifndef PU_MODELE_JEU_JEU_H_
#define PU_MODELE_JEU_JEU_H_

#include <base/association.h>
#include <base/chaine.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Jeu {    

      class Etat ;
      
      /// Initialise le module.
      /*!
      Place dans l'�tat initial.
    
      @par Etat
        planning
      */
      void init() ; 

      /// Termine le module.
      void close() ;

      /// Change d'�tat.
      void Changer(const std::string& _etat) ;
      
      /// Renvoie l'�tat courant.
      Base::Association<Etat> EtatCourant() ;
      
      
    }
  }
}



#endif /*PU_MODELE_JEU_JEU_H_*/
