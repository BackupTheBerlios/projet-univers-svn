/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

#include "types.h"


namespace ProjetUnivers {

  namespace Base {

    /*
    CLASS
      TamponChaine
      
      Classe représentant une copie partagée d'une chaîne.
      
      
    FONCTIONNEMENT
        
      Lorsque le nombre de références à cette copie tombe à 0, elle est 
      détruite.
    */
    class TamponChaine {
      
      ////////////////////
      // Nombre de références à la chaîne.
      EntierNonSigne nb_ref ;
      
      ////////////////////
      // Taille de la chaîne.
      EntierNonSigne size ;
      
      ///////////////////
      // Chaîne proprment dite.
      
      char* s ;
      
    public:
      
      // GROUP: Constructeurs
      
      TamponChaine(const EntierNonSigne& _size);
      TamponChaine(const char* _s, const EntierNonSigne& _len);
      TamponChaine(const char* _s);
      TamponChaine(char _c);
      TamponChaine();
      TamponChaine(const char* _s1, const EntierNonSigne& _s1_len, 
                    const char*_s2, const EntierNonSigne& _s2_len);
                    
      TamponChaine(const char* _s, const EntierNonSigne& _s_len, char _c);
      TamponChaine(char _c, const char* _s, const EntierNonSigne& _s_len);
      
      ~TamponChaine();
      
      ///////////////
      // Accès à la longueur de la chaîne.
      EntierNonSigne len() const;
    
      ////////////////////
      // tient une copie de la chaine, augmente le 
      // nombre de références
      TamponChaine* take() ;
      
      /////////////////
      // Laisse tomber une référence à la copie courante, 
      // diminue le nombre de références
      Booleen drop() ;
      
      //////////////////
      // Opérateur de conversion en char*.
      operator char*() const ;
      
    private:
      
      TamponChaine(const TamponChaine& _s) ;
      TamponChaine& operator=(const TamponChaine& _s) ;
    };
    
    inline TamponChaine::TamponChaine(const EntierNonSigne& _size)
      : nb_ref(1), size(_size), s(new char[_size + 1])
    {}
    
    inline TamponChaine::TamponChaine(const char *_s, const EntierNonSigne& _len)
      : nb_ref(1), size(_len), s(new char[_len + 1])
    {
      memcpy(s, _s, _len);
      s[_len] = '\0';
    }
    
    inline TamponChaine::TamponChaine(const char *_s)
      : nb_ref(1), size(strlen(_s)), s(new char[size + 1])
    {
      strcpy(s, _s);
    }
    
    inline TamponChaine::TamponChaine(char _c)
      : nb_ref(1), size(1), s(new char[2])
    {
      s[0] = _c;
      s[1] = '\0';
    }
    
    inline TamponChaine::TamponChaine()
      : nb_ref(1), size(0), s(new char[1])
    {
      s[0] = '\0';
    }
    
    inline TamponChaine::TamponChaine(const char *_s1, 
      const EntierNonSigne& _s1_len, 
        const char *_s2, const EntierNonSigne& _s2_len)
      : nb_ref(1), size(_s1_len + _s2_len), s(new char[size + 1])
    {
      memcpy(s, _s1, _s1_len);
      memcpy(s + _s1_len, _s2, _s2_len);
      s[size] = '\0';
    }
    
    inline TamponChaine::TamponChaine(const char *_s, 
      const EntierNonSigne& _s_len, char _c)
      : nb_ref(1), size(_s_len + 1), s(new char[size + 1])
    {
      memcpy(s, _s, _s_len);
      s[_s_len] = _c;
      s[size] = '\0';
    }
    
    inline TamponChaine::TamponChaine(char _c, const char *_s, 
      const EntierNonSigne& _s_len)
      : nb_ref(1), size(_s_len + 1), s(new char[size + 1])
    {
      s[0] = _c;
      memcpy(s + 1, _s, _s_len);
      s[size] = '\0';
    }
    
    inline TamponChaine::~TamponChaine() {
      delete [] s;
    }
    
    inline EntierNonSigne TamponChaine::len() const {
      return size;
    }
    
    inline TamponChaine *TamponChaine::take() {
      ++nb_ref;
      return this;
    }
    
    inline Booleen TamponChaine::drop() {
      return --nb_ref == 0;
    }
    
    inline TamponChaine::operator char *() const {
      return s;
    }

  }
}

#endif

