//*******************************************************************
//              
//  FILE:       pretty_print.h
//              
//  AUTHOR:     Mathieu ROGER
//              
//  PROJECT:    base
//              
//  COMPONENT:  -
//              
//  DATE:       13.12.2002
//              
//  COMMENTS:   Des définitions pour un affichage joli.
//              
//              
//*******************************************************************


#ifndef PRETTY_PRINT_H_
#define PRETTY_PRINT_H_


// Includes
#include "chaine.h"

/////////////
// passe à la ligne suivante
Chaine EndOfLine() ;

/////////////
// passe à la ligne suivante, augmente l'indentation
Chaine EndOfLineIncreaseIndent() ;

/////////////
// passe à la ligne suivante, diminue l'indentation
Chaine EndOfLineDecreaseIndent() ;


#endif // PRETTY_PRINT_H_
