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
#include <kernel/composition.h>
#include <kernel/vue.h>
#include <kernel/model.h>


/*!
  Check that exists a compile error in that program.
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
  
  
  // Must trigger a compile error.
  ViewA vueA(a) ;  
}
