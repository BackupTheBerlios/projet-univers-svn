

template <class T> class Composition
{};

template <class T> class Association
{};

template <class T, class V> class FonctionObjetValeur
{};

namespace PU {
  template <class T> class Zob
  {};
  
  typedef int TypeEntier ;
  
}
  
typedef enum {a, b, c} enumere ;
typedef unsigned short Booleen ;

class Titi ;

//metaclass Serialisable Test ;

class test {
public:

  ////////////////////////
  // Constructeur.
  test() ;

  virtual void Manger() ;

protected:
  
  Association< Titi > titi ;
  PU::Zob< test> unZob ;
};

//metaclass Serialisable Titi ;    // metaclass declaration



class Titi : public test {
public:

  Titi() ;

  bool ADesPoils() ;

private:

  Composition< test > toto ;
  FonctionObjetValeur< test, Booleen> estBeau ;
  enumere attribut_enum ;
  PU::TypeEntier entier ;
  
public:  
  Booleen zob ;
  int age ;
  
  /// commentaire 1
  mutable int truc ; /// commentaire 2
  /// commentaire 3
};

int main()
{
  return 0 ;
}

