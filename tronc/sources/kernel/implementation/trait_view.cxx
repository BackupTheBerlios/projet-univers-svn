/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <kernel/inherits.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    class Model ;

    template <class _Trait,class _ViewPoint>
    TraitView<_Trait,_ViewPoint>::TraitView()
    {
      Inherits<_Trait,ProjetUnivers::Kernel::Trait>() ;
    }
    
    template <class _Trait,class _ViewPoint> 
    TraitView<_Trait,_ViewPoint>::~TraitView()
    {}
    
    template <class _Trait,class _ViewPoint> 
    _Trait* TraitView<_Trait,_ViewPoint>::getTrait() const
    {
      _Trait* result = dynamic_cast<_Trait*>(m_trait) ;
      return result ;
    }

    template <class _Trait,class _ViewPoint>
    template <class T> TraitReference<T> TraitView<_Trait,_ViewPoint>::getTrait() const
    {
      return getObject()->getTrait<T>() ;
    }
    
    template <class _Trait,class _ViewPoint>
    _ViewPoint* TraitView<_Trait,_ViewPoint>::getViewPoint() const
    {
      return static_cast<_ViewPoint*>(m_viewpoint) ;
    }
    /// default implementation : empty
    
    template <class _Trait,class _ViewPoint>
    void TraitView<_Trait,_ViewPoint>::onInit() 
    {
    }
    
    template <class _Trait,class _ViewPoint>
    void TraitView<_Trait,_ViewPoint>::onClose()
    {
    } 
    
    template <class _Trait,class _ViewPoint>
    void TraitView<_Trait,_ViewPoint>::onChangeParent(Object*)
    {
    }

    template <class _Trait,class _ViewPoint>    
    void TraitView<_Trait,_ViewPoint>::onUpdate()
    {
    }
   
  }
}
