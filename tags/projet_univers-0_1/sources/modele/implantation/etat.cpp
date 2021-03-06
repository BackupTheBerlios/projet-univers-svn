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


#include <modele/jeu/etat.h>

using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {

  namespace Modele {
    
    namespace Jeu {

      void Etat::Entrer()
      {
      }
      
      void Etat::AjouterSousEtat(Etat* _nouveau)
      {
        this->sousEtats.Ajouter(_nouveau) ;
      }
      
      void Etat::SupprimererSousEtat(const Association< Etat >& _supprime)
      {
        this->sousEtats.Enlever(_supprime) ;
      }
      
      void Etat::ActiverSousEtat(const Association< Etat >& _active)
      {
        /// @todo implanter
      }
      
      Etat::~Etat()
      {}
    
    }  
  }
}


