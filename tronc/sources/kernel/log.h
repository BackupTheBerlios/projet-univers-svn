/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_KERNEL_LOG_H_
#define PU_KERNEL_LOG_H_

#include <string>

#define RLOG_COMPONENT "ProjetUnivers"

#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>


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
      #define ErrorMessage(i_message) rError(std::string(i_message).c_str())
      
      /// Trace un message d'information.
      #define InformationMessage(i_message) rLog(RLOG_CHANNEL("ProjetUnivers"), std::string(i_message).c_str())

      /// Trace un message interne.
      #define InternalMessage(i_message) rDebug(std::string(i_message).c_str())    

    // @}

    
    }    
  }
}

#endif
