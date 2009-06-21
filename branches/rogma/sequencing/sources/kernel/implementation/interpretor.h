/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    class Model ;
    
    namespace Implementation
    {
      class Transaction ;
      
      /// Model comand interpretor.
      /*!
        Executes commands on model and handle sequencement of operations.
      */
      class Interpretor
      {
      public:
        
        Interpretor(Model*) ;

        void startTransaction() ;
        void endTransaction() ;
        void startConcurrentBlock() ;
        void endConcurrentBlock() ;
        
        void destroyObject(Object*) ;
        void addTrait(Object*,Trait*) ;
        void destroyTrait(Object*,Trait*) ;
        
        Object* getParent(Object*) const ;
        Trait* getTrait(Object*,const TypeIdentifier&) const ;
        std::set<Object*> getChildren(Object*) const ;
        
      private:
        
        Model*                  m_model ;
        std::list<Transaction*> m_transactions ;
      };
    }
  }
}
