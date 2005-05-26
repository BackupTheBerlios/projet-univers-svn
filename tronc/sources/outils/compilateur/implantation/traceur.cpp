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
#include <outils/compilateur/traceur.h>

namespace ProjetUnivers {

  namespace Outils {
  
    namespace Compilateur 
    {

      const char* nomFichierDebug = "compilateur_debug.log" ;
      const char* nomFichierSortie = "compilateur_sortie.log" ;

      FILE* debug ;
      FILE* sortie ;
      
      Base::Composition<rlog::StdioNode> traceurDebug ;
      Base::Composition<rlog::StdioNode> traceurSortie ;

      /// Lance le traceur.
      void OuvrirTraceur()
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
        
        // on se définit notre propre channel de sortie
        DEF_CHANNEL("compilateur", rlog::Log_Info) ;

        traceurSortie->subscribeTo( rlog::GetGlobalChannel( "compilateur" ));
          
      }
      
      /// Ferme le traceur.
      void FermerTraceur() 
      {
        fclose(debug) ;
        fclose(sortie) ;

      }


    }
  }
}
 
 