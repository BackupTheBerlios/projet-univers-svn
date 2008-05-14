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
namespace ProjetUnivers {
  namespace Kernel {
   
    template<class _Trait,class _ControlerSet> 
    _Trait* Controler<_Trait,_ControlerSet>::getTrait() const
    {
      _Trait* result = dynamic_cast<_Trait*>(m_trait) ;
      return result ;
    }
    template<class _Trait,class _ControlerSet> 
    Controler<_Trait,_ControlerSet>::~Controler()
    {}

    template<class _Trait,class _ControlerSet> 
    Controler<_Trait,_ControlerSet>::Controler(
      _Trait*        i_trait,
      _ControlerSet* i_controler_set)
    : BaseControler(i_trait,i_controler_set)
    {}

    template<class _Trait,class _ControlerSet> 
    void Controler<_Trait,_ControlerSet>::onInit() 
    {
    }
    
    template<class _Trait,class _ControlerSet> 
    void Controler<_Trait,_ControlerSet>::onClose()
    {
    } 
    
    template<class _Trait,class _ControlerSet> 
    void Controler<_Trait,_ControlerSet>::onChangeParent(Object*)
    {
    }

    template<class _Trait,class _ControlerSet> 
    void Controler<_Trait,_ControlerSet>::onUpdate()
    {
    }
    template<class _Trait,class _ControlerSet>
    _ControlerSet* Controler<_Trait,_ControlerSet>::getControlerSet() const
    {
      return static_cast<_ControlerSet*>(m_controler_set) ;
    }  
  }
}
