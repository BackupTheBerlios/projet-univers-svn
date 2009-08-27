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

namespace ProjetUnivers
{
  namespace Kernel
  {

    class HasParentFormula ;
    class HasAncestorFormula ;
    class HasChildFormula ;
    class FormulaOr ;
    class IsRelatedFormula ;
    class IsOnlyRelatedFormula ;
    class DeducedTrait ;
    class DeducedRelation ;
    class Formula ;

    /// Something observed that can be notified.
    class Notifiable
    {
    public:

      /// Notify it's observers that it has changed.
      virtual void notify() = 0 ;

      virtual void _close() = 0 ;

      virtual void addReverseDependency(Notifiable*) ;
      virtual void removeReverseDependency(Notifiable*) ;


      /// Access to direct dependent notifiables.
      /*!
        Gives the traits/relations to update if we update @c this (non recursive).

        This value is stored and maintained during structure changes. So access
        if fast at cost of structural changes and memory.

        In case of DeducedTrait, this value is equivalent to
        getDependentNotifiables(@c this) on the formula defining the deduced trait.
      */
      const std::set<Notifiable*>& getDependentNotifiables() const ;

      /// The notifiables on with @c this depends.
      /*!
        These are the traits/relations that trigger update for @c this.
      */
      const std::set<Notifiable*>& getDependencies() const ;

      /// Transitive dependency.
      bool dependsOn(const Notifiable*) const ;

      virtual ~Notifiable() ;

      /// Return the graphviz name.
      virtual std::string graphvizName() const = 0 ;

    protected:

      Notifiable() ;

      /// Propagate update on dependent traits.
      void updateDependents() const ;

      /// Propagate close on dependent notifiable.
      void closeDependents() const ;

    private:

      /// Add a dependent trait.
      void addDependency(Notifiable*) ;
      /// Remove a dependent trait.
      void removeDependency(Notifiable*) ;
      /// Remove a dependent trait.
      void _removeDependency(Notifiable*) ;

      /// Notifiables that directly depends on @c this
      std::set<Notifiable*> m_direct_dependent_notifiables ;

      /// Inverse of m_direct_dependent_notifiables
      std::set<Notifiable*> m_reverse_dependencies ;

      friend class FormulaOr ;
      friend class IsRelatedFormula ;
      friend class IsOnlyRelatedFormula ;
      friend class DeducedTrait ;
      friend class DeducedRelation ;
      friend class Formula ;
    };
  }
}
