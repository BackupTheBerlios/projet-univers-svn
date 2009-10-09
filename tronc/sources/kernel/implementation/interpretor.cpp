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
#include <iostream>
#include <kernel/log.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/implementation/operation.h>
#include <kernel/implementation/interpretor.h>
#include <kernel/timer.h>
#include <kernel/implementation/profiler.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {
      Interpretor::Interpretor()
      : m_destroying(false),
        m_number_of_openned_transaction(0),
        m_is_finishing(false),
        m_destroying_traits(false)
      {}

      void Interpretor::startTransaction()
      {
        ++m_number_of_openned_transaction ;
      }

      Interpretor::~Interpretor()
      {}

      void Interpretor::addOperation(const Implementation::Operation& operation)
      {
        /// @todo investigate Model gpf without || m_is_finishing
        if ((m_number_of_openned_transaction > 0 || m_is_finishing) && ! m_destroying)
          m_operations.push_back(operation) ;
        else
          operation.execute() ;
      }

      void Interpretor::destroyTraits()
      {
        Profiler::startBlock("Kernel::Interpreter::destroyTraits()") ;
        m_destroying_traits = true ;
        for(std::set<Trait*>::iterator trait = m_traits_to_destroy.begin() ; trait != m_traits_to_destroy.end() ; ++trait)
        {
          (*trait)->getObject()->_detach(getObjectTypeIdentifier(*trait)) ;
          delete *trait ;
        }
        m_traits_to_destroy.clear() ;
        m_destroying_traits = false ;
        Profiler::endBlock("Kernel::Interpreter::destroyTraits()") ;
      }

      void Interpretor::destroyObjects()
      {
        Profiler::startBlock("Kernel::Interpreter::destroyObjects()") ;
        for(std::list<ObjectReference>::const_iterator object = m_objects_to_destroy.begin() ; object != m_objects_to_destroy.end() ; ++object)
        {
          if (*object)
          {
            if ((*object)->isLocked())
            {
              ErrorMessage("Interpretor::endTransaction Destroying a lock object") ;
            }

            Model* model = (*object)->getModel() ;

            if ((*object)->getParent() == NULL)
            {
              /// a top object
              model->m_objects.erase(*object) ;
              delete *object ;
            }
            else
            {
              /// a sub object
              (*object)->getParent()->_remove(*object) ;
            }
          }
        }
        m_objects_to_destroy.clear() ;
        Profiler::endBlock("Kernel::Interpreter::destroyObjects()") ;
      }

      void Interpretor::destroyRelations()
      {
        Profiler::startBlock("Kernel::Interpreter::destroyRelations()") ;
        for(std::set<Relation>::iterator relation = m_relation_to_destroy.begin() ; relation != m_relation_to_destroy.end() ; ++relation)
        {
          Model* model_from = relation->getObjectFrom()?relation->getObjectFrom()->getModel():NULL ;
          Model* model_to = relation->getObjectFrom()?relation->getObjectFrom()->getModel():NULL ;
          if (model_from == this)
            model_from->_internalDestroyRelation(*relation) ;
          else if (model_to == this)
            model_to->_internalDestroyRelation(*relation) ;
        }

        m_relation_to_destroy.clear() ;
        Profiler::endBlock("Kernel::Interpreter::destroyRelations()") ;
      }

      void Interpretor::endTransaction()
      {
        --m_number_of_openned_transaction ;
        if (0 == m_number_of_openned_transaction && ! m_is_finishing)
        {
          m_is_finishing = true ;
          m_performed_operations.clear() ;

          while (!m_operations.empty() ||
                 !m_traits_to_destroy.empty() ||
                 !m_objects_to_destroy.empty() ||
                 !m_relation_to_destroy.empty())
          {
            while (!m_operations.empty())
            {
              Operation operation(m_operations.front()) ;
              m_performed_operations.push_back(operation) ;
              m_operations.pop_front() ;

              Profiler::startBlock(operation.userMethodName()) ;
              operation.execute() ;
              Profiler::endBlock() ;
            }

            destroyTraits() ;

            if (!m_operations.empty())
              ErrorMessage("Interpretor::endTransaction Remaining operations after trait destroy") ;

            destroyRelations() ;

            destroyObjects() ;

            m_performed_operations.clear() ;

            for(std::list<Operation>::iterator operation = m_operations.begin() ; operation != m_operations.end() ; ++operation)
            {
              ErrorMessage("After object destroy remains " + operation->toString()) ;
            }
          }
          m_is_finishing = false ;

          if (!m_operations.empty())
            ErrorMessage("Interpretor::endTransaction Finishing with operations") ;
        }
      }

      void Interpretor::recordTraitToDestroy(Trait* trait)
      {
        if (!m_destroying_traits)
          m_traits_to_destroy.insert(trait) ;
        else
          throw Exception("recordTraitToDestroy while destroying traits") ;
      }

      void Interpretor::removeTraitToDestroy(Object* object,const TypeIdentifier& type)
      {
        if (!m_destroying_traits)
        {
          Trait* undestroy_trait = NULL ;

          for(std::set<Trait*>::iterator trait = m_traits_to_destroy.begin() ; trait != m_traits_to_destroy.end() ; ++trait)
          {
            if ((*trait)->getObject() == object && getObjectTypeIdentifier(*trait) == type)
            {
              undestroy_trait = *trait ;
            }
          }

          if (undestroy_trait)
            m_traits_to_destroy.erase(undestroy_trait) ;
        }
        else
          throw Exception("recordTraitToDestroy while destroying traits") ;
      }

      bool Interpretor::isToBeDestroyed(Trait* trait) const
      {
        return m_traits_to_destroy.find(trait) != m_traits_to_destroy.end() ;
      }

      void Interpretor::addObjectToDestroy(Object* object)
      {
        if (! m_destroying)
          m_objects_to_destroy.push_back(object) ;
      }
      void Interpretor::recordRelationToDestroy(const Relation& relation)
      {
        m_relation_to_destroy.insert(relation) ;
      }

      bool Interpretor::isToDestroy(const Relation& relation) const
      {
        return m_relation_to_destroy.find(relation) != m_relation_to_destroy.end() ;
      }

      void Interpretor::unRecordRelationToDestroy(const Relation& relation)
      {
        m_relation_to_destroy.erase(relation) ;
      }

      std::string Interpretor::toString(const char* module) const
      {
        std::string result("[Performed] :") ;

        for(std::list<Operation>::const_iterator operation = m_performed_operations.begin() ; operation != m_performed_operations.end() ; ++operation)
        {
          std::string operation_string(operation->toString()) ;
          if (operation_string.find(module) != std::string::npos)
            result = result + operation_string + "," ;
        }

        result += "  [Remaining]  " ;
        for(std::list<Operation>::const_iterator operation = m_operations.begin() ; operation != m_operations.end() ; ++operation)
        {
          std::string operation_string(operation->toString()) ;
          if (operation_string.find(module) != std::string::npos)
            result = result + operation_string + "," ;
        }

        return result ;
      }


    }
  }
}
