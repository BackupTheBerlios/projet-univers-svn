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

#include <kernel/composition.h>
#include <kernel/vue.h>
#include <kernel/model.h>


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

  class ViewA : public ProjetUnivers::Kernel::View<A>
  {
  public:
    
    ViewA(const ProjetUnivers::Kernel::Association<A>& _a)
    : ProjetUnivers::Kernel::View<A>(_a)
    {}
      
    virtual void Raffraichir()
    {}
           
    
  };
   
   
}

int toto()
{
  
  ProjetUnivers::Kernel::Composition<A> a(new A()) ;
  
  
  // doit provoquer une erreur de compilation car A ne dérive pas de Model.
  ViewA vueA(a) ;  
}
