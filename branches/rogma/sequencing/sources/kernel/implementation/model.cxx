/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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

    template <class _Relation>
    Link<_Relation>::Link(Object* object1,Object* object2)
    {
      Relation relation(getClassTypeIdentifier(_Relation),object1,object2) ;
      object1->getModel()->addRelation(relation) ;
    }

    template <class _Relation> class Link< Inverse<_Relation> >
    {
    public:
      Link(Object* object1,Object* object2)
      {
        Relation relation(getClassTypeIdentifier(_Relation),object2,object1) ;
        object1->getModel()->addRelation(relation) ;
      }
    };

    template <class _Relation>
    UnLink<_Relation>::UnLink(Object* object1,Object* object2)
    {
      Relation relation(getClassTypeIdentifier(_Relation),object1,object2) ;
      object1->getModel()->removeRelation(relation) ;
    }

    template <class _Relation> class UnLink< Inverse<_Relation> >
    {
    public:
      UnLink(Object* object1,Object* object2)
      {
        Relation relation(getClassTypeIdentifier(_Relation),object2,object1) ;
        object1->getModel()->removeRelation(relation) ;
      }
    };

    namespace Implementation
    {
      /// Implementation of link access
      template <class Relation> class GetLink
      {
      public:

        static std::set<Object*> get(Object* object)
        {
          return object->getModel()->getRelations(getClassTypeIdentifier(Relation),object) ;
        }
      };

      /// Specialisation for inverse relation
      template <class Relation> class GetLink<Inverse<Relation> >
      {
      public:

        static std::set<Object*> get(Object* object)
        {
          return object->getModel()->getInverseRelations(getClassTypeIdentifier(Relation),object) ;
        }
      };
    }

    template <class _Relation>
    std::set<Object*> Relation::getLinked(Object* object)
    {
      return Implementation::GetLink<_Relation>::get(object) ;
    }

    template <class T> T* Model::getControlerSet() const
    {
      for(std::set<ControlerSet*>::const_iterator
            controlerset = m_controler_sets.begin() ;
          controlerset != m_controler_sets.end() ;
          ++controlerset)
      {
        T* temp = dynamic_cast<T*>(*controlerset) ;
        if (temp)
          return temp ;
      }

      return NULL ;
    }

    template <class T> T* Model::getViewPoint() const
    {
      for(std::set<ViewPoint*>::const_iterator
            viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        T* temp = dynamic_cast<T*>(*viewpoint) ;
        if (temp)
          return temp ;
      }

      return NULL ;
    }

  }
}
