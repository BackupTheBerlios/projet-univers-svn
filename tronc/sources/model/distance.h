/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_DISTANCE_H_
#define PU_MODEL_DISTANCE_H_

#include <ostream>

#include <kernel/reader.h>

namespace ProjetUnivers {
  namespace Model {

    namespace Test
    {
      class TestDistance ;
    }
    
    class Position ;
      
    /// A distance between 2 points.
    /*!  
    */
    class Distance 
    {
    public:
    
    // ********************
    /// @name Constructs
    // ********************
    // @{   
    
      /// Measure units.
      typedef enum {
        _Meter,
        _LightYear, 
        _Parsec 

      } Unit ;

      /// Null distance.
      Distance() ;
      
      /// Copy constructor.
      Distance(const Distance&) ;

      /// Constructor with unit and value.
      Distance(const Unit&, const float&) ;
    
      /// Calculus
      Distance operator +(const Distance&) const ;

      /// Calculus
      Distance operator -(const Distance&) const ;

      /// Read a distance.
      /*!
        stored as 
        @code
          <Distance value=".." unit="Meter|LightYear|Parsec"/>
        @endcode
      */          
      static Distance read(Kernel::Reader* reader) ;

      
    // @}
    // ******************
    /// @name Conversions
    // ******************
    // @{
      

      /// Convert to parsecs.
      float Parsec() const ; 
      
      /// Convert to meters.
      float Meter() const ; 
      
      /// Convert to light years.
      float LightYear() const ; 

    
    // @}    
    // ************
    /// @name Access
    // ************
    // @{
      
      /// Print operator.
      friend std::ostream& operator<<(std::ostream&,const Unit&) ;
    
      /// Comparison.
      bool operator <=(const Distance&) const ;
    
    // @}
      
    private:
    

      /// value.
      float m_value ;
  
      /// Unit of m_value.
      Unit  m_unit ;    

      /// Internal unit conversions.
      static float convert(float i_value,
                           Unit  i_from,
                           Unit  i_to) ;
      
      /// Choose the best unit from i_unit1 and i_unit2.
      static Unit bestCompatibleUnit(Unit  i_unit1,
                                     Unit  i_unit2) ;
      
      /// Unit comparison; test purpose.
      friend bool operator<=(Distance::Unit, Distance::Unit) ;

                            
      friend class ::ProjetUnivers::Model::Test::TestDistance ;
      friend class ::ProjetUnivers::Model::Position ;
    };

    bool operator<=(Distance::Unit,Distance::Unit) ;


  }
}




#endif
