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
#include <base/iterateur_ensemble_valeur.h>

namespace ProjetUnivers {
  namespace Base {
 
      
    template <typename Valeur> 
    EnsembleValeur<Valeur>::EnsembleValeur()
    : tampon(new Implantation::TamponEnsembleValeur<Valeur>())
    {}
  
    /// Constructeur de copie.
    template <typename Valeur> 
    EnsembleValeur<Valeur>::EnsembleValeur(const EnsembleValeur<Valeur>& _e)
    : tampon(_e.tampon->Prendre())
    {}

    template <typename Valeur> 
    void EnsembleValeur<Valeur>::Vider()
    {
      if (tampon->Laisser())
        delete tampon ;
        
      tampon = new Implantation::TamponEnsembleValeur<Valeur>() ;
      
    }
    
    /// Ajoute un élément à l'ensemble.
    template <typename Valeur> 
    void EnsembleValeur<Valeur>::Ajouter(const Valeur& _elt)
    {
      if (tampon->nombreDeReferences == 1)
      {
        if (! Contient(_elt))
        {
          tampon->ensemble.push_back(_elt) ;
        }
      }
      else
      {

        if (! Contient(_elt))
        {
          Implantation::TamponEnsembleValeur<Valeur>* nouveauTampon 
             = new Implantation::TamponEnsembleValeur<Valeur>(*tampon) ;

          if (tampon->Laisser())
            delete tampon ;
          
          tampon = nouveauTampon ;

          tampon->ensemble.push_back(_elt) ;
        }      
      }
    }

    /// Ajoute des éléments à l'ensemble.
    template <typename Valeur> 
    void EnsembleValeur<Valeur>::Ajouter(const EnsembleValeur<Valeur>& _elt)
    {
      for(IterateurEnsembleValeur<Valeur> valeur(_elt) ; 
          valeur.Valide() ;
          ++valeur)
      {
        Ajouter(valeur) ;
      }
      
    }
  
    /// Enlève l'élément _el, s'il n'y est pas ne fait rien.
    template <typename Valeur> 
    void EnsembleValeur<Valeur>::Enlever(const Valeur& _el)
    {
      typename std::vector<Valeur>::iterator position ;
      bool trouve = false ;
      for(typename std::vector<Valeur>::iterator i = tampon->ensemble.begin() ; 
          !trouve && i != tampon->ensemble.end() ;
          ++i)
      {
        if (*i == _el)
        {
          trouve = true ;
          position = i ;
        }
      }    
     
      if (trouve)
      {
        if (tampon->nombreDeReferences != 1) 
        {
          Implantation::TamponEnsembleValeur<Valeur>* nouveauTampon 
             = new Implantation::TamponEnsembleValeur<Valeur>(*tampon) ;

          if (tampon->Laisser())
            delete tampon ;
          
          tampon = nouveauTampon ;

        }

        tampon->ensemble.erase(position) ;
      }
    }
  
  
    // @}
    // *************************
    /// @name Consultation
    // *************************      
    // @{      
  
  
    /// Determine si _el fait partie de l'ensemble.
    template <typename Valeur> 
    Booleen EnsembleValeur<Valeur>::Contient(const Valeur& _el) const
    {
      
      for(typename std::vector<Valeur>::iterator i = tampon->ensemble.begin() ; 
      i != tampon->ensemble.end() ;
          ++i)
      {
        if (*i == _el)
          return VRAI ;
      }    
      return FAUX ;    
    }
  
    /// Egalité de deux ensembles.
    template <typename Valeur> 
    Booleen EnsembleValeur<Valeur>::operator==(const EnsembleValeur<Valeur>& _r) const 
    {
      return tampon->ensemble == _r.tampon->ensemble ;
    }
  
    template <typename Valeur> 
    EntierPositif 
    EnsembleValeur<Valeur>::
    NombreDElements() const 
    {
      return tampon->ensemble.size() ;
    }
 
  }
}


