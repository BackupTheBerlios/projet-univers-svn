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

#include <vector>
#include <base/types.h>
#include <base/implantation/tampon_ensemble_valeur.h>


namespace ProjetUnivers {
  namespace Base {


    template <typename Valeur> class IterateurEnsembleValeur ;

    ///  Représente un ensemble d'élément d'une classe de valeur.
    /*!

    */
    template <typename Valeur> class EnsembleValeur
    {
    public:
    
    
      
    // *************************
    /// @name Construction
    // *************************      
    // @{      
      

      /// Constructeur par défaut.
      
      /// Construit un ensemble vide.
      EnsembleValeur() ; 
    
      /// Constructeur de copie.
      EnsembleValeur(const EnsembleValeur< Valeur >& _e);
    
      /// Ajoute un élément à l'ensemble.
      void Ajouter(const Valeur& _elt);

      /// Ajoute des éléments à l'ensemble.
      void Ajouter(const EnsembleValeur< Valeur >& _elt);
    
      /// Enlève l'élément _el, s'il n'y est pas ne fait rien.
      void Enlever(const Valeur& _el) ;
    
      /// Vide l'ensemble
      void Vider() ;
      
      
    // @}
    // *************************
    /// @name Consultation
    // *************************      
    // @{      
    
      /// Accès au nombre d'éléments.
      EntierPositif NombreDElements() const ;
    
      /// Determine si _el fait partie de l'ensemble.
      Booleen Contient(const Valeur& _el) const ;
      
      /// Egalité de deux ensembles.
      Booleen operator==(const EnsembleValeur<Valeur>& _r) const ;
      

    // @}
    private:

      Implantation::TamponEnsembleValeur<Valeur>* tampon ;

      friend class IterateurEnsembleValeur<Valeur> ;
      
    };
        
  }
}

#include <base/implantation/ensemble_valeur.cxx>

#endif
