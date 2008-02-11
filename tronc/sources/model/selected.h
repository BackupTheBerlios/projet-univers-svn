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
#ifndef PU_MODEL_SELECTED_H_
#define PU_MODEL_SELECTED_H_

#include <set>
#include <kernel/trait.h>
#include <kernel/object.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers {
  namespace Model {

    /// For DetectionData that are selected.
    class Selected : public Kernel::Trait
    {
    public:

    /*!
      @name Constructors
    */
    // @{

      /// Constructor.
      Selected() ;

    // @}
    /*!
      @name Access
    */
    // @{
      
      /// Tell if @c by is selecting this.
      bool isSelected(Kernel::Object* by) const ;
      
      /// Tell if element is still selected.
      bool isSelected() const ;
      
    // @}
    /*!
      @name Update
    */
    // @{
      
      /// Make this selected by @c by.
      void select(Kernel::Object* by) ;

      /// Make this un-selected by @c by.
      void unSelect(Kernel::Object* by) ;

    // @}
        
    private:
      
      /// Those who selected this.
      std::set<Kernel::ObjectReference> m_selectors ;
    
    };
  }
}

#endif /*PU_MODEL_SELECTED_H_*/
