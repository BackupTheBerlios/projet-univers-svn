#ifndef ABSTRACT_EXCEPTION_H
#define ABSTRACT_EXCEPTION_H



#include "chaine.h"


namespace SpaceTheater {
  
  /*
  CLASS
    AbstractException
  
    Classe de base des exceptions utilis�es dans le Space Theater.
  
  
  NOTE
    Il me semble que c'est bisarre d'avoir une classe de valeur abstraite. 
    Eventuellement, s�parer la hi�rarchie � part et mettre une m�thode 
    de copie abstraite.
  */
  class AbstractException {
  public:
  
    ////////////////
    // Constructeur de copie, le constructeur de copie est obligatoire
    // pour les exceptions.
    AbstractException(const AbstractException& x) ;
  
    ////////////////
    // Classe abstraite donc destructeur virtuel.
    virtual ~AbstractException() ;
  
    ////////////////
    // Message d'erreur correspondant � l'exception.
    Chaine get_message() const ;
  
  
  protected:
  
    ////////////////
    // Message associ� � l'exception.
    Chaine		message ;
  
    //////////////////
    // num�ro de l'erreur.
    Entier		numero_erreur ;
  
    ////////////////
    // Classe virtuelle, donc constructeur protected.
    AbstractException(const Chaine& _message,const EntierNonSigne& numero) ;
  
  };
}

#endif
