// pretty_print.cpp

#include "pretty_print.h"
#include "exception.h"


////////////////
// Indentation courante, initialis�e � 0
EntierNonSigne indentation(0) ;

//////////////
// D�calage, � ajouter o� � soustraire
EntierNonSigne tabulation(2) ;

////////////////
// fonction locale d'affichage de indentation espaces
Chaine afficheEspaces() {

  Chaine resultat ;

  // on ajoute des espaces
  for(EntierNonSigne i(0) ; i < indentation ; ++i)
    
    resultat += " " ;

  return resultat ;
}


Chaine EndOfLine()
{
  return "\n" + afficheEspaces() ;
}

Chaine EndOfLineIncreaseIndent()
{
	// on accroit l'indentation
  indentation = indentation + tabulation ;
 
  return EndOfLine() ;
}

Chaine EndOfLineDecreaseIndent()
{
	// on d�croit l'indentation
  if (indentation < tabulation)

    throw Exception("_pretty_printing error : cannot decrease indentation anymore") ;

  indentation = indentation - tabulation ;
 
  return EndOfLine() ;

}
