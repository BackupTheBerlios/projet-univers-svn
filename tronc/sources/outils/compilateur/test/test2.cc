
#include <base/association.h>
#include <base/composition.h>
#include <base/ensemble_association.h>

namespace ProjetUnivers
{

  namespace Base 
  {
  
    class Valeur
    {} ;
    
  }
}

namespace ProjetUnivers {
  
  namespace Modele {
 
    class A : public Base::Valeur
    {
    
      int toto ;
      
      ProjetUnivers::Base::Booleen estVrai ;
    
      void Fonction()
      {
      }
    };
  
    
    class B : public A
    {
    public:
      ProjetUnivers::Base::Association<A> a ;
      // Base::FonctionObjetValeur<A,B> fonction ;
      
      A attribut_classe ;
      
      void Test();
      
    };
    
    
  }
  
  namespace Vue {
  
    template <class T> class Temp
    {};
    
  
    class A 
    {
    public:
    
      Temp<Modele::B> temp ;
      ProjetUnivers::Base::Composition<Modele::A> a ;
      Modele::A objet ;

      int i ;

      int fonction(void) const ;
    };
    
    
  }
}

int main()
{
  
  
  return 0 ;
}

