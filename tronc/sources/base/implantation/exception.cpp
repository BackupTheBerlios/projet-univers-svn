// exception.cpp

#include "exception.h"


namespace SpaceTheater {

  namespace Base {


    Exception::Exception(const Chaine& _message)
    : AbstractException(_message,70)
    {}
  }
}
    
