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
#include <modele/attribut_inexistant.h>
#include <modele/valeur.h>
#include <base/joli_affichage.h>

namespace ProjetUnivers {

  namespace Modele {


    
    Objet::~Objet()
    {}
    
    Objet::Objet()
    {}

    Objet::Objet(const Nom& _nom)
    : nom(_nom)
    {}

    Base::Chaine Objet::AfficherReference() const
    {
      Base::Chaine resultat ;

      resultat += Base::AfficheEspaces() ;
      resultat += "<objet nom=\"" ;
      resultat += nom ;
      resultat += "\"/>" ;
      resultat += Base::FinDeLigne() ;
      
      return resultat ;
      
    }
    
    Base::Chaine Objet::AfficherDefinition() const
    {
      Base::Chaine resultat ;

      resultat += Base::AfficheEspaces() ;
      resultat += "<objet nom=\"" ;
      resultat += nom ;
      resultat += "\">" ;
      resultat += Base::FinDeLigne() ;
      resultat += Base::AfficheEspaces() + "</objet>" + Base::FinDeLigne() ;
      
      return resultat ;
      
    }



//    Valeur 
//    Objet::AccesAttributLocal(const Base::Chaine& _nomAttribut) const 
//    throw(AttributInexistant)
//    {
//      
//      /// recherche dans les attributs codés en dur
//      if (_nomAttribut == "nom")
//        return this->nom ;
//      if (_nomAttribut == "identificateur")
//        return this->identificateur ;
//      
//      /// recherche dans les attributs variables
//      
//      /// on n'a pas trouvé
//      throw AttributInexistant(_nomAttribut) ;
//    }


  }
}

