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
namespace ProjetUnivers {
  namespace Kernel {
  
    template <class T> T* Model::getControlerSet() const
    {
      for(std::set<ControlerSet*>::const_iterator 
            controlerset = m_controler_sets.begin() ;
          controlerset != m_controler_sets.end() ;
          ++controlerset)
      {
        T* temp = dynamic_cast<T*>(*controlerset) ;
        if (temp)
          return temp ;
      }
      
      return NULL ;
    }

    template <class T> T* Model::getViewPoint() const
    {
      for(std::set<ViewPoint*>::const_iterator 
            viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        T* temp = dynamic_cast<T*>(*viewpoint) ;
        if (temp)
          return temp ;
      }
      
      return NULL ;
    }
    
  }
}
