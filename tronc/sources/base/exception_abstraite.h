#ifndef ABSTRACT_EXCEPTION_H
#define ABSTRACT_EXCEPTION_H



#include "chaine.h"


namespace SpaceTheater {
  
  /*
  CLASS
    AbstractException
  
    Classe de base des exceptions utilisées dans le Space Theater.
  
  
  NOTE
    Il me semble que c'est bisarre d'avoir une classe de valeur abstraite. 
    Eventuellement, séparer la hiérarchie à part et mettre une méthode 
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
    // Message d'erreur correspondant à l'exception.
    Chaine get_message() const ;
  
  
  protected:
  
    ////////////////
    // Message associé à l'exception.
    Chaine		message ;
  
    //////////////////
    // numéro de l'erreur.
    Entier		numero_erreur ;
  
    ////////////////
    // Classe virtuelle, donc constructeur protected.
    AbstractException(const Chaine& _message,const EntierNonSigne& numero) ;
  
  };
}

#endif
