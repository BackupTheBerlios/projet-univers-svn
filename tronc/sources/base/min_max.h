/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#ifdef __GNUG__
#pragma interface
#endif

#ifndef MIN_MAX_H_
#define MIN_MAX_H_


namespace ProjetUnivers {

  namespace Base {

    //////////////////////
    // Donne le minimum de _v1 et _v2
    template <class T> inline T Minimum(T _v1, T _v2) 
    
    {
        return _v1 < _v2 ? _v1 : _v2;
    }
    
    //////////////////////
    // Donne le maximum de _v1 et _v2    
    template <class T> inline T Maximum(T _v1, T _v2) 
    
    {
        return _v1 > _v2 ? _v1 : _v2;
    }
  }
}
#endif
