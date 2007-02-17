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
#include <base/traceur.h>

#include <modele/position.h>
#include <modele/positionne.h>

#include <modele/objet.h>

namespace ProjetUnivers {

  namespace Model {


    Position::Position()
    {}

    Position::Position(const Position& _position)
    : coordonneeX(_position.coordonneeX),
      coordonneeY(_position.coordonneeY),
      coordonneeZ(_position.coordonneeZ)
    {}

    Position::Position(const Distance& x, 
                       const Distance& y, 
                       const Distance& z)
    : coordonneeX(x),
      coordonneeY(y),
      coordonneeZ(z)
    {}

    Distance Position::AccesCoordonneeX() const
    {
      return this->coordonneeX ;
    }

    Distance Position::AccesCoordonneeY() const
    {
      return this->coordonneeY ;
    }
    
    Distance Position::AccesCoordonneeZ() const
    {
      return this->coordonneeZ ;
    }
 
/*!
  @todo 
    implanter
*/
//    Base::Booleen Position::operator==(const Position& _position) const
//    {
//      
//    }
//      
//    Distance Position::CalculerDistance(const Position& _position) const 
//    {
//      
//    }

/*!
  @name obsolete
  @todo supprimer
*/

     
//    Position::Position(const Base::Association<Positionne>& _origine)
//    : origine(_origine)
//    {
//      /// on a une boucle infinie dans le cas 
//      Base::Traceur::MessageInterne("Position#1") ;
//      Base::Traceur::MessageInterne("origine = " + std::string((int)_origine->AccesPosition().origine) ) ;
//            
//      if (_origine->AccesPosition().origine == _origine)
//      {
//        Base::Traceur::MessageInterne("l'objet est son propre referentiel") ;
//        referentiel = _origine ;
//      }
//      else
//      {
//        Base::Traceur::MessageInterne("l'objet n'est pas son propre referentiel") ;
//        referentiel = _origine->AccesPosition().referentiel ;
//      }
//    }
//
//    /*!
//      @pre
//        _nouvelleOrigine et _position.origine possèdent un ancêtre commun.
//    */
//    Position::Position(const Position& _position, 
//                       const Base::Association<Positionne>& _nouvelleOrigine)
//    : origine(_nouvelleOrigine), 
//      coordonneeX(),
//      coordonneeY(),
//      coordonneeZ(),
//      referentiel(_nouvelleOrigine->AccesReferentiel())
//    {
//      Base::Traceur::MessageInterne("Position#2") ;
      
//      Base::Erreur(referentiel == _origine->AccesReferentiel(),
//                   "impossible de recentrer par rapport à un autre référentiel") ;

//    }
//
//    Position 
//    Position::Relocaliser(const Base::Association<Positionne>& _origine) const
//    {
//      Position resultat(_origine) ;
//      resultat.coordonneeX = coordonneeX ;
//      resultat.coordonneeY = coordonneeY ;
//      resultat.coordonneeZ = coordonneeZ ;
//      resultat.referentiel = _origine->AccesReferentiel() ;
//      
//      return resultat ;
//      
//    }
//

//    Position::Position(const Position& _position,
//               const Distance& x, 
//               const Distance& y, 
//               const Distance& z)
//    : origine(_position.origine), 
//      coordonneeX(x),
//      coordonneeY(y),
//      coordonneeZ(z),
//      referentiel(_position.referentiel)
//    {
//      Base::Traceur::MessageInterne("Position#3") ;
//    
//    }
    
  }
}
