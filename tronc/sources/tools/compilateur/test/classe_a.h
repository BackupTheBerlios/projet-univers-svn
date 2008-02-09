
#ifndef PU_OUTILS_COMPILATEUR_TEST_CLASSE_A_H
#define PU_OUTILS_COMPILATEUR_TEST_CLASSE_A_H

#include <base/types.h>

#include "base.h"

namespace ProjetUnivers {
  
  namespace Modele {
 
    class A : public Base::Valeur
    {
    
      int toto ;
      
      ::ProjetUnivers::bool estVrai ;
    
      virtual void Fonction()
      {
      }
    };
  }
}

#endif
