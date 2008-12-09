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
#ifndef PU_KERNEL_READER_H_
#define PU_KERNEL_READER_H_

#include <string>
#include <map>
#include <set>


namespace ProjetUnivers {
  namespace Kernel {
    
    class Object ;
    class Model ;
    class ObjectReference ;
    
    /// Abstract class for data reading.
    class Reader
    {
    public:
      
      /// Read and fill @c model with content.
      void read(Model* model) ;
      
      /// Read a new object and put it under @c parent. 
      Object* read(Object* parent) ;
      
      /// Move to the next object child or trait node.
      /*!
        @pre we are in an object node.
        @post we are in a trait node or an child object node
      */
      bool moveToTraitOrChild(const int& depth) ;
      
      /// Return the name attribute value iff present.
      std::string getName() const ;
      
      /// Move to next node return true iff there is another.
      virtual bool processNode() = 0 ;

      /// True iff there are nodes.
      virtual bool hasNode() const = 0 ;
      
      /// Get the current node depth.
      virtual int getNodeDepth() const = 0 ;

      /// True iff current node is a model one.
      virtual bool isModelNode() const = 0 ;
      
      /// True iff current node is an object one.
      virtual bool isObjectNode() const = 0 ;
      
      /// Access to object identifier.
      virtual int getObjectIdentifier() const = 0 ;

      /// True iff current node is a trait one.
      virtual bool isTraitNode() const = 0 ;

      /// In case current node is a trait : get trait's name.
      virtual std::string getTraitName() const = 0 ; 
      
      /// True iff current node is deeper that previous.
      virtual bool isChild() const = 0 ;
      
      /// True iff the node is the beginning. 
      virtual bool isBeginNode() const = 0 ;

      /// True iff the node is the end. 
      virtual bool isEndNode() const = 0 ;
      
      /// Access to attribute values.
      virtual const std::map<std::string,std::string>& getAttributes() const = 0 ;
      
      /// Debug print
      std::string print() const ;

    private:
      
      /// Read a model.
      Object* internalReadModel(Model* model,Object* parent) ;
      
      /// Read an object.
      /*!
        @pre isObjectNode() 
        @post on the node following the read object
      */
      Object* readObject(Model* model,Object* parent) ;
    
      /// Mapping between id used in the reading source to the real object ids. 
      std::map<int,int> m_local_id_to_real_id ;
      
      /// References to be resolved.
      std::set<ObjectReference*> m_references ;
      
      /// ??
      int m_current_object_depth ;
      
      /// Register a reference for further resolution.
      void _registerReference(ObjectReference*) ;
      
      /// Unregister a reference from further resolution.
      void _unregisterReference(ObjectReference*) ;
      
      friend class ObjectReference ;
      
    };


  }
}

#endif /*PU_KERNEL_READER_H_*/
