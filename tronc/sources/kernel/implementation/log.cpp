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
#include <stdio.h>

#include <kernel/log.h>

namespace ProjetUnivers {

  namespace Kernel {

    namespace Log
    {
  
      const std::string debugFileName("debug.log") ;
      const std::string outputFileName("sortie.log") ;
  
      FILE* debug ;
      FILE* sortie ;
      
      std::auto_ptr<rlog::StdioNode> debugLog ;
      std::auto_ptr<rlog::StdioNode> outputLog ;
  
      void init()
      {
      #ifndef NDEBUG
        
        // erreurs et debug
        debug = fopen(debugFileName.c_str(), "w") ;
        debugLog.reset(new rlog::StdioNode(fileno(debug))) ;
  
  
        debugLog->subscribeTo( rlog::GetGlobalChannel( "warning" ));
        debugLog->subscribeTo( rlog::GetGlobalChannel( "error" ));
        debugLog->subscribeTo( rlog::GetGlobalChannel( "debug" ));  
  
        // sortie
        sortie = fopen(outputFileName.c_str(), "w") ;
        outputLog.reset(new rlog::StdioNode(fileno(sortie))) ;
        
        // on se d�finit notre propre channel de sortie
        DEF_CHANNEL("ProjetUnivers", rlog::Log_Info) ;
  
        outputLog->subscribeTo( rlog::GetGlobalChannel( "ProjetUnivers" ));

      #endif          
      }
      
      void close() 
      {
      #ifndef NDEBUG
        fclose(debug) ;
        fclose(sortie) ;
      #endif          
      }



    }

  }
}
