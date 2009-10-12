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
#include <kernel/string.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/observer.h>
#include <kernel/relation_observer.h>
#include <kernel/implementation/operation.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      Operation::Operation(const Operation& operation)
      : m_type(operation.m_type),
        m_object(operation.m_object),
        m_observer(operation.m_observer),
        m_old_parent(operation.m_old_parent),
        m_relation_observer(operation.m_relation_observer),
        m_updated_trait(operation.m_updated_trait),
        m_debug_display(operation.m_debug_display),
        m_user_method_name(operation.m_user_method_name)
      {}

      Operation::Operation()
      : m_type(None),
        m_object(),
        m_observer(NULL),
        m_old_parent(NULL),
        m_relation_observer(NULL)
      {}

      Operation Operation::init(Observer* observer)
      {
        Operation result ;
        result.m_type = Init ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        std::string class_name(getObjectTypeIdentifier(result.m_observer).fullName()) ;
        result.m_debug_display = "Init(" + Kernel::toString(result.m_object->getIdentifier()) + "," + class_name +")" ;
        result.m_user_method_name = class_name + "::onInit()" ;
        return result ;
      }

      Operation Operation::close(Observer* observer)
      {
        Operation result ;
        result.m_type = Close ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        std::string class_name(getObjectTypeIdentifier(result.m_observer).fullName()) ;
        result.m_debug_display = "Close(" + Kernel::toString(result.m_object->getIdentifier()) + "," + class_name +")" ;
        result.m_user_method_name = class_name + "::onClose()" ;
        return result ;
      }

      Operation Operation::update(Observer* observer)
      {
        Operation result ;
        result.m_type = Update ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        result.m_updated_trait = Trait::getLatestUpdatedTrait() ;
        std::string class_name(getObjectTypeIdentifier(result.m_observer).fullName()) ;
        result.m_debug_display = "Update(" + Kernel::toString(result.m_object->getIdentifier()) + "," + class_name +")" ;
        result.m_user_method_name = class_name + "::onUpdate()" ;
        return result ;
      }

      Operation Operation::changeParent(Observer* observer,Object* old_parent)
      {
        Operation result ;
        result.m_type = ChangeParent ;
        result.m_object = observer->getObject() ;
        result.m_observer = observer ;
        result.m_old_parent = old_parent ;
        result.m_debug_display = "ChangeParent(" + Kernel::toString(result.m_object->getIdentifier()) +
                                 "," + getObjectTypeIdentifier(result.m_observer).fullName() +
                                  Kernel::toString(result.m_old_parent?result.m_old_parent->getIdentifier():-1) + ")" ;
        return result ;
      }

      Operation Operation::init(RelationObserver* observer)
      {
        Operation result ;
        result.m_type = InitRelation ;
        result.m_relation_observer = observer ;
        std::string class_name(getObjectTypeIdentifier(result.m_relation_observer).fullName()) ;
        result.m_debug_display = "InitRelation(" + class_name +
                                 "," + Kernel::toString(observer->getObjectFrom()->getIdentifier()) + "," +
                                 Kernel::toString(observer->getObjectTo()->getIdentifier()) + ")" ;
        result.m_user_method_name = class_name + "::onInit()" ;
        return result ;
      }

      Operation Operation::close(RelationObserver* observer)
      {
        Operation result ;
        result.m_type = CloseRelation ;
        result.m_relation_observer = observer ;
        std::string class_name(getObjectTypeIdentifier(result.m_relation_observer).fullName()) ;
        result.m_debug_display = "CloseRelation(" + class_name +
                                 "," + Kernel::toString(observer->getObjectFrom()->getIdentifier()) + "," +
                                 Kernel::toString(observer->getObjectTo()->getIdentifier()) + ")" ;
        result.m_user_method_name = class_name + "::onClose()" ;
        return result ;
      }

      Operation Operation::update(RelationObserver* observer)
      {
        Operation result ;
        result.m_type = UpdateRelation ;
        result.m_relation_observer = observer ;
        result.m_updated_trait = Trait::getLatestUpdatedTrait() ;
        std::string class_name(getObjectTypeIdentifier(result.m_relation_observer).fullName()) ;
        result.m_debug_display = "UpdateRelation(" + class_name +
                                 "," + Kernel::toString(observer->getObjectFrom()->getIdentifier()) + "," +
                                 Kernel::toString(observer->getObjectTo()->getIdentifier()) + ")" ;
        result.m_user_method_name = class_name + "::onUpdate()" ;
        return result ;
      }

      void Operation::execute() const
      {
        switch(m_type)
        {
        case Init:
          m_observer->realInit() ;
          break ;
        case Close:
          m_observer->realClose() ;
          break ;
        case Update:
          m_observer->m_latest_updated_trait = m_updated_trait ;
          m_observer->realUpdate() ;
          m_observer->m_latest_updated_trait = TypeIdentifier() ;
          break ;
        case ChangeParent:
          m_observer->realChangeParent(m_old_parent) ;
          break ;
        case InitRelation:
          m_relation_observer->realInit() ;
          break ;
        case CloseRelation:
          m_relation_observer->realClose() ;
          break ;
        case UpdateRelation:
          m_relation_observer->m_latest_updated_trait = m_updated_trait ;
          m_relation_observer->realUpdate() ;
          m_relation_observer->m_latest_updated_trait = TypeIdentifier() ;
          break ;
        case None:
          break ;
        }
      }

      std::string Operation::toString() const
      {
        return m_debug_display ;
      }

      std::string Operation::userMethodName() const
      {
        return m_user_method_name ;
      }
    }
  }
}
