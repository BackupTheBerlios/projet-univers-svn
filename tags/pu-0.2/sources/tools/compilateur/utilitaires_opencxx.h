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



#ifndef _PU_COMPILATEUR_UTILITAIRES_OPENCXX_H_
#define _PU_COMPILATEUR_UTILITAIRES_OPENCXX_H_

#include <opencxx/mop.h>


#include <base/types.h>
#include <base/chaine.h>


namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {

      /*!
        Quelques fonctions utiles pour openc++.
      
      */


      /// Test si le membre est un attribut.
      Base::Booleen EstAttribut(Opencxx::Member& _membre) ;
      
      /// Donne le nom complet d'un namespace.
      /*!
        \remarks 
          marche avec openc++ 2.8.5 (la mienne)
      */
      Base::Chaine NomComplet(Opencxx::Environment* _espaceDeNom) ;
      
      /// Donne le nom complet d'une classe.
      /*!
        \remarks 
          marche avec openc++ 2.8.5 (la mienne)
      */
      Base::Chaine NomComplet(Opencxx::Class* _classe) ;
      
      
      /// Recherche une classe dans l'environement spécifié
      /*!
        Est capable de traiter les identificateurs de classes avec parcours 
        de namespaces.
      */
//      ::Opencxx::Class* RechercheClasse(::Opencxx::Environment* _environement, 
//                                        ::Opencxx::Ptree* _identificateur) ;
      
      

    }
  }
}



#endif //_PU_COMPILATEUR_UTILITAIRES_OPENCXX_H_
