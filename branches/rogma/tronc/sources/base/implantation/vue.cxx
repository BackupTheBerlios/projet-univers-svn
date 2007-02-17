/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <base/derive_de.h>

namespace ProjetUnivers {

  namespace Base {

    class Modele ;

    template <class Modele> 
    Vue<Modele>::Vue(const Association<Modele>& _modele)
    : Implantation::BaseVue(), observe(_modele)
    {
      
      // vérifie que Modele dérive de Base::Modele
      DeriveDe<Modele,ProjetUnivers::Base::Modele>() ;
      observe->AjouterVue(*this) ;
    }
    
    template <class Modele> 
    Vue<Modele>::~Vue()
    {
      if (observe)
      {
        observe->EnleverVue(*this) ;
      }
    }
    template <class Modele> 
    void Vue<Modele>::DetacherDeModele()
    {
      observe = Association<Modele>() ;
    }

    
    
   
  }
}
