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

#ifndef _PU_BASE_TAMPON_CHAINE_H_
#define _PU_BASE_TAMPON_CHAINE_H_

#include <base/types.h>
#include <string>

namespace ProjetUnivers {

  namespace Base {

    class Chaine ;

    namespace Implantation {
      
  
      /// Classe repr�sentant une copie partag�e d'une cha�ne.
      
      
      /*!
        Lorsque le nombre de r�f�rences � cette copie tombe � 0, elle est 
        d�truite.
      */
      class TamponChaine {
      public:
        
        /// @name Constructeurs
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
        
        
//        TamponChaine(const char* _s1, const EntierPositif& _s1_len, 
//                      const char*_s2, const EntierPositif& _s2_len);
                      
//        TamponChaine(const char* _s, const EntierPositif& _s_len, char _c);
//        TamponChaine(char _c, const char* _s, const EntierPositif& _s_len);

        TamponChaine& operator +=(const TamponChaine&) ;


        // @}
        /// @name Acc�s
        // @{

        
        /// Acc�s � la longueur de la cha�ne.
        EntierPositif Longueur() const;

        /// Op�rateur de conversion en char*.
        operator const char*() const ;


        // @}
        /// @name gestion du nombre de r�f�rences
        // @{


        /// R�cup�re un pointeur sur la chaine, augmente le 
        /// nombre de r�f�rences
        TamponChaine* Prendre() ;
        
        /// Laisse tomber une r�f�rence � la chaine, 
        /// diminue le nombre de r�f�rences
        Booleen Laisser() ;


        // @}        
        /// @name Comparaison
        // @{
        
        
        /// Comparaison.
        Booleen operator ==(const TamponChaine& ) const ;

        // @}
        


        
      private:

        /// Constructeur de copie de classe d'objet        
        TamponChaine(const TamponChaine& _s) ;
        
        /// idem
        TamponChaine& operator=(const TamponChaine& _s) ;

        
        /// Nombre de r�f�rences � la cha�ne.
        EntierPositif nombreReferences ;
        
        /// Cha�ne proprement dite.
        std::string chaine ;
        
        
        friend class Chaine ;

      };



      inline Booleen TamponChaine::operator ==(const TamponChaine& droite) const
      {
        return chaine == droite.chaine ;
      }


      inline TamponChaine::TamponChaine(const EntierPositif& _size)
        : nombreReferences(1), chaine()
      {}
      
      inline TamponChaine::TamponChaine(const char *_s, const EntierPositif& _len)
        : nombreReferences(1), chaine(_s)
      {}
      
      inline TamponChaine::TamponChaine(const char *_s)
        : nombreReferences(1), chaine(_s)
      {}
      
      inline TamponChaine::TamponChaine(char _c)
        : nombreReferences(1), chaine()
      {
        chaine.append(1,_c) ;
      }
      
      inline TamponChaine::TamponChaine()
        : nombreReferences(1), chaine()
      {}


      inline TamponChaine::TamponChaine(const TamponChaine& _s)
        : nombreReferences(1), chaine(_s.chaine)
      {}
      

      inline TamponChaine& TamponChaine::operator +=(const TamponChaine& _s)
      {
        this->chaine += _s.chaine ;
      }

      
//      
//      inline TamponChaine::TamponChaine(
//        const char *_s1, 
//        const EntierPositif& _s1_len, 
//        const char *_s2, const EntierPositif& _s2_len)
//      : nombreReferences(1), chaine( std::string(_s1) + std::string(_s2))
//      {}
//      
//      inline TamponChaine::TamponChaine(
//        const char *_s, 
//        const EntierPositif& _s_len, 
//        char _c)
//      : nombreReferences(1), chaine( std::string(_s) + std::string(_c))
//      {}
//      
//      inline TamponChaine::TamponChaine(
//        char _c, const char *_s, 
//        const EntierPositif& _s_len)
//        : nombreReferences(1), chaine( std::string(c) + std::string(_s))
//      {}
      
      
      inline EntierPositif TamponChaine::Longueur() const {
        return chaine.length() ;
      }
      
      inline TamponChaine *TamponChaine::Prendre() {
        ++nombreReferences;
        return this;
      }
      
      inline Booleen TamponChaine::Laisser() {
        return --nombreReferences == 0;
      }
      
      inline TamponChaine::operator const char *() const {
        return chaine.c_str() ;
      }

        
      
    }
  }
}

#endif

