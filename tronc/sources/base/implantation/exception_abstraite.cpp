// abstract_exception.cpp :
// implementation de abstract_exception.h

#include "abstract_exception.h"



// Classe de base
// **************

AbstractException::AbstractException
    (const Chaine& _message,
    const EntierNonSigne& numero)
    
  : message(_message),numero_erreur(numero)
{} 

AbstractException::~AbstractException()
{}

AbstractException::AbstractException(const AbstractException& x)
  : message(x.message),numero_erreur(x.numero_erreur)
{}


Chaine AbstractException::get_message() const {

  return Chaine("ERR") + Chaine(numero_erreur) + Chaine(" : ") + message;
}


