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

#include <outils/compilateur/utilitaires_opencxx.h>

using namespace ProjetUnivers::Base ;
using namespace Opencxx ;

namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {

      /*!
        Quelques fonctions utiles pour openc++.
      
      */


      /// Test si le membre est un attribut.
      Base::Booleen EstAttribut(Opencxx::Member& _membre)
      {
        return ! _membre.IsFunction() && 
               ! _membre.IsConstructor() &&
               ! _membre.IsDestructor() ;
      }
      
      /// Donne le nom complet d'un namespace.
      /*!
        \remarks 
          marche avec openc++ 2.8.5 (la mienne)
      */
      Base::Chaine NomComplet(Opencxx::Environment* _espaceDeNom)
      {
        Chaine resultat ;
        Opencxx::Environment* espaceDeNom = _espaceDeNom ;
        
        while(espaceDeNom != NULL && espaceDeNom->IsNamespace() != NULL)
        {
          if (resultat == Chaine(""))
            resultat = espaceDeNom->IsNamespace()->ToString() ;
          else
            resultat = Chaine(espaceDeNom->IsNamespace()->ToString()) 
                       + "::" + resultat ;
          
          espaceDeNom = espaceDeNom->GetOuterEnvironment() ;
        }
        
        return resultat ;  
      }
      
      /// Donne le nom complet d'une classe.
      /*!
        \remarks 
          marche avec openc++ 2.8.5 (la mienne)
      */
      Base::Chaine NomComplet(Opencxx::Class* _classe)
      {
        Chaine resultat ;
      
        resultat = 
            NomComplet(_classe->GetEnvironment()->GetOuterEnvironment()) 
            + "::" 
            + _classe->Name()->ToString() ;
      
        return resultat ;
      }
      
      
      

    }
  }
}



