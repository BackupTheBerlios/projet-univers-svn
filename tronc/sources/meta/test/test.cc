

template <class T> class Composition
{};

template <class T> class Association
{};

template <class T, class V> class FonctionObjetValeur
{};

namespace PU {
  template <class T> class Zob
  {};
}
  

typedef unsigned short Booleen ;

class Titi ;

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

metaclass Serialisable Titi ;    // metaclass declaration



class Titi : public test {
public:

  Titi() ;

  bool ADesPoils() ;

private:

  Composition< test > toto ;
  FonctionObjetValeur< test, Booleen> estBeau ;
  
public:  
  Booleen zob ;
  int age ;
};
