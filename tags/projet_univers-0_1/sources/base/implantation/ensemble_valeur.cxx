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
namespace ProjetUnivers {

  namespace Base {
 
      
      template <typename VALEUR> 
      EnsembleValeur<VALEUR>::EnsembleValeur()
      : Implantation::ListeValeur<VALEUR>()
      {}
    
      /// Constructeur de copie.
      template <typename VALEUR> 
      EnsembleValeur<VALEUR>::EnsembleValeur(const EnsembleValeur<VALEUR>& _e)
      : Implantation::ListeValeur<VALEUR>(_e)
      {}
    
      /// Ajoute un élément à l'ensemble.
      template <typename VALEUR> 
      void EnsembleValeur<VALEUR>::Ajouter(const VALEUR& _elt)
      {
        if (! this->Contient(_elt))
        {
          this->AjouterEnTete(_elt) ;
        }
      }

      /// Ajoute des éléments à l'ensemble.
      template <typename VALEUR> 
      void EnsembleValeur<VALEUR>::Ajouter(const EnsembleValeur<VALEUR>& _elt)
      {
        for(Implantation::IterateurListeValeur<VALEUR> valeur(_elt) ; 
            valeur.Valide() ;
            ++valeur)
        {
          Ajouter(valeur) ;
        }
        
      }
    
      /// Enlève l'élément _el, s'il n'y est pas ne fait rien.
      template <typename VALEUR> 
      void EnsembleValeur<VALEUR>::Enlever(const VALEUR& _el)
      {
        EntierPositif position(Position(_el)) ;
        
        if (position != 0)
        {
          Implantation::ListeValeur<VALEUR>::Enlever(position) ;
        }
      }
    
    
      // @}
      // *************************
      /// @name Consultation
      // *************************      
      // @{      
    
    
      /// Determine si _el fait partie de l'ensemble.
      template <typename VALEUR> 
      Booleen EnsembleValeur<VALEUR>::Contient(const VALEUR& _el) const
      {
        return (this->Position(_el) != 0) ;
      }
    
      /// Egalité de deux ensembles.
      template <typename VALEUR> 
      Booleen EnsembleValeur<VALEUR>::operator==(const EnsembleValeur<VALEUR>& _r) const 
      {
      
      
      }
  
 
  }
}


