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
 
#ifndef _BASE_FONCTION_OBJET_VALEUR_H_
#define _BASE_FONCTION_OBJET_VALEUR_H_

#include <map>


#include <base/association.h>


namespace ProjetUnivers {

  namespace Base {

    
    
    
    ///  Une fonction qui associe un �l�ment de VALEUR � un �l�ment de OBJET. 
    /*!  
      OBJET doit �tre une classe d'objets et VALEUR une classe de valeurs.
    
      @todo
        A r�aliser et tester
    */
    template <class OBJET, typename VALEUR > class FonctionObjetValeur {
    public:
    
      /// @name Construction
      // @{      
    
    
      /// Constructeur.
      FonctionObjetValeur() ;
    
      /// Constructeur de copie.
      FonctionObjetValeur(const FonctionObjetValeur& _v);
    
      // @}
            
      /// @name Modification
      // @{      
    
      /// Ajoute un �l�ment identifi� par le nom du param�tre.
      void Ajouter(const Association<OBJET>&, const VALEUR&) ;
    
      /// Modifie l'�l�ment associ� au param�tre de type OBJET. 
      /*!
        Si l'�l�ment n'existe pas alors cela a l'effet de Ajouter.
      */
      void Changer(const Association<OBJET>&, const VALEUR&) ;
    
      // @}
          

      // *************************
      /// @name Acc�s
      // *************************      
      // @{      
    
      /// Acc�s � un �l�ment en fonction de l'identifiant.
      VALEUR Acces(const Association<OBJET>&) const ;
    
      /// Op�rateur de comparaison
    	Booleen operator==(const FonctionObjetValeur<OBJET,VALEUR>& _right) const ;
    
      // @}
    
    private:
    
    
      std::map<OBJET*,VALEUR> fonction ;
      
    
    };

  }
}

#include <base/implantation/fonction_objet_valeur.cxx>


#endif
