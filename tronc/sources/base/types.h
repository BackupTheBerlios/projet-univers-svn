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

#ifndef _O_TYPES_H_
#define _O_TYPES_H_

#include <limits.h>

// Compileur dépendant
// mais bien pratique...
#if _MSC_VER > 1000     // VC++
#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
#endif // _MSC_VER > 1000



namespace ProjetUnivers {

  namespace Base {
    
    
    //*************************************
    // GROUP: Définition des types de bases
    //*************************************
    
    #ifndef Bool
    //////////////////
    // Type des booléens
    typedef unsigned short Booleen ;
    
    #endif
    
    #ifndef FALSE
    const Booleen FAUX(0) ;
    #endif
    
    #ifndef TRUE
    const Booleen VRAI(1) ; 
    #endif
    
    //////////////////
    // Type des booléens étendus avec "peut-être", les valeurs sont 
    // VRAI
    // FAUX
    // PEUTETRE
    typedef float BooleenEtendu ;
    
    
    #ifndef MAYBE
    const BooleenEtendu PEUTETRE(0.5) ;
    #endif
    
    
    
    // ********************
    // GROUP: Types de base
    // ********************
    
    
    //////////////////
    // Type des entiers
    typedef long int Entier ;
    
    /////////////////
    // Entier maximum
    const Entier EntierMaximum = LONG_MAX ;
    
    //////////////////
    // Type des caractères
    typedef char Caracter ;
    
    
    //////////////////
    // Type des réels
    typedef double Reel ;
    
    
    // ***************************
    // GROUP: Types non signés, i.e., positifs
    // ***************************
    
    typedef unsigned int EntierNonSigne ;
    typedef unsigned char CaractereNonSigne ;
    typedef unsigned long ReelNonSigne ;

  }
}

#endif










