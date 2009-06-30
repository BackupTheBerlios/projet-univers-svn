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

    /// A pair of objects (precursor for a relation).
    class ObjectPair
    {
    public:

      ObjectPair(Object* object1,Object* object2)
      : m_object1(object1),
        m_object2(object2)
      {}

      ObjectPair(const ObjectPair& pair)
      : m_object1(pair.m_object1),
        m_object2(pair.m_object2)
      {}

      ObjectPair(const Relation& relation)
      : m_object1(relation.getObjectFrom()),
        m_object2(relation.getObjectTo())
      {}

      bool operator ==(const ObjectPair& pair) const
      {
        return m_object1 == pair.m_object1 && m_object2 == pair.m_object2 ;
      }

      bool operator <(const ObjectPair& pair) const
      {
        return m_object1 < pair.m_object1 ||
               (m_object1 == pair.m_object1 && m_object2 < pair.m_object2) ;
      }

      /// True iff @c formula is valid for thist link.
      bool getValidity(const Formula* formula) const
      {
        // we choose object from's model as canonical storage
        return m_object1->getModel()->getValidity(*this,formula) ;
      }

      /// Change the validity of @c formula for @c this
      void setValidity(const Formula* formula,const bool& validity) const
      {
        m_object1->getModel()->setValidity(*this,formula,validity) ;
      }

      /// Access to the number of true child formulae for @c this
      unsigned short getNumberOfTrueChildFormulae(const Formula* formula) const
      {
        return m_object1->getModel()->getNumberOfTrueChildFormulae(*this,formula) ;
      }

      /// Change the number of true child formulae for @c this
      void setNumberOfTrueChildFormulae(const Formula* formula,unsigned short number) const
      {
        m_object1->getModel()->setNumberOfTrueChildFormulae(*this,formula,number) ;
      }

      Object* getObjectFrom() const
      {
        return m_object1;
      }

      Object* getObjectTo() const
      {
        return m_object2;
      }


      ObjectReference m_object1 ;
      ObjectReference m_object2 ;


    };

    template <class _Relation>
    Link<_Relation>::Link(Object* object1,Object* object2)
    {
      Relation::createLink(getClassTypeIdentifier(_Relation),object1,object2) ;
    }

    template <class _Relation> class Link< Inverse<_Relation> >
    {
    public:
      Link(Object* object1,Object* object2)
      {
        Relation::createLink(getClassTypeIdentifier(_Relation),object2,object1) ;
      }
    };

    template <class _Relation>
    UnLink<_Relation>::UnLink(Object* object1,Object* object2)
    {
      Relation::destroyLink(getClassTypeIdentifier(_Relation),object1,object2) ;
    }

    template <class _Relation> class UnLink< Inverse<_Relation> >
    {
    public:
      UnLink(Object* object1,Object* object2)
      {
        Relation::destroyLink(getClassTypeIdentifier(_Relation),object2,object1) ;
      }
    };

    namespace Implementation
    {
      /// Implementation of link access
      template <class Relation> class GetLink
      {
      public:

        /// Implementation of getLinked
        static std::set<Object*> get(Object* object)
        {
          return object->getModel()->getRelations(getClassTypeIdentifier(Relation),object) ;
        }

        /// Implementation of areLinked
        static bool areLinked(Object* object1,Object* object2)
        {
          std::set<Object*> linked(get(object1)) ;
          return linked.find(object2) != linked.end() ;
        }


      };

      /// Specialisation for inverse relation
      template <class Relation> class GetLink<Inverse<Relation> >
      {
      public:

        /// Implementation of getLinked
        static std::set<Object*> get(Object* object)
        {
          return object->getModel()->getInverseRelations(getClassTypeIdentifier(Relation),object) ;
        }

        /// Implementation of areLinked
        static bool areLinked(Object* object1,Object* object2)
        {
          std::set<Object*> linked(get(object1)) ;
          return linked.find(object2) != linked.end() ;
        }

      };
    }

    template <class _Relation>
    std::set<Object*> Relation::getLinked(Object* object)
    {
      return Implementation::GetLink<_Relation>::get(object) ;
    }

    template <class _Relation>
    bool Relation::areLinked(Object* object1,Object* object2)
    {
      return Implementation::GetLink<_Relation>::areLinked(object1,object2) ;
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
