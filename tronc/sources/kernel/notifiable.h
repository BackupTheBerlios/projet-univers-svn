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
#include <string>

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
    class ViewPoint ;
    class ControlerSet ;

    /// Something observed that can be notified.
    /*!
    The observable in a Observer pattern.
    */
    class Notifiable
    {
    public:

      /// Notify it's observers that it has changed.
      virtual void notify() = 0 ;

      /// Close all the observers
      virtual void _close() = 0 ;

      /// Close the views.
      virtual void _close(ViewPoint* viewpoint) = 0 ;

      /// Close the controllers before controller set closing.
      virtual void _close(ControlerSet* controler_set) = 0 ;

      virtual void addReverseDependency(Notifiable*) ;
      virtual void removeReverseDependency(Notifiable*) ;

      void resetUpdatedStatus() ;

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

      /// Return a printable description
      virtual std::string toString() const = 0 ;

      /// Return the graphviz name.
      virtual std::string graphvizName() const = 0 ;

      /// Give the total number of observers updated by this.
      int getNumberOfImpactedObservers() const ;

    protected:

      /// True if this has view or controller.
      virtual bool hasObserver() const = 0 ;

      Notifiable() ;

      /// Propagate update on dependent traits.
      void updateDependents() ;

      /// Propagate close on dependent notifiable.
      void closeDependents() const ;

      /// Propagate close on dependent notifiable.
      void closeDependents(ViewPoint* viewpoint) const ;

      /// Propagate close on dependent notifiable.
      void closeDependents(ControlerSet* controler_set) const ;

      /// Indicate that an observer has been added.
      void onAddObserver() ;
      void onRemoveObserver() ;

    private:

      /// Indicate that observers has been added.
      void onAddObservers(const int&) ;

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

      /// True when already updated this round
      bool m_updated_this_round ;

      /// Number of observers to update.
      int m_number_of_impacted_observers ;

      friend class FormulaOr ;
      friend class IsRelatedFormula ;
      friend class IsOnlyRelatedFormula ;
      friend class DeducedTrait ;
      friend class DeducedRelation ;
      friend class Formula ;
    };
  }
}
