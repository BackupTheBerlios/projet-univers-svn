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

#include <stdio.h>

#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>

#include <base/composition.h>

namespace ProjetUnivers {

  namespace Base {

    namespace Traceur
    {
  
      const Chaine nomFichierDebug("debug.log") ;
      const Chaine nomFichierSortie("sortie.log") ;
  
      FILE* debug ;
      FILE* sortie ;
      
      Base::Composition<rlog::StdioNode> traceurDebug ;
      Base::Composition<rlog::StdioNode> traceurSortie ;
  
      void Initialiser()
      {
        
        // erreurs et debug
        debug = fopen(nomFichierDebug, "w") ;
        traceurDebug = new rlog::StdioNode(fileno(debug)) ;
  
  
        traceurDebug->subscribeTo( rlog::GetGlobalChannel( "warning" ));
        traceurDebug->subscribeTo( rlog::GetGlobalChannel( "error" ));
        traceurDebug->subscribeTo( rlog::GetGlobalChannel( "debug" ));  
  
        // sortie
        sortie = fopen(nomFichierSortie, "w") ;
        traceurSortie = new rlog::StdioNode(fileno(sortie)) ;
        
        // on se d�finit notre propre channel de sortie
        DEF_CHANNEL("ProjetUnivers", rlog::Log_Info) ;
  
        traceurSortie->subscribeTo( rlog::GetGlobalChannel( "ProjetUnivers" ));
          
      }
      
      void Terminer() 
      {
        fclose(debug) ;
        fclose(sortie) ;
  
      }

      void MessageErreur(const Chaine& _message)
      {
        rError(_message) ;
      }
      
      /// Trace un message d'information.
      void MessageInformation(const Chaine& _message)
      {
        rLog(RLOG_CHANNEL("ProjetUnivers"), _message) ;
      }

      void MessageInterne(const Chaine& _message)
      {
        rDebug(_message) ;
      }


    }

  }
}
