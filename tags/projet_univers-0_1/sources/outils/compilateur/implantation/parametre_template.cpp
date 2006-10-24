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

#include <rlog/rlog.h>

#include <opencxx/parser/token-names.h>

#include <base/chaine.h>


#include <outils/compilateur/parametre_template.h>
#include <outils/compilateur/traceur.h>

using namespace Opencxx ;
using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
      /// Construit le param�tre.
      ParametreTemplate* ParametreTemplate::Construire(Ptree* parametre,
                                                      Environment* environement)
      {
      
        if (parametre->IsA(Constant))
        {
          rDebug(Chaine(parametre->ToString()) + "est une constante") ;
        }
        else
        {
          rDebug(Chaine(parametre->ToString()) + "n'est pas une constante") ;          
        }
        
      }

      Base::Chaine ParametreTemplate::Afficher() const
      {
        return "" ;
      }

      ParametreTemplate::~ParametreTemplate()
      {}

      ParametreTemplate::ParametreTemplate()
      {}

    }
  }
}
