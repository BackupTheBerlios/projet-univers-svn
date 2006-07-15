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


#ifndef _PU_MODELE_DESTRUCTIBLE_H_
#define _PU_MODELE_DESTRUCTIBLE_H_


#include <modele/energie.h>
#include <modele/objet.h>

namespace ProjetUnivers {


  namespace Modele {


    
      
    /// Propri�t� des objets pouvant subir des d�g�ts et �tre d�truits.

    /*!
      @todo
        Cette classe n'est qu'un squelette, implanter tache 2378.
    */
    class Destructible : public virtual Objet
    {
    public:
   
    /*!
      @name M�thodes principales
    */
    // @{
   
      /// Valeur de point de vie en pourcentage.
      /*!
        100% correspond � un objet neuf
        0% � un objet d�truit
      */
      Base::Entier PourcentagePointsDeVie() const ;
   
      /// Fait dubir un d�gat d'une certaine quantit� d'�nergie.
      void FaireSubirDegats(const Energie& _energie) ;
   
    // @}
   
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Destructible() ;
    
   
    protected:


      /// Classe abstraite donc constructeur prot�g�.
      Destructible(const Energie& _pointsDeVieTotal) ;
      
      /// En�rgie n�c�ssaire � sa destruction
      Energie pointsDeVieTotal ;
      
      /// Energie restante.
      Energie pointsDeVieActuel ;


    };

  }

}

#endif
