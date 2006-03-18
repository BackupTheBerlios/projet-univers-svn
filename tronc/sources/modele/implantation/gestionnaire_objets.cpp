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

#include <base/ensemble_composition.h>

#include <modele/gestionnaire_objet.h>
#include <modele/objet.h>



namespace ProjetUnivers {

  namespace Modele {
    
    namespace GestionnaireObjets {

      /*!
        @name Variables du module.
      */
      // @{

      Base::EnsembleComposition<Objet> objets ;


      // @}

      void Ajouter(Objet* _objet)
      {
        objets.Ajouter(_objet) ;
      }
      
      Objet* Enlever(const Base::Association<Objet>& _objet)
      {
      }

      
//      void CreerInstance(const Base::Association<TypeObjet>&)
//      {
//      }
      


//      void Ajouter(TypeContrainte*) ;
//      void Ajouter(TypeObjet*) ;
                             

      
            
    }

    

  }

}
