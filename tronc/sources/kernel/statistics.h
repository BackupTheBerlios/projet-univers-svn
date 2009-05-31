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
#pragma once

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    /// Hold the statistics of a model.
    class Statistics
    {
    public:

      Statistics() ;
      
      /// Access to stats
      float maximumNumberOfPrimitiveTraitsPerObject() const ;
      float maximumNumberOfDeducedTraitsPerObject() const ;
      
      void addObject() ;
      void removeObject() ;

      void addDeducedTrait() ;
      void addPrimitiveTrait() ;
      void removeDeducedTrait() ;
      void removePrimitiveTrait() ;
      
    private:
      
      void updateStatistics() ;
      
      int m_number_of_objects ;
      int m_number_of_primitive_traits ;
      int m_number_of_deduced_traits ;
      
      float m_maximum_number_of_primitive_trais_per_object ;
      float m_maximum_number_of_deduced_trais_per_object ;
      
      int m_number_of_object_creations ;
      int m_number_of_object_destructions ;
    };
  }
}
