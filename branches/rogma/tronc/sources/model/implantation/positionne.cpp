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

#include <modele/objet.h>
#include <modele/positionne.h>


namespace ProjetUnivers {
  namespace Model {


    Positionne::Positionne(const Position& _position)
    : Trait(), position(_position)
    {}

    Positionne::Positionne()
    : Trait(), position()
    {
      
    }

    Position Positionne::AccesPosition() const 
    {
      return position ;
    }

    Orientation Positionne::AccesOrientation() const
    {
      return this->orientation ;
    }


    void Positionne::ModifierOrientation(const Orientation& _orientation)
    {
      this->orientation = _orientation ;
      
      this->Notifier() ;
    }




//    Base::Association<Positionne> Positionne::AccesReferentiel() const
//    {
//      return position.referentiel ;
//    }
    
//    Base::Booleen 
//    Positionne::MemeReferentiel(const Base::Association<Positionne>& _objet) const
//    {
//      if (this->AccesPosition().referentiel 
//          == 
//          _objet->AccesPosition().referentiel)
//      
//        return Base::VRAI ;
//        
//      else
//      
//        return Base::FAUX ;
//      
//    }
    
  }
}
