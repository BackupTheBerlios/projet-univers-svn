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

#ifndef _PU_UNIVERS_PERSONNAGE_H_
#define _PU_UNIVERS_PERSONNAGE_H_

#include <base/association.h>
#include <base/chaine.h>
#include <modele/objet_physique.h>


namespace ProjetUnivers {

  namespace Modele {

    class Poste ;

    /// Personnage.
    /*!
      Un personnage est une entité physique du monde qui est douée d'une 
      autonomie de choix d'actions, i.e., une âme.  
      Cette âme peyut être contrôlée soit 
        - directement par le joueur 
        - par programme (une IA).
    */
    class Personnage : public ObjetPhysique {
    public:
    
      /// @name Construction
      // @{

      Personnage(const Base::Chaine& _nom, const Base::Chaine& _prenom) ;

      // @}
      /// @name Modifications
      // @{
    
    
      /// Change de poste.
      /*!
        Un changement de poste n'est pas toujours possible.
      */
      void ChangerPoste(const Base::Association< Poste > _nouveauPoste) ;
    
    
      // @}
      /// @name Lecture
      // @{
      
      
      /// Accès au nom
      Base::Chaine Nom() const ;
      
      /// Accès au prénom
      Base::Chaine Prenom() const ;
      
      /// Accès au poste occupé.
      Base::Association< Poste > AccesPoste() const ;
      
      
      //@}
    private:

      /// @name Attributs
      // @{
      
    
      /// Le nom de famille du personnage.
      /*!
        \todo
          généraliser pour les cultures qui possède un autre système de 
          désignation d'individus.
      */
      Base::Chaine nom ;
      
      /// Le prénom du personnage.      
      /*!
        \todo
          généraliser pour les cultures qui possède un autre système de 
          désignation d'individus.
      */
      Base::Chaine prenom ;
      
      /// Poste occupé par le personnage dans la mission en cours.
      /*!
        Attribut non persistant.
      */
      Base::Association< Poste > poste ;
      
      
      // @}
    };
    
  }
}

#endif
