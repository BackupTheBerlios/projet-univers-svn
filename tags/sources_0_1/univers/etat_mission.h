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

#ifndef _PU_UNIVERS_ETAT_MISSION_H_
#define _PU_UNIVERS_ETAT_MISSION_H_

#include "association.h"
#include "etat.h"


namespace ProjetUnivers {

  namespace Univers {
    
    using namespace ProjetUnivers::Base ;
    using namespace ProjetUnivers::Noyau ;
  
    class Mission ;
    
    /*
    CLASS
      EtatMission
      
      Repr�sente le fait de jouer une mission.

    TYPE_DE_CLASSE
      Objet
      Concret
      
    */
    class EtatMission : public Etat {
    public:


      ////////////////////
      // Initialisation de l'�tat.
      // Construction des controles.
      virtual void Initialiser() ;
      
      //////////////////////
      // Terminaison de l'�tat, r�aliser � la sortie
      virtual void Finaliser() ;

      
    private:

      // ****************
      // GROUP: Attributs
      // ****************
      
      
      /////////////////
      // La mission jou�e
      Association< Mission > mission ; 

    };
    
    
  }

}

#endif
