// o_types.h

#ifndef _O_TYPES_H_
#define _O_TYPES_H_

#include <limits.h>

// Compileur dépendant
// mais bien pratique...
#if _MSC_VER > 1000     // VC++
#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
#endif // _MSC_VER > 1000



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

#endif










