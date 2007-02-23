
#ifndef PU_OUTILS_COMPILATEUR_TEST_BASE_H
#define PU_OUTILS_COMPILATEUR_TEST_BASE_H


namespace ProjetUnivers
{

  namespace Base 
  {
  
    class Valeur
    {} ;

    class Objet
    {} ;

    
    template <class T, int nombre> class TempAvecNombre
    {};

    template <class T, int nombre, class U> class TempAvecTroisParametres
    {};

    template <class T, class U> class FonctionObjetValeur
    {};

    
  }
}

#endif
