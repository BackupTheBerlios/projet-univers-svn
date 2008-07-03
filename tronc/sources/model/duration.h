/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_DURATION_H_
#define PU_MODEL_DURATION_H_

#include <kernel/reader.h>

namespace ProjetUnivers {
  namespace Model {
      
    /// A time duration.
    /*!  
    */
    class Duration 
    {
    public:
    
    /*! 
      @name Constructors
    */
    // @{   
    

      /// Zero duration.
      Duration() ;
      
      /// Build a duration in seconds.
      static Duration Second(float i_seconds) ;
      
      /// Copy constructor.
      Duration(const Duration&) ;
    
      /// Addition
      Duration operator +(const Duration&) const ;

      /// Substraction
      Duration operator -(const Duration&) const ;

      /// Assignment.
      Duration& operator=(const Duration&) ;

      /// Read duration.
      /*!
        stored as 
        @code
          <Duration value=".." unit="Second"/>
        @endcode
      */          
      static Duration read(Kernel::Reader* reader) ;
      
    // @}
    /*! 
      @name Convertions
    */
    // @{

      /// Duration in seconds.
      float Second() const ; 
    
    // @}
      
    private:
    
      /// Units
      typedef enum {
        _Second
      } Unit ;
      
      /// Private constructor.
      Duration(Unit i_unit,float i_value) ;

      float m_value ;
      Unit  m_unit ;    
  
    };

  }
}

#endif
