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


namespace ProjetUnivers {

  namespace Modele {

    Position Objet::AccesPosition() const 
    {
      return position ;
    }

    Base::Association<Objet> Objet::AccesReferentiel() const
    {
      return position.referentiel ;
    }

    
    Objet::~Objet()
    {}
    
    Objet::Objet()
    : position(Position(*this)), orientation()
    {}

    Objet::Objet(const Position& _position)
    : position(_position), orientation()
    {}

    Base::Booleen 
    Objet::MemeReferentiel(const Base::Association<Objet>& _objet) const
    {
      if (this->AccesPosition().referentiel == _objet->AccesPosition().referentiel)
      
        return Base::VRAI ;
        
      else
      
        return Base::FAUX ;
      
    }


  }
}

