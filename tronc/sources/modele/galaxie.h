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

#ifndef _PU_MODELE_GALAXIE_H_
#define _PU_MODELE_GALAXIE_H_

#include <base/chaine.h>
#include <base/ensemble_association.h>
#include <base/association.h>


#include <modele/nom.h>
#include <modele/facette.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
    
    class SystemeStellaire ;
    
      
    /// Une galaxie.

    /*!
    @par Etat
      planning
      
    */
    class Galaxie : public Facette 
    {
    public:

      /// Constructeur.
      Galaxie(const Nom& _nom) ;
      
      /// Ajoute un nouveau système
      void Ajouter(const Base::Association<SystemeStellaire>& _systeme) ;
      
      
    private:
      

      Nom nom ;

      /// Les systèmes "actifs".
      /*!
        Ceux dont on a obligatoirement besoin pour le jeux...
      */      
      Base::EnsembleAssociation<SystemeStellaire> systemes ;
      

    };
    
    
  }

}

#endif
