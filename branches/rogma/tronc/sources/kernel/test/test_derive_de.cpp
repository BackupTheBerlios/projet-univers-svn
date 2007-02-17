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

#include <base/composition.h>
#include <base/vue.h>
#include <base/modele.h>


/*!
  Vérifie qu'il existe uen erreur de compilation dans ce programme.
*/

     
namespace {
 
  class A 
  {
  public:
    A()
    {}
  };

  class VueA : public ProjetUnivers::Base::Vue<A>
  {
  public:
    
    VueA(const ProjetUnivers::Base::Association<A>& _a)
    : ProjetUnivers::Base::Vue<A>(_a)
    {}
      
    virtual void Raffraichir()
    {}
           
    
  };
   
   
}

int toto()
{
  
  ProjetUnivers::Base::Composition<A> a(new A()) ;
  
  
  // doit provoquer une erreur de compilation car A ne dérive pas de Model.
  VueA vueA(a) ;  
}
