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
#include <kernel/model.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    /// For static registration of readers.
    class RelationReaderRegistration
    {
    public:

      RelationReaderRegistration(const std::string& name,const TypeIdentifier& type)
      {
        Relation::_registerReader(name,type) ;
      }
    };

    /// Register a view on relation.
    template <class _Relation,class _ViewPoint,class _View>
    class RelationViewRegistration
    {
    public:

      RelationViewRegistration(Relation::ViewBuilder builder)
      {
        Relation::registerViewBuilder(getClassTypeIdentifier(_Relation),
                                      getClassTypeIdentifier(_ViewPoint),
                                      builder) ;
        Relation::registerMapping(getClassTypeIdentifier(_View),
                                  getClassTypeIdentifier(_ViewPoint),
                                  getClassTypeIdentifier(_Relation)) ;
      }

    };

    /// Register a controller on relation.
    template <class _Relation,class _ControlerSet,class _Controler>
    class RelationControlerRegistration
    {
    public:

      RelationControlerRegistration(Relation::ControlerBuilder builder)
      {
        Relation::registerControlerBuilder(getClassTypeIdentifier(_Relation),
                                           getClassTypeIdentifier(_ControlerSet),
                                           builder) ;
      }

    };

  }
}
