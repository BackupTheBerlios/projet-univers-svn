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
#include <exception>
#include <kernel/implementation/number.h>
#include <kernel/exception_kernel.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      Number::Number(const int& number)
      : m_implementation(number)
      {}

      Number::Number(const Number& number)
      : m_implementation(number.m_implementation)
      {}

      Number& Number::operator=(const Number& number)
      {
        if (this != &number)
          m_implementation = number.m_implementation ;
        return *this ;
      }

      Number& Number::operator=(const unsigned int& number)
      {
        m_implementation = number ;
        return *this ;
      }

      Number& Number::operator++()
      {
        ++m_implementation ;
        return *this ;
      }

      Number& Number::operator+=(const Number& number)
      {
        m_implementation += number.m_implementation ;
        return *this ;
      }

      Number Number::operator+(const Number& number) const
      {
        Number result(*this) ;
        result.m_implementation += number.m_implementation ;
        return result ;
      }

      Number Number::operator+(const unsigned int& number) const
      {
        Number result(*this) ;
        result.m_implementation += number ;
        return result ;
      }

      Number Number::operator-(const Number& number) const
      {
        Number result(*this) ;
        result.m_implementation -= number.m_implementation ;
        return result ;
      }

      Number Number::operator-(const unsigned int& number) const
      {
        Number result(*this) ;
        result.m_implementation -= number ;
        return result ;
      }

      bool Number::operator==(const Number& number) const
      {
        return m_implementation == number.m_implementation ;
      }

      bool Number::operator==(const unsigned int& number) const
      {
        return m_implementation == number ;
      }
      bool Number::operator!=(const Number& number) const
      {
        return m_implementation != number.m_implementation ;
      }
      bool Number::operator!=(const unsigned int& number) const
      {
        return m_implementation != number ;
      }
      bool Number::operator<(const Number& number) const
      {
        return m_implementation < number.m_implementation ;
      }
      bool Number::operator<(const unsigned int& number) const
      {
        return m_implementation < number ;
      }
      bool Number::operator<=(const Number& number) const
      {
        return m_implementation <= number.m_implementation ;
      }
      bool Number::operator<=(const unsigned int& number) const
      {
        return m_implementation <= number ;
      }
      bool Number::operator>(const Number& number) const
      {
        return m_implementation > number.m_implementation ;
      }
      bool Number::operator>(const unsigned int& number) const
      {
        return m_implementation > number ;
      }
      bool Number::operator>=(const Number& number) const
      {
        return m_implementation >= number.m_implementation ;
      }
      bool Number::operator>=(const unsigned int& number) const
      {
        return m_implementation >= number ;
      }

      std::ostream& operator<<(std::ostream& out,const Number& number)
      {
        out << number.m_implementation ;
        return out ;
      }

    }
  }
}
