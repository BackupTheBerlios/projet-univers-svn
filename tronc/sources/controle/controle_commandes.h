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

#ifndef _PU_CONTROLE_CONTROLE_COMMANDES_H_
#define _PU_CONTROLE_CONTROLE_COMMANDES_H_

#include <base/association.h>
#include <noyau/controle.h>


namespace ProjetUnivers {


  // Déclaration en avant.
  namespace Modele {
    
    class CommandesPilotage ;
  }
  
  namespace Controle {
    
    
    
    
      
    /// Le contrôle qui gère les commandes de pilotage.

    /*!
      
      Récupère les entrées et effectue les actions correspondantes 
      sur les commandes de pilotage.
     
      Type de classe :
        - Objet
        - Concret
    */
    class ControleCommandes : public Noyau::Controle {
    public:

      /// Constructeur
      ControleCommandes(
        const Base::Association<Modele::CommandesPilotage>& _commandes) ;


      /// Réalise son contrôle.
 
      /*!
        
        
        
      */
      virtual void Controler() ;
 
      

      
    private:

      // ****************
      /// @name Attributs
      // ****************
      // @{
      
      
      /// Les commandes de pilotage.
      Base::Association<Modele::CommandesPilotage> commandes ;


      // @}
    };
    
    
  }

}

#endif
