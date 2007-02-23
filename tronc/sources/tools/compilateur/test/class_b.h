

#include <base/association.h>
#include <base/composition.h>
#include <base/ensemble_association.h>

#include "class_a.h"
#include "base.h"

#ifndef PU_OUTILS_COMPILATEUR_TEST_CLASSE_B_H
#define PU_OUTILS_COMPILATEUR_TEST_CLASSE_B_H


namespace ProjetUnivers {
  
  namespace Modele {

    class B : public A
    {
    public:


      // marche

      ProjetUnivers::Base::Association<A> associationA ;
      Base::FonctionObjetValeur<A,B> fonctionAB ;
      A valeurA ;
      
      virtual void Test();
      B() ;
      B(const B& _toto) ;
      virtual ~B() ;
      bool operator==(const B& _toto) const ;
      virtual void VirtuellePure() = 0 ;
            
      // marche pas
            
    };
  }
}

#endif

