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
 
#ifndef _BASE_FONCTION_ASSOCIATION_VALEUR_OBJET_H_
#define _BASE_FONCTION_ASSOCIATION_VALEUR_OBJET_H_

#include <map>

#include <base/association.h>


namespace ProjetUnivers 
{

  namespace Base 
  {
    
    ///  Une fonction qui associe un �l�ment de Objet � un �l�ment de VALEUR. 
    /*!  
      Objet doit �tre une classe d'objets et VALEUR une classe de valeurs.
      
      @par Test
        Test� le 02/04/2006 avec TestFonctionAssociationValeurObjet :
        - Constructeur
        - Ajouter
        - Acces (� un existant et � un non existant)
    */
    template <typename Valeur, class Objet > 
    class FonctionAssociationValeurObjet
    {
    public:
    
      /// @name Construction
      // @{      
    
    
      /// Constructeur.
      FonctionAssociationValeurObjet() ;
    
      /// Constructeur de copie.
      FonctionAssociationValeurObjet(const FonctionAssociationValeurObjet&);
    
      // @}
            
      /// @name Modification
      // @{      
    
      /// Ajoute un �l�ment.
      void Ajouter(const Valeur&, const Association<Objet>&) ;
    
      /// Modifie l'�l�ment associ� � une Valeur.. 
      /*!
        Si l'�l�ment n'existe pas alors cela a l'effet de Ajouter.
      */
      void Changer(const Valeur&, const Association<Objet>&) ;
    
      // @}
          

      // *************************
      /// @name Acc�s
      // *************************      
      // @{      
    
      /// Acc�s � un �l�ment en fonction de l'identifiant.
      Association<Objet> Acces(const Valeur&) const ;
    
      /// Op�rateur de comparaison
      /*!
        @todo
          permetre n'importe quel type d'Objet, pour g�rer les h�ritages.
      */
      Booleen operator==(const FonctionAssociationValeurObjet<Valeur,Objet>&) const ;
    
      // @}
    
    private:
    
    
      std::map<Valeur,Objet*> fonction ;
      
    
    };

  }
}

#include <base/implantation/fonction_association_valeur_objet.cxx>


#endif
