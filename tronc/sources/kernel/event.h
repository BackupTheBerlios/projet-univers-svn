/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef PU_KERNEL_EVENT_H_
#define PU_KERNEL_EVENT_H_

#include <string>


namespace ProjetUnivers {
  namespace Kernel {

    class Model ;

    /// Update on Model event.
    /*!
    */
    struct Event
    {
      /// Kinds of update
      typedef enum
      {
        /// Mono-valued attribute modification.
        Update,
        /// Multi-valued attribute insert.
        Add,
        /// Multi-valued attribute remove.
        Remove,
        /// Object deleted.
        Delete,
        /// Object created.
        New,
        /// Default value.
        Undefined

      } Action ;
      
      /// Default constructor.
      Event() ;
      
      /// 
      Event(const Action&, const std::string& , Model*) ;
      
      
      /// Copy constructor.
      Event(const Event&) ;
      
      /// Comparison operator.
      bool operator==(const Event&) const ;
      
      
      /// Action 
      Action action ;
      
      /// Modified attribute.
      std::string name ;
      
      /// Object modified.
      /*!
        ObjectId ??? mainly because of destruction.
      */
      Model* parameter ;

    };
  }
}

#endif /*PU_KERNEL_EVENT_H_*/
