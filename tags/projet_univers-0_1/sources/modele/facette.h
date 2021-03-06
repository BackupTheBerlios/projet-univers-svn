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
#ifndef PU_MODELE_FACETTE_H_
#define PU_MODELE_FACETTE_H_

#include <base/association.h>
#include <base/modele.h>


namespace ProjetUnivers {
  namespace Modele {

    class Objet ;

    /// Une facette d'un objet.
    /*!
      C'est une partie d'un objet dans un mod�le � d�l�gation.
      Une facette appartient � un seul objet. 
      Un objet peut avoir autant de facettes qu'il veut.
      Un objet ne peut avoir qu'une seule facette d'un certain type :
      - par exemple, un objet ne peut avoir qu'une seule facette de type 
        Positionn�, car l'objet n'a qu'une seule position.
        
      Une facette d'objet regoupe un ensemble d'attributs de l'objet.
    */
    class Facette : public Base::Modele
    {
    public:

    /*!
      @name Partie "objet"
    
    */
    // @{
      
      Base::Association<Objet> AccesObjet() const ;
      
//        virtual 
//          Base::Association<Facette> 
//          AccesFacette(const Base::Chaine& _nom) const :
//          
    
    // @}
    
      /// Type de la facette.
//      virtual Base::Chaine Type() const = 0 ;

      /// Autres facettes obligatoires
      /*!
        Il s'agit en quelque sorte d'un h�ritage de facette.
        
        @todo 
          voir si c'ets vraiment utile
      */
//        virtual Base::EnsembleValeur<Base::Chaine> FacettesResquises() const = 0 ;

      virtual ~Facette() ;


      /// Conversion vers une autre Facette
      /*!
        pas au point.
      */


    protected: 
    
      /// Cr�� une facette pour un objet.
      Facette() ;
      
      /// Objet sur lequel s'applique la facette.
      Base::Association<Objet> objet ;
      
      friend class Objet ;
            
    };



  }
}



#endif /*PU_MODELE_FACETTE_H_*/
