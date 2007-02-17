
#ifndef PU_OUTILS_COMPILATEUR_TEST_CLASSE_C_H
#define PU_OUTILS_COMPILATEUR_TEST_CLASSE_C_H

#include <base/types.h>
#include <base/association.h>

#include "base.h"

namespace ProjetUnivers {
  
  namespace Modele {
 
    /// Déclaration en avant...
    class A ;
 
    class C : public Base::Valeur
    {
    public:
      
      Base::Association<A> attributA ;
    
    };
  }
}

#endif
