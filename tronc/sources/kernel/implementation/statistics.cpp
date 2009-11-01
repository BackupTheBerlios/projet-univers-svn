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
#include <algorithm>
#include <kernel/statistics.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    Statistics::Statistics()
    : m_number_of_objects(0),
      m_number_of_primitive_traits(0),
      m_number_of_deduced_traits(0),
      m_maximum_number_of_primitive_trais_per_object(0),
      m_maximum_number_of_deduced_trais_per_object(0),
      m_number_of_object_creations(0),
      m_number_of_object_destructions(0)
    {}
    
    void Statistics::updateStatistics()
    {
      if (m_number_of_objects > 0)
      {
        m_maximum_number_of_primitive_trais_per_object = std::max(m_maximum_number_of_primitive_trais_per_object,
                                                                  (float)m_number_of_primitive_traits
                                                                  /(float)m_number_of_objects) ;
        m_maximum_number_of_deduced_trais_per_object = std::max(m_maximum_number_of_deduced_trais_per_object,
                                                                (float)m_number_of_deduced_traits/(float)m_number_of_objects) ;
      }
    }
    
    float Statistics::maximumNumberOfPrimitiveTraitsPerObject() const
    {
      return m_maximum_number_of_primitive_trais_per_object ;
    }
    
    float Statistics::maximumNumberOfDeducedTraitsPerObject() const
    {
      return m_maximum_number_of_deduced_trais_per_object ;
    }
    
    void Statistics::addObject()
    {
      ++m_number_of_objects ;
      updateStatistics() ;
    }
    
    void Statistics::removeObject()
    {
      --m_number_of_objects ;
      updateStatistics() ;
    }
    
    void Statistics::addDeducedTrait()
    {
      ++m_number_of_deduced_traits ;
      updateStatistics() ;
    }
    
    void Statistics::addPrimitiveTrait()
    {
      ++m_number_of_primitive_traits ;
      updateStatistics() ;
    }
    
    void Statistics::removeDeducedTrait()
    {
      --m_number_of_deduced_traits ;
      updateStatistics() ;
    }
    
    void Statistics::removePrimitiveTrait()
    {
      --m_number_of_primitive_traits ;
      updateStatistics() ;
    }
    
  }
}
