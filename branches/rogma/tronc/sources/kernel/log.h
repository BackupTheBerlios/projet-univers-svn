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

 
#ifndef _PU_KERNEL_LOG_H_
#define _PU_KERNEL_LOG_H_

#include <string>

namespace ProjetUnivers {
  namespace Kernel {
    namespace Log
    {
        
    /*!
      @name Initialisation
    */ 
    // @{
    
      /// Lance le traceur.
      void init() ;
      
      /// Ferme le traceur.
      void close() ;
  
    // @}
    /*!
      @name Utilisation
    */ 
    // @{
    
      /// Trace un message d'erreur.
      void ErrorMessage(const Chaine&) ;
      
      /// Trace un message d'information.
      void InformationMessage(const Chaine&) ;

      /// Trace un message interne.
      void InternalMessage(const Chaine&) ;    

    // @}
    
    }    
  }
}

#endif
