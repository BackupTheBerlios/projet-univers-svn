
#include <base/association.h>
#include <base/composition.h>
#include <base/ensemble_association.h>

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

namespace ProjetUnivers {
  
  namespace Modele {
 
    class A : public Base::Valeur
    {
    
      int toto ;
      
      ::ProjetUnivers::Base::Booleen estVrai ;
    
      virtual void Fonction()
      {
      }
    };
  
    
    class B : public A
    {
    public:

      bool operator==(const B& _toto) const ;
      virtual ~B() ;


      // marche

      ProjetUnivers::Base::Association<A> associationA ;
      Base::FonctionObjetValeur<A,B> fonctionAB ;
      A valeurA ;
      
      virtual void Test();
      B() ;
      
      // marche pas
      B(const B& _toto) ;
      
    };
    
    
    class ObjetA : public Base::Objet
    {};
    
  }
  
  namespace Vue {
  
    template <class T> class Temp
    {};
    
  
    class A 
    {
    public:
    
      ProjetUnivers::Base::Composition<Modele::A> CompositionA ;
      Modele::A objet ;

      int i ;

      int fonction(void) const ;
    };
    
    class C : public Base::Objet
    {
    public:
      
      Base::Association<A> associationA ;  
    };
    
    
    class D : public C
    {};
    
    class ValeurA : public Base::Valeur
    {
    public:
      Base::Association< Modele::ObjetA> objetA ;  
    };

    class ValeurB : public Base::Valeur
    {
    public:
      Base::Association< Modele::ObjetA> objetA ;  
      ValeurA valeurA ;
      
      Base::FonctionObjetValeur< Modele::ObjetA, ValeurA> fonctionObjetValeur ;
      
    };

    
  }
}

int main()
{
  
  
  return 0 ;
}

