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

    template <class M> 
    Vue<M>::Vue(const Association<M>& _modele)
    : Implantation::BaseVue(), observe(_modele)
    {
      
      // vérifie que Modele dérive de Base::Modele
      DeriveDe<Modele,ProjetUnivers::Base::Modele>() ;
      observe->AjouterVue(*this) ;
    }
    
    template <class M> 
    Vue<M>::~Vue()
    {
      if (observe)
      {
        observe->EnleverVue(*this) ;
      }
    }
    template <class M> 
    void Vue<M>::DetacherDeModele()
    {
      observe = Association<M>() ;
    }

    template <class M> 
     Association<Modele> Vue<M>::AccesObserve() const
     {
       Modele* result = dynamic_cast<Modele*>(&*observe) ;
       return *result ;
     }

    
    
   
  }
}
