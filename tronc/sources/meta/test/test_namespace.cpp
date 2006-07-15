
#include <iostream>

using namespace std ;

namespace ProjetUnivers 
{

  namespace Base 
  {
  
    class Valeur
    {
    public:
      void Print() const 
      {
        cout << "ProjetUnivers::Base::Valeur" << endl ;
      }  
    };
    
     
    
  } 
  
  namespace Modele
  {

    class Valeur
    {
    public:
      void Print() const 
      {
        cout << "ProjetUnivers::Modele::Valeur" << endl ;
      }
    };
  
    using namespace Base ;
    
    class Test : public Valeur
    {};
      
  }
  
  namespace Vue
  {
  
    using namespace Base ;
    
    class Test : public Valeur
    {};
      
  }
   
  
  
  
  
  
}




int main()
{
  ProjetUnivers::Modele::Test temp ;
  temp.Print() ;

  ProjetUnivers::Vue::Test temp2 ;
  temp2.Print() ;

  
  return 0 ;
}
