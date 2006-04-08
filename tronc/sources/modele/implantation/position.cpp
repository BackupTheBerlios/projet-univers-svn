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

#include <modele/position.h>
#include <modele/positionne.h>

namespace ProjetUnivers {

  namespace Modele {


//    Position::Position()
//    {}
     
    Position::Position(const Base::Association<Positionne>& _origine)
    : origine(_origine)
    {
      if (_origine->AccesPosition().origine == _origine)
        referentiel = _origine ;
     
      else
        referentiel = _origine->AccesPosition().referentiel ;
    }


//    Base::Booleen Position::EstOrigine(const Position& _position) const
//    {
//            
//    }

    /*!
      @pre
        _nouvelleOrigine et _position.origine possèdent un ancêtre commun.
    */
    Position::Position(const Position& _position, 
                       const Base::Association<Positionne>& _nouvelleOrigine)
    : origine(_nouvelleOrigine), 
      coordonneeX(),
      coordonneeY(),
      coordonneeZ(),
      referentiel(_nouvelleOrigine->AccesReferentiel())
    {
      
//      Base::Erreur(referentiel == _origine->AccesReferentiel(),
//                   "impossible de recentrer par rapport à un autre référentiel") ;

    }

    Position 
    Position::Relocaliser(const Base::Association<Positionne>& _origine) const
    {
      Position resultat(_origine) ;
      resultat.coordonneeX = coordonneeX ;
      resultat.coordonneeY = coordonneeY ;
      resultat.coordonneeZ = coordonneeZ ;
      resultat.referentiel = _origine->AccesReferentiel() ;
      
      return resultat ;
      
    }


    Position::Position(const Position& _position,
               const Distance& x, 
               const Distance& y, 
               const Distance& z)
    : origine(_position.origine), 
      coordonneeX(x),
      coordonneeY(y),
      coordonneeZ(z),
      referentiel(_position.referentiel)
    {}
      
    
      

    Position::Position(const Position& _position)
    : origine(_position.origine), 
      coordonneeX(_position.coordonneeX),
      coordonneeY(_position.coordonneeY),
      coordonneeZ(_position.coordonneeZ),
      referentiel(_position.referentiel)
    {}


    Base::Booleen Position::operator==(const Position& _position) const
    {
      
    }
      
    Distance Position::CalculerDistance(const Position& _position) const 
    {
      
    }
    
  }
}
