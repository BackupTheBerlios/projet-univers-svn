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

#include <base/derive_de.h>

//#include <base/objet.h>
//#include <base/valeur.h>

namespace ProjetUnivers {

  namespace Base {


    template <class OBJET, typename VALEUR> 
    FonctionObjetValeur<OBJET,VALEUR>::FonctionObjetValeur()
    : fonction()
    {
//      DeriveDe<OBJET, ProjetUnivers::Base::Objet>() ;
//      DeriveDe<VALEUR, ProjetUnivers::Base::Valeur>() ;
    }
    
    template <class OBJET, typename VALEUR> 
    FonctionObjetValeur<OBJET,VALEUR>::
    FonctionObjetValeur(const FonctionObjetValeur& _v)
    : fonction(_v.fonction)
    {}
    
    template <class OBJET, typename VALEUR> 
    void FonctionObjetValeur<OBJET,VALEUR>::
    Ajouter(const Association< OBJET >& _cle, const VALEUR& _valeur)
    {
      fonction[_cle.pt] = _valeur ;
    }
    
    template <class OBJET, typename VALEUR> 
    void FonctionObjetValeur<OBJET,VALEUR>::
    Changer(const Association< OBJET >& _cle, const VALEUR& _valeur)
    {
      fonction[_cle.pt] = _valeur ;
    }
    
    template <class OBJET, typename VALEUR> 
    VALEUR FonctionObjetValeur<OBJET,VALEUR>::
    Acces(const Association<OBJET>& _cle) const
    {
      return fonction[_cle.pt] ;
    }
    
    template <class OBJET, typename VALEUR> 
    Booleen FonctionObjetValeur<OBJET,VALEUR>::
    operator==(const FonctionObjetValeur< OBJET,VALEUR >& _right) const
    {
      return fonction == _right.fonction ;
    }




  }
}
