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

#ifndef _PU_UNIVERS_SYSTEME_STELLAIRE_H_
#define _PU_UNIVERS_SYSTEME_STELLAIRE_H_

#include <modele/facette.h>

namespace ProjetUnivers {
  namespace Modele {
    
    /// Représente un système stellaire.
    /*!
      @par Etat
        planning
    */
    class SystemeStellaire : public Facette 
    {
    public:


    // *******************
    /*! 
      @name Constructeur
    */
    // *******************
    // @{

      /// Constructeur.
      SystemeStellaire() ;
      
      
    // @}
    // *******************
    /*! 
      @name Acces
    */
    // *******************
    // @{

      /// Les étoiles du système
      Base::EnsembleAssociation<Objet> AccesEtoiles() const ;
    
    // @}

    };


  // *******************
  /*! 
    @name Fonctions d'aide
  */
  // *******************
  // @{

    
    /// Acces au systeme stellaire contenant l'objet paramètre.
    /*!
    @deprecated 
      utiliser AccesParent<SystemeStellaire> à la place
    */
    Base::Association<SystemeStellaire> AccesSysteme(const Base::Association<Objet>&) ;
    
    
  // @}  
    
  }
}

#endif
