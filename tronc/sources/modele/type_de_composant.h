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

#ifndef _PU_MODELE_TYPE_COMPOSANT_H_
#define _PU_MODELE_TYPE_COMPOSANT_H_


#include <base/association.h>
#include <base/fonction_composition_valeur_objet.h>

#include <modele/objet_abstrait.h>
#include <modele/duree.h>
#include <modele/nom.h>
#include <modele/energie.h>
#include <modele/masse.h>


namespace ProjetUnivers {

  namespace Modele {
    
    class Composant ;
    class EtatTypeDeComposant ;
    
    /// Repr�sente le type d'un composant.
    
    /*!
      
      Un Composant repr�sente une instance r��lle d'un TypeDeComposant. C'est 
      la m�me diff�rence qu'entre une voiture donn�e (la mienne par exemple) et 
      le mod�le de cette voiture (une renault clio). 
    
      Type de classe
      - Objet
      - Abstrait
    */
    class TypeDeComposant : public ObjetAbstrait
    {
    public:

      /// Simule l'action de ce type de composant sur un composant particulier.
      /*
        Simule l'action pendant une certaine dur�e d'une instance de ce type de 
        composant �tant dans certain �tat.
      */
      virtual void Simuler(const Base::Association<Composant>& _etat, 
                           const Duree& _duree) const = 0 ;


      /// 
      virtual Composant* Construire() const ;
    
      /// Destructeur de classe abstraite.
      virtual ~TypeDeComposant() ;
      

    protected:    
    
      /// Constructeur de classe abstraite.
      TypeDeComposant(const Nom&, const Energie&, const Masse&) ;
    
      /// Nom du type de composant.
      Nom nom ;

      /// Une fonction des pourcentages de d�gats vers les �tats
      Base::FonctionCompositionValeurObjet<Base::Entier,
                                           EtatTypeDeComposant> etats ;


      // ->dans �tat
      /// Points de vie du composant neuf.
      Energie resistance ;
      
      /// La masse du composant neuf.
      Masse masse ;

      friend class Composant ;

    };
    
  }
}

#endif
