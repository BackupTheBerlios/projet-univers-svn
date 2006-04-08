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


#include <base/joli_affichage.h>
#include <base/ensemble_composition.h>
#include <base/iterateur_ensemble_composition.h>

#include <modele/gestionnaire_objets.h>
#include <modele/objet.h>
#include <modele/exception.h>


namespace ProjetUnivers {

  namespace Modele {
    
    namespace GestionnaireObjets {

    /*!
      @name Variables du module.
    */
    // @{

      Base::EnsembleComposition<Objet> objets ;


    // @}

      Base::Association<Objet> Ajouter(Objet* _objet)
      {
        if (_objet != NULL)
        {
          Objet& reference = *_objet ;
          objets.Ajouter(_objet) ;
          return reference ;
        }
        
        throw Exception("GestionnaireObjets::Ajouter appelé sans objet") ;
      }
      
      Objet* Enlever(const Base::Association<Objet>& _objet)
      {
      }

      Base::Chaine AfficherObjets()
      {
        Base::Chaine resultat ;
        resultat += "<GestionnaireObjets>" ;
        resultat += Base::FinDeLigne() ;
        Base::AugmenteIndentation() ;

        for(Base::IterateurEnsembleComposition<Objet> objet(objets) ;
            objet.Valide() ;
            ++objet)
        {
          resultat += objet->AfficherDefinition() ;
        }
        
        Base::DiminueIndentation() ;
        resultat += Base::AfficheEspaces() ;
        resultat += "</GestionnaireObjets>" ;
        resultat += Base::FinDeLigne() ;
        
        return resultat ;
      }
      
//      void CreerInstance(const Base::Association<TypeObjet>&)
//      {
//      }
      


//      void Ajouter(TypeContrainte*) ;
//      void Ajouter(TypeObjet*) ;
                             

      
            
    }

    

  }

}
