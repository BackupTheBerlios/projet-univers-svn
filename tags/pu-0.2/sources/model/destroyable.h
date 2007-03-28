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


#ifndef PU_MODEL_DESTROYABLE_H_
#define PU_MODEL_DESTROYABLE_H_


#include <model/energy.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {


    
      
    /// Propri�t� des objets pouvant subir des d�g�ts et �tre d�truits.
    /*!
    @todo
      Cette classe n'est qu'un squelette, implanter tache 2378.
    @par Etat
      planning
    */
    class Destroyable : public Kernel::Trait
    {
    public:

      /// Construit � neuf.
      Destroyable(const Energy& _pointsDeVieTotal) ;
   
    /*!
      @name M�thodes principales
    */
    // @{
   
      /// Valeur de point de vie en pourcentage.
      /*!
        100% correspond � un objet neuf
        0% � un objet d�truit
      */
      float getLife() const ;
   
      /// Fait dubir un d�gat d'une certaine quantit� d'�nergie.
      void damage(const Energy& _energy) ;
   
    // @}
   
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Destroyable() ;
    
   
    protected:


      
      /// En�rgie n�c�ssaire � sa destruction
      Energy totalResistance ;
      
      /// Energy restante.
      Energy resistance ;


    };

  }

}

#endif
