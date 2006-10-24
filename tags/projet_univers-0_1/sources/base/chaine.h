/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef _PU_BASE_CHAINE_H_
#define _PU_BASE_CHAINE_H_


#include <iostream>
#include <string>

#include <base/types.h>
#include <base/implantation/tampon_chaine.h>
#include <base/min_max.h>


namespace ProjetUnivers {

  namespace Base {
    
    
    ///	Classe des chaînes de caractères.
        
    /*! 
    
    @par Fonctionnement
	    Cette classe évite les copies de chaînes en maintenant le nombre de 
    	  référence à une chaîne particulière, c'est le rôle de 
      TamponChaine qui contient effectivement un char*.
    @todo
      re-implanter à l'aide de std::string      
    
    */
    class Chaine {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  

      Chaine();
     
      Chaine(const char* _s, int _len);

      Chaine(const char* _s);

      Chaine(char _c);

      Chaine(unsigned char _c);

      Chaine(const Chaine& _s);

      Chaine(short _val);

      Chaine(unsigned short _val);

      Chaine(int _val);

      Chaine(unsigned int _val);

      Chaine(long _val);

      Chaine(unsigned long _val);

      Chaine(float _val);

      Chaine(double _val);

      friend Chaine operator + (const Chaine& _s1, const Chaine& _s2);


      // @}  
            
              
      ~Chaine();
    	
      /*!
        @name Affectation
      */
      // @{
      
      Chaine& operator = (const Chaine& _s);

      Chaine& operator += (const Chaine& _s);
            
      // @}  
      /*!
        @name Acces
      */
      // @{
    
      operator const char* () const ;
      
      EntierPositif Longueur() const ;

      /*!
        @todo 
          franciser
      */    
      Chaine& append(const char* _s, int _s_len);
      Chaine& append(const Chaine& _s);
      Chaine& append(const char* _s);
      Chaine& append(char _c);
    
      // @}     
      // *************************
      /// @name Opérateurs de comparaison
      // *************************      
      // @{  
     
    
      
      friend inline Booleen operator == (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator != (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator == (const Chaine& _s1, const char* _s2);

      friend inline Booleen operator <= (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator < (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator >= (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator > (const Chaine& _s1, const Chaine& _s2);
    
      // @}

          
    protected:
        
      /*!
        @todo 
          franciser
      */    
      short cmp(const Chaine& _s) const;
        
      Chaine(const char* _s1, int _s1_len, const char* _s2, int _s2_len);
      Chaine(const char* _s, int _s_len, char _c);
      Chaine(char _c, const char* _s, int _s_len);
      
    
    private:
    
      /// Prends une référence à _p_rep.
      static Implantation::TamponChaine* Prendre(Implantation::TamponChaine* _p_rep);
    
      /// Abandonne la référence à _p_rep.
      static void Laisser(Implantation::TamponChaine* _p_rep);
    
    
      /// LA chaine vide
      static Implantation::TamponChaine chaineVide ;

      /// ?    
      static char number_buffer[];
    
      /// Copie partagée.
      Implantation::TamponChaine* representation;


      friend class Implantation::TamponChaine ;

    };


    inline Implantation::TamponChaine *Chaine::Prendre(Implantation::TamponChaine *_p_rep) {
      return _p_rep->Prendre();
    }
    
    inline void Chaine::Laisser(Implantation::TamponChaine *_p_rep) {
    
      // on teste si la référence à tuer est la chaîne vide :
      if (_p_rep != &chaineVide) {
    
        if (_p_rep->Laisser())
          delete _p_rep;
      } 
      // si c'est le cas on ne fait rien (elle sera détruite à la fin du 
      // programme, car 
      // c'est une variable "static"
    }                                                     
    
    
    inline Chaine::Chaine(const char *_s, int _len)
      : representation(new Implantation::TamponChaine(_s, _len))
    {}
    
    inline Chaine::Chaine()
      : representation(Prendre(&chaineVide))
    {}
    
    inline Chaine::Chaine(const char* _s)
      : representation((_s != 0) ? new Implantation::TamponChaine(_s) : Prendre(&chaineVide))
    {}
    
    inline Chaine::Chaine(char _c)
      : representation(new Implantation::TamponChaine(_c))
    {}
    
    inline Chaine::Chaine(unsigned char _c)
      : representation(new Implantation::TamponChaine((char)_c))
    {}
    
    inline Chaine::Chaine(const Chaine &_s)
      : representation(Prendre(_s.representation))
    {}
    
    inline Chaine::~Chaine() {
      Laisser(representation);
    }
    

 
    inline EntierPositif Chaine::Longueur() const {
      return representation->Longueur() ;
    }
    
    inline Chaine &Chaine::operator = (const Chaine &_s) {
     
      if (&_s == this)
    
        return *this ;
    
      Prendre(_s.representation);
      Laisser(representation);
      representation = _s.representation;
      return *this;
    }
    
    
    inline Chaine::operator const char *() const {
      return (const char *)*representation;
    }
    
    
    
    
    
    
    
    inline Chaine& Chaine::operator += (const Chaine &_s) {
      
      Implantation::TamponChaine* temp = new Implantation::TamponChaine(*representation) ;
      Laisser(representation) ;
      representation = temp ;
      representation->operator+=(*_s.representation) ;
      
      return *this ;
    
    }
    
    
    inline Booleen operator == (const Chaine &_s1, const Chaine &_s2) {
      return (_s1.cmp(_s2) == 0) ;
    }

   inline Booleen operator == (const Chaine& _s1, const char* _s2)
   {
    Chaine chaine(_s2) ;
    return _s1 == chaine ;
   }

   inline Booleen operator != (const Chaine& _s1, const char* _s2)
   {
    Chaine chaine(_s2) ;
    return _s1 != chaine ;
   }

    
    inline Booleen operator != (const Chaine &_s1, const Chaine &_s2) {
      return (_s1.cmp(_s2) != 0);
    }
    
    inline Booleen operator <= (const Chaine &_s1, const Chaine &_s2) {
      return _s1.cmp(_s2) <= 0;
    }
    
    inline Booleen operator < (const Chaine &_s1, const Chaine &_s2) {
      return _s1.cmp(_s2) < 0;
    }
    
    inline Booleen operator >= (const Chaine &_s1, const Chaine &_s2) {
      return _s1.cmp(_s2) >= 0;
    }
    
    inline Booleen operator > (const Chaine &_s1, const Chaine &_s2) {
      return _s1.cmp(_s2) > 0;
    }
    
    
    inline Chaine operator + (const Chaine &_s1, const Chaine &_s2) {
      
      Chaine resultat = _s1 ;
      resultat += _s2 ;
      return resultat ;
    }

    
    inline Chaine::Chaine(short _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%hd", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(unsigned short _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%hu", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(int _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%d", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(unsigned int _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%u", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(long _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%ld", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(unsigned long _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%lu", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(float _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%g", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(double _val)
      : representation(new Implantation::TamponChaine((sprintf(number_buffer, "%g", _val), number_buffer)))
    {}    
    
    

  }
}

#endif
