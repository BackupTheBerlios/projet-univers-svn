// abstract_exception.cpp :
// implementation de abstract_exception.h

#include "../exception_abstraite.h"



// Classe de base
// **************

Exception::Exception
    (const Chaine& _message,
    const EntierNonSigne& numero)
    
  : message(_message),numero_erreur(numero)
{} 

Exception::~Exception()
{}

Exception::Exception(const Exception& x)
  : message(x.message),numero_erreur(x.numero_erreur)
{}


Chaine Exception::get_message() const {

  return Chaine("ERR") + Chaine(numero_erreur) + Chaine(" : ") + message;
}


