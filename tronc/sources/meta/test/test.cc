

template <class T> class Composition
{};

template <class T> class Association
{};

template <class T, V> class FonctionObjetValeur
{};

namespace PU {
  template <class T> class Zob
  {};
}
  

typedef unsigned short Booleen ;


class Toto {
public:

  Toto() ;

  virtual void Manger() ;

protected:
  
  Association< Titi > titi ;
  PU::Zob< Toto> unZob ;
};

metaclass Serialisable Titi ;    // metaclass declaration



class Titi : public Toto {
public:

  Titi() ;

  bool ADesPoils() ;

private:

  Composition< Toto > toto ;
  FonctionObjetValeur< Toto, Booleen> estBeau ;
  
public:  
  Booleen zob ;
  int age ;
};
