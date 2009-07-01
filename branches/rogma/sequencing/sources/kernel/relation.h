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

#include <set>
#include <kernel/object_reference.h>
#include <kernel/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    class Object ;
    class Formula ;
    template <class Relation> class Link ;
    template <class Relation> class UnLink ;
    class DeducedRelation ;
    class RelationObserver ;
    template <class _Relation,class _ViewPoint,class _View>
    class RelationViewRegistration ;
    template <class _Relation,class _ViewPoint,class _View>
    class RelationControlerRegistration ;
    class BaseRelationView ;
    class ViewPoint ;
    class BaseRelationControler ;
    class ControlerSet ;

    /// A relation 'type' between objects.
    /*!
      A relation link is destroyed when one of object is.

      Create a sub-class of Relation to define a new relation type.
      * Use
        @code
          Link<RelationType>(object1,object2) ;
        @endcode
        to link two objects
      * Use
        @code
          UnLink<RelationType>(object1,object2) ;
        @endcode
        to un-link two objects
    */
    class Relation
    {
    public:

      /// Returns the linked objects of @c object through @c _Relation.
      template <class _Relation>
      static std::set<Object*> getLinked(Object* object) ;

      /// True iff @c object1 @c _Relation @c object2.
      template <class _Relation>
      static bool areLinked(Object* object1,Object* object2) ;

      /// Access to relation type.
      const TypeIdentifier& getType() const ;

      /// Access to the starting object of the link.
      Object* getObjectFrom() const ;
      /// Access to the ending object of the link.
      Object* getObjectTo() const ;

      Relation(const Relation&) ;
      virtual ~Relation() ;
      bool operator ==(const Relation&) const ;
      bool operator <(const Relation&) const ;

      /// Returns the linked objects of @c object through @c relation.
      static std::set<Object*> _getLinked(const TypeIdentifier& relation,Object* object) ;

      /// Returns the linked objects from @c object through any relation.
      static std::set<Object*> _getLinked(Object* object) ;

      /// Returns the linked objects to @c object through any relation.
      static std::set<Object*> _getInversedLinked(Object* object) ;

      /// True iff @c object1 @c _Relation @c object2.
      static bool _areLinked(const TypeIdentifier& relation,Object* object1,Object* object2) ;

      /// Notify for a change and update all observers.
      void notify() ;

    protected:

      Relation() ;
      Relation(const TypeIdentifier&,Object*,Object*) ;

      /// Create a link.
      static void createLink(const TypeIdentifier&,Object*,Object*) ;

      /// Destroy a link.
      static void destroyLink(const TypeIdentifier&,Object*,Object*) ;

    private:

      ObjectReference m_object_from ;
      ObjectReference m_object_to ;
      TypeIdentifier  m_type ;

    /*!
      @name View Handling
    */
    //@{

      /// Type for function that build views from a relation and viewpoint.
      /*!
        @todo : simplify (no need to have the parameters anymore)
      */
      typedef
      boost::function2<BaseRelationView*,const Relation&,ViewPoint*> ViewBuilder ;

      /// create the views.
      void createViews() const ;

      /// create views for a viewpoint.
      void createViews(ViewPoint* viewpoint) const ;

      /// Register @c builder as the builder for @c relation in @c viewpoint
      /*!
        Whenever a relation is built, the corresponding relation views will be
        automatically built in each viewpoints.
      */
      static void registerViewBuilder(const TypeIdentifier& relation,
                                      const TypeIdentifier& viewpoint,
                                      ViewBuilder           builder) ;

    //@}
    /*!
      @name Controler Handling
    */
    //@{

      /// Type for function that build views from a relation and viewpoint.
      typedef
      boost::function0<BaseRelationControler*> ControlerBuilder ;

      /// create the controlers.
      void createControlers() const ;

      /// create views for a viewpoint.
      void createControlers(ControlerSet* controler_set) const ;

      /// Register @c builder as the builder for @c relation in @c controler_set
      /*!
        Whenever a relation is built, the corresponding relation controlers will
        be automatically built in each controler set.
      */
      static void registerControlerBuilder(const TypeIdentifier& relation,
                                           const TypeIdentifier& controler_set,
                                           ControlerBuilder      builder) ;

    //@}

      /// Static storage
      /*!
        Because static variable dynamic initialization occurs in an undefined
        order, we use this hook. By calling :
        <code>
          StaticStorage::get()->variable...
        </code>
        we are assured that map are dynamically initialized on demand.
      */
      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// Return the view builder.
        ViewBuilder getViewBuilder(ViewPoint*,const Relation&) ;

        /// ViewPoint X Relation --> ViewBuilder (in term of classes names)
        std::map<std::pair<TypeIdentifier,TypeIdentifier>,
                 ViewBuilder>                              m_view_builders ;

        /// Return the controler builder.
        ControlerBuilder getControlerBuilder(ControlerSet*,const Relation&) ;

        /// ViewPoint X Relation --> ViewBuilder (in term of classes names)
        std::map<std::pair<TypeIdentifier,TypeIdentifier>,
                 ControlerBuilder>                         m_controler_builders ;
      };

      template <class Relation> friend class Link ;
      template <class Relation> friend class UnLink ;
      friend class DeducedRelation ;
      friend class RelationObserver ;
      template <class _Relation,class _ViewPoint,class _View>
      friend class RelationViewRegistration ;
      template <class _Relation,class _ViewPoint,class _View>
      friend class RelationControlerRegistration ;
      friend class Model ;
    };

    /// The act of linking two objects
    /*!
      @see Relation
    */
    template <class Relation> class Link
    {
    public:

      /// Create a link between two objects.
      Link(Object*,Object*) ;
    };

    /// The act of un-linking two objects
    /*!
      @see Relation
    */
    template <class Relation> class UnLink
    {
    public:

      /// Create a link between two objects.
      UnLink(Object*,Object*) ;
    };

    /// Inverse relation of @c _Relation
    /*!
      @par Usage

      Everywhere we are expecting a relation one may use
      Inverse<R>
    */
    template <class _Relation> class Inverse : public Relation
    {};

    /// @c ClassView is the view for @c ClassRelation in @c ClassViewPoint.
    /*!
    @par Usage
    @c ClassView must inherit from
    @code
      Kernel::RelationView<ClassViewPoint>
    @endcode
    In the .cpp of a view class :
    @code
      RegisterRelationView(ClassView,ClassRelation,ClassViewPoint) ;
    @endcode

    @par Example
    @code
      RegisterRelationView( @todo ) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterRelationView(ClassView,ClassRelation,ClassViewPoint)     \
      namespace PU_MAKE_UNIQUE_NAME(register_view) {                         \
        static                                                               \
        ProjetUnivers::Kernel::BaseRelationView* build(                      \
          const ProjetUnivers::Kernel::Relation& _model,                     \
          ProjetUnivers::Kernel::ViewPoint* _viewpoint)                      \
        {                                                                    \
          ClassView* result(new ClassView()) ;                               \
          return result ;                                                    \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::RelationViewRegistration<                     \
          ClassRelation,ClassViewPoint,ClassView> temp(&build) ;             \
      }

    /// @c ClassControler is the controler for @c ClassRelation in @c ClassControlerSet.
    /*!
    @par Usage
    @c ClassControler must be declared as
    @code
      class ClassControler : public Kernel::RelationControler<ClassControlerSet>
    @endcode
    In the .cpp of a view class :
    @code
      RegisterRelationControler(ClassControler,ClassRelation,ClassControlerSet) ;
    @endcode

    @par Example
    @code
      RegisterRelationView( @todo ) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterRelationControler(ClassControler,ClassRelation,ClassControlerSet)\
      namespace PU_MAKE_UNIQUE_NAME(register_controler) {                    \
        static                                                               \
        ProjetUnivers::Kernel::BaseRelationControler* build()                \
        {                                                                    \
          return new ClassControler() ;                                      \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::RelationControlerRegistration<                \
          ClassRelation,ClassControlerSet,ClassControler> temp(&build) ;     \
      }


  }
}

#include <kernel/implementation/relation.cxx>
