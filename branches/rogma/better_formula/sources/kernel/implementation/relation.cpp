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
#include <kernel/view_point.h>
#include <kernel/controler_set.h>
#include <kernel/relation.h>
#include <kernel/deduced_trait.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    Relation::StaticStorage* Relation::StaticStorage::get()
    {
      static StaticStorage instance ;
      return &instance ;
    }

    Relation::ViewBuilder Relation::StaticStorage::getViewBuilder(ViewPoint* viewpoint,
                                                                  const Relation& relation)
    {
      std::map<std::pair<TypeIdentifier,TypeIdentifier>,
               ViewBuilder>::iterator                     finder ;

      finder = m_view_builders.find(std::make_pair(getObjectTypeIdentifier(viewpoint),relation.getType())) ;
      if (finder != m_view_builders.end())
        return finder->second ;

      return ViewBuilder() ;
    }

    Relation::ControlerBuilder Relation::StaticStorage::getControlerBuilder(ControlerSet* controler_set,
                                                                            const Relation& relation)
    {
      std::map<std::pair<TypeIdentifier,TypeIdentifier>,
               ControlerBuilder>::iterator                finder ;

      finder = m_controler_builders.find(std::make_pair(getObjectTypeIdentifier(controler_set),relation.getType())) ;
      if (finder != m_controler_builders.end())
        return finder->second ;

      return ControlerBuilder() ;
    }

    Relation::Relation(const TypeIdentifier& type,Object* object1,Object* object2)
    : m_object_from(object1),
      m_object_to(object2),
      m_type(type)
    {}

    Relation::Relation()
    : m_object_from(),
      m_object_to(),
      m_type(VoidTypeIdentifier)
    {}

    Relation::~Relation()
    {}

    /*
      We do not clone notifiable content...
    */
    Relation::Relation(const Relation& relation)
    : Notifiable(),
      m_object_from(relation.m_object_from),
      m_object_to(relation.m_object_to),
      m_type(relation.m_type)
    {}

    bool Relation::operator ==(const Relation& relation) const
    {
      return m_object_from == relation.m_object_from && m_object_to == relation.m_object_to && m_type == relation.m_type ;
    }

    bool Relation::operator <(const Relation& relation) const
    {
      return m_type < relation.m_type ||
             (m_type == relation.m_type && m_object_from < relation.m_object_from) ||
             (m_type == relation.m_type && m_object_from == relation.m_object_from && m_object_to < relation.m_object_to) ;
    }

    const TypeIdentifier& Relation::getType() const
    {
      return m_type ;
    }

    Object* Relation::getObjectFrom() const
    {
      return m_object_from ;
    }

    Object* Relation::getObjectTo() const
    {
      return m_object_to ;
    }

    std::set<Object*> Relation::_getLinked(const TypeIdentifier& relation,Object* object)
    {
      return object->getModel()->getRelations(relation,object) ;
    }

    std::set<Object*> Relation::_getLinked(Object* object)
    {
      return object->getModel()->getRelations(object) ;
    }

    std::set<Object*> Relation::_getInversedLinked(Object* object)
    {
      return object->getModel()->getInverseRelations(object) ;
    }

    bool Relation::_areLinked(const TypeIdentifier& relation,Object* object1,Object* object2)
    {
      std::set<Object*> linked = object1->getModel()->getRelations(relation,object1) ;
      return linked.find(object2) != linked.end() ;
    }

    void Relation::createLink(const TypeIdentifier& type,Object* object1,Object* object2)
    {
      Relation relation(type,object1,object2) ;
      object1->getModel()->addRelation(relation) ;

      /// @todo : see if it is useful
      if (object1->getModel() != object2->getModel())
        object2->getModel()->addRelation(relation) ;
    }

    void Relation::destroyLink(const TypeIdentifier& type,Object* object1,Object* object2)
    {
      Relation relation(type,object1,object2) ;
      if (object1)
      {
        object1->getModel()->removeRelation(relation) ;

        /// @todo : see if it is useful
        if (object1->getModel() != object2->getModel())
          object2->getModel()->removeRelation(relation) ;
      }
    }

    void Relation::createViews() const
    {
      for(std::set<ViewPoint*>::iterator viewpoint = getObjectFrom()->getModel()->m_viewpoints.begin() ;
          viewpoint != getObjectFrom()->getModel()->m_viewpoints.end() ;
          ++viewpoint)
      {
        createViews(*viewpoint) ;
      }

    }

    void Relation::createViews(ViewPoint* viewpoint) const
    {
      ViewBuilder builder = StaticStorage::get()->getViewBuilder(viewpoint,*this) ;

      if (!builder.empty())
        getObjectFrom()->getModel()->addRelationView(*this,builder(),viewpoint) ;

    }

    void Relation::registerViewBuilder(const TypeIdentifier& relation,
                                       const TypeIdentifier& viewpoint,
                                       ViewBuilder           builder)
    {
      StaticStorage::get()->m_view_builders[std::make_pair(viewpoint,relation)] = builder ;
    }

    void Relation::createControlers() const
    {
      for(std::set<ControlerSet*>::iterator controler_set = getObjectFrom()->getModel()->m_controler_sets.begin() ;
          controler_set != getObjectFrom()->getModel()->m_controler_sets.end() ;
          ++controler_set)
      {
        createControlers(*controler_set) ;
      }

    }

    void Relation::createControlers(ControlerSet* controler_set) const
    {
      ControlerBuilder builder = StaticStorage::get()->getControlerBuilder(controler_set,*this) ;

      if (!builder.empty())
        getObjectFrom()->getModel()->addRelationControler(*this,builder(),controler_set) ;

    }

    void Relation::registerControlerBuilder(const TypeIdentifier& relation,
                                            const TypeIdentifier& controler_set,
                                            ControlerBuilder      builder)
    {
      StaticStorage::get()->m_controler_builders[std::make_pair(controler_set,relation)] = builder ;
    }

    void Relation::notify()
    {
      getObjectFrom()->getModel()->update(*this) ;
      DeducedRelation::updateRelation(*this) ;
    }

    void Relation::_close()
    {
      getObjectFrom()->getModel()->close(*this) ;
    }

  }
}
