/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#pragma once

#include <kernel/observer.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Trait ;
    class ControlerSet ;
    class Object ;

    /// A controler on a trait.
    class BaseControler : public Observer
    {
    public:

      /// Any controler does a simulation.
      virtual void simulate(const float& seconds) ;

      /// Some controlers prepare simulation.
      virtual void prepare() ;

      /// init the controler after construction.
      virtual void realInit() ;

      /// abstract class means virtual destructor.
      virtual ~BaseControler() ;

      /// Access to controler set.
      ControlerSet* getControlerSet() const ;

      /// Access to the first parent controler of the same controler set.
      /*!
        @return the first (up, by parentship) initialised controler
      */
      template <class _Controler> _Controler* getControler() const ;

      /// Access to the first ancestor controler of the same controler set.
      template <class _Controler> _Controler* getAncestorControler() const ;

    protected:

      /// abstract class means protected constructor.
      BaseControler(Trait* trait,ControlerSet* controler_set) ;
      BaseControler() ;


      ControlerSet* m_controler_set ;

    private:

      void setControlerSet(ControlerSet* controler_set) ;

      friend class Trait ;

    };

  }
}
#include <kernel/implementation/base_controler.cxx>

