/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_KERNEL_OBJECT_REFERENCE_H_
#define PU_KERNEL_OBJECT_REFERENCE_H_

namespace ProjetUnivers {
  namespace Kernel {

    class Object ;
    class Model ;
    class Reader ;
    
    /// Used to reference an object.
    /*!
      Use this instead of pointer to Object, for it checks for object 
      existence.
      
      Imagine we have an object "pointing" on another one that will be 
      destroyed latter. After that destruction, the pointer is invalid : 
      instead use an object reference, if the object is destroyed, the reference 
      equals a NULL pointer.
      
    */
    class ObjectReference
    {
    public:
      
      /// Constructor.      
      ObjectReference(Object*) ;

      /// Constructor.      
      ObjectReference() ;

      /// Destructor.
      ~ObjectReference() ;
      
      /// Copy constructor.      
      ObjectReference(const ObjectReference&) ;

      /// Read an ObjectReference.
      /*!
        stored as <Reference id=".."/>
      */          
      static ObjectReference read(Reader* reader) ;
      
      /// Assignment.
      ObjectReference& operator=(const ObjectReference&) ;

      /// Assignment.
      ObjectReference& operator=(Object*) ;
      
      /// Access to object.
      Object* operator->() ;
      
      /// Comparison
      bool operator==(const ObjectReference&) const ;
      
      /// Conversion back to object.
      operator Object*() const ;
      
      /// Is NULL.
      bool operator!() const ;
      
      /// Is not NULL.
      operator bool() const ;
      
    private:
      
      void _setModel(Model*) ;
      
      /// Model of the object
      Model* m_model ;
      
      /// OID.
      int    m_object_identifier ;
      
      friend class Model ;
      
      /// In case this reference is a temporary one : reder that is reading it.
      Reader* m_reader ;
      
      friend class Reader ;
      
    };

  }
}


#endif /*PU_KERNEL_OBJECT_REFERENCE_H_*/
