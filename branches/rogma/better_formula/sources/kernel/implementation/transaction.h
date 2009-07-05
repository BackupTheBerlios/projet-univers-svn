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
    namespace Implementation
    {
      class Operation ;
      
      /// Model transaction.
      /*!
        It is a set of operations on a model. 
        The operations are performed either locally to the transaction or 
        grouped into sub transactions that should "behave" concurrently.
      */
      class Transaction
      {
      public:
        
        Transaction() ;

        /// Add an operation to be performed locally
        void addOperation(Operation*) ;
        
        /// Perform operations
        virtual void execute() ;
        
        ~Transaction() ;
        
      private:
        
        std::list<Operation*> m_operations ;
      };
    }
  }
}
