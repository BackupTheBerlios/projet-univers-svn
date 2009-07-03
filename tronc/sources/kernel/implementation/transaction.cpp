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
#include <kernel/implementation/operation.h>
#include <kernel/implementation/transaction.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Implementation
    {
      Transaction::Transaction()
      {}

      void Transaction::addOperation(Operation* operation)
      {
        m_operations.push_back(operation) ;
      }
      
      void Transaction::execute()
      {
        for(std::list<Operation*>::const_iterator operation = m_operations.begin() ;
            operation != m_operations.end() ;
            ++operation)
        {
          (*operation)->execute() ;
        }
      }
      
      Transaction::~Transaction()
      {
        for(std::list<Operation*>::const_iterator operation = m_operations.begin() ;
            operation != m_operations.end() ;
            ++operation)
        {
          delete *operation ;
        }
      }
      
    }
  }
}
