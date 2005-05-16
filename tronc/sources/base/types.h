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

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

#include <limits.h>

// Compileur d�pendant
// mais bien pratique...
//#if _MSC_VER > 1000     // VC++
//#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
//#endif // _MSC_VER > 1000



namespace ProjetUnivers {

  namespace Base {
    
    
    //*************************************
    /// @name D�finition des types de bases
    //*************************************
    // @{
    
        
    /// Type des bool�ens
    typedef unsigned short Booleen ;
    
    /// Type des bool�ens �tendus avec "peut-�tre", les valeurs sont 
    /// VRAI
    /// FAUX
    /// PEUT_ETRE
    typedef float BooleenEtendu ;
    
    /// La valeur faux
    const Booleen FAUX(0) ;
    
    /// La valeur vrai
    const Booleen VRAI(1) ; 

    /// La valeur peut-�tre
    const BooleenEtendu PEUT_ETRE(0.5) ;
    
    
    // @}   
    // ********************
    /// @name Types de base
    // ********************
    // @{
    
    
    /// Type des entiers
    typedef long int Entier ;
    
    /// Entier maximum
    const Entier EntierMaximum = LONG_MAX ;
    
    /// Type des caract�res
    typedef char Caracter ;
    
    
    /// Type des r�els
    typedef double Reel ;
    
    
    // ***************************
    /// @name Types positifs
    // ***************************
    // @{
    
    
    /// Type des entiers positifs.    
    typedef unsigned int EntierPositif ;
    
    /// Type des r�els positifs.
    typedef unsigned long ReelPositif ;


    // @}
    
    // @}
  }
}

#endif










