/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#ifndef _PU_BASE_ENSEMBLE_VALEUR_H_
#define _PU_BASE_ENSEMBLE_VALEUR_H_

#include <base/association.h>
#include <base/implantation/liste_valeur.h>
#include <base/implantation/iterateur_liste_valeur.h>

namespace ProjetUnivers {

  namespace Base {


    ///  Représente un ensemble d'élément d'une classe de valeur.
    
    /*!

    */
    template <typename VALEUR> class EnsembleValeur 
            : public Implantation::ListeValeur<VALEUR> {
    public:
    
    
      
      // *************************
      /// @name Construction
      // *************************      
      // @{      
      

      /// Constructeur par défaut.
      
      /// Construit un ensemble vide.
      EnsembleValeur() ; 
    
      /// Constructeur de copie.
      EnsembleValeur(const EnsembleValeur< VALEUR >& _e);
    
      /// Ajoute un élément à l'ensemble.
      void Ajouter(const VALEUR& _elt);

      /// Ajoute des éléments à l'ensemble.
      void Ajouter(const EnsembleValeur< VALEUR >& _elt);
    
      /// Enlève l'élément _el, s'il n'y est pas ne fait rien.
      void Enlever(const VALEUR& _el) ;
    
    
      // @}
      // *************************
      /// @name Consultation
      // *************************      
      // @{      
    
    
      /// Determine si _el fait partie de l'ensemble.
      Booleen Contient(const VALEUR& _el) const ;
      
      /// Egalité de deux ensembles.
      Booleen operator==(const EnsembleValeur<VALEUR>& _r) const ;
      

      // @}      
    };
        
  }
}

#include <base/implantation/ensemble_valeur.cxx>

#endif
