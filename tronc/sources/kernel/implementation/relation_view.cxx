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
namespace ProjetUnivers
{
  namespace Kernel
  {
    class Model ;

    template <class _ViewPoint>
    RelationView<_ViewPoint>::RelationView()
    {}

    template <class _ViewPoint>
    RelationView<_ViewPoint>::~RelationView()
    {}

    template <class _ViewPoint>
    _ViewPoint* RelationView<_ViewPoint>::getViewPoint() const
    {
      return static_cast<_ViewPoint*>(m_viewpoint) ;
    }
    /// default implementation : empty

    template <class _ViewPoint>
    void RelationView<_ViewPoint>::onInit()
    {
    }

    template <class _ViewPoint>
    void RelationView<_ViewPoint>::onClose()
    {
    }

    template <class _ViewPoint>
    void RelationView<_ViewPoint>::onUpdate()
    {
    }

  }
}


