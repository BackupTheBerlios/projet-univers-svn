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

#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

#include <base/types.h>


namespace ProjetUnivers {

  namespace Base {

    namespace Implantation {
      
  
      /// Classe repr�sentant une copie partag�e d'une cha�ne.
      
      
      /*!
        FONCTIONNEMENT          
        Lorsque le nombre de r�f�rences � cette copie tombe � 0, elle est 
        d�truite.
      */
      class TamponChaine {
      public:
        
        // ********************
        /// @name Constructeurs
        // ********************
        // @{


        /// Construit une chaine "" de taille maximum _size.
        TamponChaine(const EntierPositif& _size) ;

        /// Construit une cha�ne "".
        TamponChaine();
        
        /// Construit une chaine.
        TamponChaine(const char* _s, const EntierPositif& _len);
                
        /// Construit une chaine.
        TamponChaine(const char* _s);

        /// Construit une cha�ne � partir d'un caract�re.
        TamponChaine(char _c);
        
        
        TamponChaine(const char* _s1, const EntierPositif& _s1_len, 
                      const char*_s2, const EntierPositif& _s2_len);
                      
        TamponChaine(const char* _s, const EntierPositif& _s_len, char _c);
        TamponChaine(char _c, const char* _s, const EntierPositif& _s_len);
        
        ~TamponChaine();
        
        /// Acc�s � la longueur de la cha�ne.
        EntierPositif len() const;

        /// Op�rateur de conversion en char*.
        operator char*() const ;


        // @}
        // **************************************
        /// @name gestion du nombre de r�f�rences
        // **************************************
        // @{


        /// R�cup�re un pointeur sur la chaine, augmente le 
        /// nombre de r�f�rences
        TamponChaine* take() ;
        
        /// Laisse tomber une r�f�rence � la chaine, 
        /// diminue le nombre de r�f�rences
        Booleen drop() ;


        // @}        

        
      private:
        
        TamponChaine(const TamponChaine& _s) ;
        TamponChaine& operator=(const TamponChaine& _s) ;

      private:
        
        /// Nombre de r�f�rences � la cha�ne.
        EntierPositif nb_ref ;
        
        /// Taille de la cha�ne.
        EntierPositif size ;
        
        /// Cha�ne proprment dite.
        char* s ;

      };
      
      inline TamponChaine::TamponChaine(const EntierPositif& _size)
        : nb_ref(1), size(_size), s(new char[_size + 1])
      {}
      
      inline TamponChaine::TamponChaine(const char *_s, const EntierPositif& _len)
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
        const EntierPositif& _s1_len, 
          const char *_s2, const EntierPositif& _s2_len)
        : nb_ref(1), size(_s1_len + _s2_len), s(new char[size + 1])
      {
        memcpy(s, _s1, _s1_len);
        memcpy(s + _s1_len, _s2, _s2_len);
        s[size] = '\0';
      }
      
      inline TamponChaine::TamponChaine(const char *_s, 
        const EntierPositif& _s_len, char _c)
        : nb_ref(1), size(_s_len + 1), s(new char[size + 1])
      {
        memcpy(s, _s, _s_len);
        s[_s_len] = _c;
        s[size] = '\0';
      }
      
      inline TamponChaine::TamponChaine(char _c, const char *_s, 
        const EntierPositif& _s_len)
        : nb_ref(1), size(_s_len + 1), s(new char[size + 1])
      {
        s[0] = _c;
        memcpy(s + 1, _s, _s_len);
        s[size] = '\0';
      }
      
      inline TamponChaine::~TamponChaine() {
        delete [] s;
      }
      
      inline EntierPositif TamponChaine::len() const {
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
}

#endif

