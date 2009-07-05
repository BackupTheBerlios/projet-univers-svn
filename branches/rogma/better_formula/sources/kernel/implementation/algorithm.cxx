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
namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Algorithm 
    {

      template <typename T> T findAfter(const std::set<T>& s,const T& object)      
      {
        typename std::set<T>::const_iterator up = s.upper_bound(object) ;
        
        if (up == s.end())
        {
          return *(s.begin()) ;
        }
        else
        {
          return *up ;
        }
      }

      template <typename T> T findBefore(const std::set<T>& s,const T& object)      
      {
        typename std::set<T>::const_iterator up = s.lower_bound(object) ;
        
        if (up == s.end())
        {
          return *(s.rbegin()) ;
        }
        else
        {
          if (object <= *up)
          {
            if (up == s.begin())
              return *(s.rbegin()) ;
            else
            {
              --up ;
              return *up ;
            }
          }
          return *up ;
        }
      }
      
    }
  }
}
