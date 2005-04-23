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

#ifndef _PU_AFFICHAGE_POINT_DE_VUE_H_
#define _PU_AFFICHAGE_POINT_DE_VUE_H_

#include <noyau/vue.h>

namespace ProjetUnivers {



  namespace Affichage {


    /// Le fait de voir une partie du mod�le depuis un certain endroit.
    /*!
      Type de classe :
        - Objet
        - Abstrait
    */
    class PointDeVue : public Noyau::Vue {
    public:

      /// Active ce point de vue???
      /// virtual void Activer() ;

    
      /// Destructeur de classe abstraite.
      virtual ~ PointDeVue() ;

    protected:
      
      /// Contructeur de classe abstraite.
      PointDeVue() ;
      
    };

  }
}


#endif

