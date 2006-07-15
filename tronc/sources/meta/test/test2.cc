
//#include <base/association.h>
//#include <base/composition.h>
//#include <base/ensemble_association.h>

namespace ProjetUnivers
{

  namespace Base 
  {
  
    typedef float Reel ;
  
    class Valeur
    {} ;
  
    template <class T> class Composition
    {};

    template <class T> class Association
    {};

    template <class T, class V> class FonctionObjetValeur
    {};
  }
}

namespace ProjetUnivers {
  
  namespace Modele {
 
    class A : public Base::Valeur
    {
    public:
      A() ;
      ~A() ;
      
      static void truc(int a, A b) ;
      
      int toto ;
    
      void Fonction()
      {
      }
    };
  
    
    class B : public A
    {
    public:
      ProjetUnivers::Base::Association<A> a ;
      Base::FonctionObjetValeur<A,B> fonction ;
      
//      void Test()
//      {
//        if (this->a == 0)
//          return ;
//        
//        if (a == 0)
//          return ;
//        
//      }
      
    };
    
    
  }
  
  namespace Vue {
  
    template <class T> class Temp
    {};
    
  
    class A //: protected Modele::A
    {
    public:
    
      Temp<A> temp ;
      ProjetUnivers::Base::Composition<Modele::A> a ;
      Modele::A objet ;

      void fonction(void) const ;
      static const int methode(int a, float b) ;
      
      static volatile const int i ;
     
    };
    
    
  }
}

int main()
{
  
  
  return 0 ;
}

