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
 
#ifndef _BASE_FONCTION_VALEUR_VALEUR_H_
#define _BASE_FONCTION_VALEUR_VALEUR_H_

#include <map>


#include <base/association.h>


namespace ProjetUnivers {
  namespace Base {
    
    ///  Une fonction qui associe un élément de VALEUR à un élément de CLE.
    /*!  
      Cle et Valeur doivent être des classes de valeurs.
    
      @todo
        A réaliser et tester
    */
    template <class Cle, typename Valeur > class FonctionValeurValeur {
    public:
    
      /// @name Construction
      // @{      
    
    
      /// Constructeur.
      FonctionValeurValeur() ;
    
      /// Constructeur de copie.
      FonctionValeurValeur(const FonctionValeurValeur& _v);
    
      // @}
            
      /// @name Modification
      // @{      
    
      /// Ajoute @c _valeur identifié par @c _cle.
      void Ajouter(const Cle& _cle, const Valeur& _valeur) ;
    
      /// Modifie l'élément associé à la clé. 
      /*!
        Si l'élément n'existe pas alors cela a l'effet de Ajouter.
      */
      void Changer(const Cle&, const Valeur&) ;
    
      // @}
          

      // *************************
      /// @name Accès
      // *************************      
      // @{      
    
      /// Accès à un élément en fonction de l'identifiant.
      Valeur Acces(const Cle&) const ;

      /// Accès à un élément en fonction de l'identifiant.
      Valeur& operator[](const Cle&) const ;
    
      /// Opérateur de comparaison
      Booleen operator==(const FonctionValeurValeur<Cle,Valeur>& _right) const ;
    
      // @}
    
    private:
    
    
      mutable std::map<Cle,Valeur> fonction ;
      
    
    };

  }
}

#include <base/implantation/fonction_valeur_valeur.cxx>


#endif
