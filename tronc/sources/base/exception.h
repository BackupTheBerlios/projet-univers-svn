// exception.h


#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "abstract_exception.h"


namespace SpaceTheater {

  namespace Base {


    /*
    CLASS
    	Exception
    
    	Classe des exceptions dues à une erreur d'implantation dans le module Base.
    */
    class Exception : public AbstractException {
    
    public:
    
    	Exception(const Chaine& _message) ;
    
    };

  }
}

#endif
