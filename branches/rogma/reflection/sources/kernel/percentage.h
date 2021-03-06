/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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

    /// Class representing a percentage positive or negative.
    class Percentage
    {
    public:

      /// Construction.
      Percentage() ;
      
      /// Construct from a integer.
      Percentage(const int&) ;
      
      /// Construct from a integer.
      Percentage& operator=(const int&) ;
      
      /// Construct from a float.
      Percentage(const float&) ;
    
      /// Construct from a float.
      Percentage& operator=(const float&) ;

      /// Addition.
      Percentage& operator+=(const Percentage&) ;

      /// Addition.
      Percentage operator+(const Percentage&) ;
      
      /// Conversion to int value in [-100,100].
      operator int() const ;

      /// Conversion to float value in [-1,1].
      operator float() const ;
      
      /// Comparison.
      bool operator==(const Percentage&) const ;

      /// Comparison.
      bool operator==(const int&) const ;

      /// Comparison.
      bool operator==(const float&) const ;

      /// Comparison.
      bool operator!=(const Percentage&) const ;

      /// Comparison.
      bool operator!=(const int&) const ;

      /// Comparison.
      bool operator!=(const float&) const ;
      
    private:  
    
      float m_value ;
    };
  }
}
