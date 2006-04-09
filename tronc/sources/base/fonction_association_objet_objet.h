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
 
#ifndef _BASE_FONCTION_ASSOCIATION_OBJET_OBJET_H_
#define _BASE_FONCTION_ASSOCIATION_OBJET_OBJET_H_

#include <map>

#include <base/association.h>


namespace ProjetUnivers 
{

  namespace Base 
  {
    
    /// Une fonction qui associe un �l�ment de ObjetValeur � un �l�ment de ObjetCle. 
    /*!  
      ObjetCle et ObjetValeur doivent �tre des classe d'objets.
      
      @par Test Test
        Test� le 06/04/2006 avec TestFonctionAssociationObjetObjet :
        - Constructeur
        - Ajouter
        - Acces (� un existant et � un non existant)
    */
    template <class ObjetCle, class ObjetValeur > 
    class FonctionAssociationObjetObjet
    {
    public:
    
    /// @name Construction
    // @{      
    
    
      /// Constructeur.
      FonctionAssociationObjetObjet() ;
    
      /// Constructeur de copie.
      FonctionAssociationObjetObjet(const FonctionAssociationObjetObjet&);
    
    // @}           
    /// @name Modification
    // @{      
    
      /// Ajoute un �l�ment.
      void Ajouter(const Association<ObjetCle>&, const Association<ObjetValeur>&) ;
    
      /// Modifie l'�l�ment associ� � une cl�. 
      /*!
        Si l'�l�ment n'existe pas alors cela a l'effet de Ajouter.
      */
      void Changer(const Association<ObjetCle>&, const Association<ObjetValeur>&) ;
    
    // @}
    // *************************
    /// @name Acc�s
    // *************************      
    // @{      
    
      /// Acc�s � un �l�ment en fonction de l'identifiant.
      Association<ObjetValeur> Acces(const Association<ObjetCle>&) const ;
    
      /// Op�rateur de comparaison
      /*!
        @todo
          permetre n'importe quel type d'Objet, pour g�rer les h�ritages.
      */
      Booleen operator==(const FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>&) const ;
    
    // @}
    
    private:
    
    
      std::map<ObjetCle*,ObjetValeur*> fonction ;
      
    
    };

  }
}

#include <base/implantation/fonction_association_objet_objet.cxx>


#endif
