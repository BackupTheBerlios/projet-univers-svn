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

#include "types.h"
#include "implantation/tampon_chaine.h"
#include "min_max.h"


namespace ProjetUnivers {

  namespace Base {
    
    /*
    CLASS
    	Chaine
    
    	Classe des chaînes de caractères.
    
    FONCTIONNEMENT
    
    	Cette classe évite les copies de chaînes en maintenant le nombre de 
    	référence à une chaîne particulière, c'est le rôle de StringBuffer qui contient 
    	effectivement un char*.
     */
    class Chaine {
    public:
    
      ///////////////////////
      // GROUP: Constructeurs
      ///////////////////////
    
      Chaine(const char* _s, int _len);
      Chaine();
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
        
      ~Chaine();
        
      //operator Int () const ;
    
    	
      Chaine& operator = (const Chaine& _s);
      Chaine& operator = (const char* _s);
      Chaine& operator = (char _c);
        
    
      operator const char* () const;
      operator char* ();
      int length() const;
      int len() const;
      char operator [] (int _pos) const;
      char& operator [] (int _pos);
    
      /////////////////
      // Renvoie la même chaîne en majuscule.
      Chaine upper() const ;
    
      Chaine operator() (int _pos, int _len) const;
      Chaine& append(const char* _s, int _s_len);
      Chaine& operator += (const Chaine& _s);
      Chaine& append(const Chaine& _s);
      Chaine& operator += (const char* _s);
      Chaine& append(const char* _s);
      Chaine& operator += (char _c);
      Chaine& append(char _c);
    
      
    
      // ********************************
      // GROUP: Opérateurs de comparaison
      // ********************************
    
    
      
