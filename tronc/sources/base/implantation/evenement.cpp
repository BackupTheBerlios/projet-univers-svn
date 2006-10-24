/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#include<base/evenement.h>

namespace ProjetUnivers {
  namespace Base {

    /// Constructeur par défaut.
    Evenement::Evenement()
    {}

    Evenement::Evenement(const Action& _action, 
                         const Chaine& _nom, 
                         const Association<Modele>& _parametre)
    : action(_action), nom(_nom), parametre(_parametre)
    {}
      
      /// Constructeur de copie.
    Evenement::Evenement(const Evenement& _evenement)
    : action(_evenement.action), nom(_evenement.nom), 
      parametre(_evenement.parametre)
    {}
    
    bool Evenement::operator==(const Evenement& _evenement) const
    {
      return action == _evenement.action && nom ==_evenement.nom
              && parametre == _evenement.parametre ;
    }
         
  }
}
