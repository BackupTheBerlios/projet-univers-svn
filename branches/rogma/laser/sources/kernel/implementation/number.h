/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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

#include <ostream>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {
      class Number ;

      std::ostream& operator<<(std::ostream&,const Number&) ;

      /// A positive integer.
      class Number
      {
      public:

        /// Initialize to zero.
        Number(const int& = 0) ;
        /// Copy.
        Number(const Number&) ;
        /// Assignment
        Number& operator=(const Number&) ;
        /// Assignment
        Number& operator=(const unsigned int&) ;
        /// Increment
        Number& operator++() ;
        /// Assignment
        Number& operator+=(const Number&) ;

        /// Sum
        Number operator+(const Number&) const ;
        /// Sum
        Number operator+(const unsigned int&) const ;
        /// Subtract
        Number operator-(const Number&) const ;
        /// Subtract
        Number operator-(const unsigned int&) const ;

        bool operator==(const Number&) const ;
        bool operator==(const unsigned int&) const ;
        bool operator!=(const Number&) const ;
        bool operator!=(const unsigned int&) const ;
        bool operator<(const Number&) const ;
        bool operator<(const unsigned int&) const ;
        bool operator<=(const Number&) const ;
        bool operator<=(const unsigned int&) const ;
        bool operator>(const Number&) const ;
        bool operator>(const unsigned int&) const ;
        bool operator>=(const Number&) const ;
        bool operator>=(const unsigned int&) const ;

      private:

        unsigned int m_implementation ;

        friend std::ostream& operator<<(std::ostream&,const Number&) ;
      };

    }
  }
}