      friend inline Booleen operator == (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator != (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator <= (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator < (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator >= (const Chaine& _s1, const Chaine& _s2);
      friend inline Booleen operator > (const Chaine& _s1, const Chaine& _s2);
    
      
    
    
      // GROUP: Opérateurs de construction
    
      friend inline Chaine operator + (const Chaine& _s1, const Chaine& _s2);
      friend inline Chaine operator + (const Chaine& _s1, const char* _s2);
      friend inline Chaine operator + (const char* _s1, const Chaine& _s2);
      friend inline Chaine operator + (const Chaine& _s, char _c);
      friend inline Chaine operator + (char _c, const Chaine& _s);
    
      // ****************
      // GROUP: Recherche
      // ****************
      
      Booleen contains(const Chaine& _s) const;
      int find(const Chaine& _s) const;
    
    protected:
        
      short cmp(const Chaine& _s) const;
        
      Chaine(const char* _s1, int _s1_len, const char* _s2, int _s2_len);
      Chaine(const char* _s, int _s_len, char _c);
      Chaine(char _c, const char* _s, int _s_len);
      
    
    private:
    
      ////////////////
      // Prends une référence à _p_rep.
      static Implantation::TamponChaine* take_rep(Implantation::TamponChaine* _p_rep);
    
      //////////////////
      // Abandonne la référence à _p_rep.
      static void drop_rep(Implantation::TamponChaine* _p_rep);
    
      static Implantation::TamponChaine empty_str_rep;
    
      static char number_buffer[];
    
      //////////////////
      // Copie partagée.
      Implantation::TamponChaine* p_rep;
    
    
    
    };
    
    inline Implantation::TamponChaine *Chaine::take_rep(Implantation::TamponChaine *_p_rep) {
      return _p_rep->take();
    }
    
    inline void Chaine::drop_rep(Implantation::TamponChaine *_p_rep) {
    
      // on teste si la référence à tuer est la chaîne vide :
      if (_p_rep != &empty_str_rep) {
    
        if (_p_rep->drop())
          delete _p_rep;
      } 
      // si c'est le cas on ne fait rien (elle sera détriute à la fin du programme, car 
      // c'est une variable "static"
    }                                                     
    
    inline Chaine::Chaine(const char *_s, int _len)
      : p_rep(new Implantation::TamponChaine(_s, _len))
    {}
    
    inline Chaine::Chaine()
      : p_rep(take_rep(&empty_str_rep))
    {}
    
    inline Chaine::Chaine(const char* _s)
      : p_rep((_s != 0) ? new Implantation::TamponChaine(_s) : take_rep(&empty_str_rep))
    {}
    
    inline Chaine::Chaine(char _c)
      : p_rep(new Implantation::TamponChaine(_c))
    {}
    
    inline Chaine::Chaine(unsigned char _c)
      : p_rep(new Implantation::TamponChaine((char)_c))
    {}
    
    inline Chaine::Chaine(const Chaine &_s)
      : p_rep(take_rep(_s.p_rep))
    {}
    
    inline Chaine::~Chaine() {
      drop_rep(p_rep);
    }
    
    inline int Chaine::length() const {
      return p_rep->len();
    }
    
    inline int Chaine::len() const {
      return length();
    }
    
    inline Chaine &Chaine::operator = (const Chaine &_s) {
    	
      if (&_s == this)
    
        return *this ;
    
      take_rep(_s.p_rep);
      drop_rep(p_rep);
      p_rep = _s.p_rep;
      return *this;
    }
    
    inline Chaine &Chaine::operator = (const char *_s) {
      if (*_s) {
        Implantation::TamponChaine *p_new_rep = new Implantation::TamponChaine(_s);
        drop_rep(p_rep);
        p_rep = p_new_rep;
      }
      else {
        drop_rep(p_rep);
        p_rep = take_rep(&empty_str_rep);
      }
      return *this;
    }
    
    inline Chaine &Chaine::operator = (char _c) {
      drop_rep(p_rep);
      p_rep = new Implantation::TamponChaine(_c);
      return *this;
    }
    
    inline Chaine::operator const char *() const {
      return (const char *)*p_rep;
    }
    
    inline Chaine::operator char *() {
      return (char *)*p_rep;
    }
    
    inline char Chaine::operator [] (int _pos) const {
      return _pos < length() ? (operator const char *())[_pos] : '\0';    
    }
    
    inline char &Chaine::operator [] (int _pos) {
      if (_pos >= length()) {
        Implantation::TamponChaine *p_new_rep = new Implantation::TamponChaine(*p_rep, _pos + 1);
        drop_rep(p_rep);
        p_rep = p_new_rep;
      }
      return (operator char *())[_pos];    
    }
    
    inline Chaine Chaine::operator() (int _pos, int _len) const {
      return _pos < len() ? Chaine(operator const char *() + _pos, Minimum(_len, len() - _pos)) : Chaine();
    }
    
    
    
    
    
    
    inline Chaine &Chaine::operator += (const Chaine &_s) {
      return append((const char *)_s, _s.len());
    }
    
    inline Chaine &Chaine::append(const Chaine &_s) {
      return operator += (_s);
    }
    
    inline Chaine &Chaine::operator += (const char *_s) {
      return append(_s, strlen(_s));
    }
    
    inline Chaine &Chaine::append(const char *_s) {
      return operator += (_s);
    }
    
    inline Chaine &Chaine::append(char _c) {
      return operator += (_c);
    }
    
    inline Booleen operator == (const Chaine &_s1, const Chaine &_s2) {
      return (_s1.len() == _s2.len()) && (_s1.cmp(_s2) == 0);
    }
    
    inline Booleen operator != (const Chaine &_s1, const Chaine &_s2) {
      return (_s1.len() != _s2.len()) || (_s1.cmp(_s2) != 0);
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
    
    inline Chaine::Chaine(const char *_s1, int _s1_len, const char *_s2, int _s2_len)
      : p_rep(new Implantation::TamponChaine(_s1, _s1_len, _s2, _s2_len))
    {}
    
    inline Chaine::Chaine(const char *_s, int _s_len, char _c)
      : p_rep(new Implantation::TamponChaine(_s, _s_len, _c))
    {}
    
    inline Chaine::Chaine(char _c, const char *_s, int _s_len)
      : p_rep(new Implantation::TamponChaine(_c, _s, _s_len))
    {}
    
    inline Chaine operator + (const Chaine &_s1, const Chaine &_s2) {
      return Chaine(_s1, _s1.len(), _s2, _s2.len());
    }
    
    inline Chaine operator + (const Chaine &_s1, const char *_s2) {
      return Chaine(_s1, _s1.len() , _s2, strlen(_s2));
    }
    
    inline Chaine operator + (const char *_s1, const Chaine &_s2) {
      return Chaine(_s1, strlen(_s1), _s2, _s2.len());
    }
    
    inline Chaine operator + (const Chaine &_s, char _c) {
      return Chaine(_s, _s.len(), _c);
    }
    
    inline Chaine operator + (char _c, const Chaine &_s) {
      return Chaine(_c, _s, _s.len());
    }
    
    inline Booleen Chaine::contains(const Chaine &_s) const {
      return find(_s) != -1;
    }
    
    #include <stdio.h>
    
    inline Chaine::Chaine(short _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%hd", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(unsigned short _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%hu", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(int _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%d", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(unsigned int _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%u", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(long _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%ld", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(unsigned long _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%lu", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(float _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%g", _val), number_buffer)))
    {}
    
    inline Chaine::Chaine(double _val)
      : p_rep(new Implantation::TamponChaine((sprintf(number_buffer, "%g", _val), number_buffer)))
    {}
  }
}

#endif
