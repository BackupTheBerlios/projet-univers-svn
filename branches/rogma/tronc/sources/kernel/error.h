/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef _PU_KERNEL_ERROR_H_
#define _PU_KERNEL_ERROR_H_

#include <cassert>

/*!
  @name Gestion des erreurs
  
  Ce syst�me permet de changer � la compilation entre une assertion et une 
  exception.
  
  
  
*/


/// D�clenche une erreur/exception si @c condition est faux
/*!
  @param condition une expression renvoyant un booleen
  @param exception une exception
*/
#ifdef _DEBUG
  
  #define check(condition, exception) assert((condition)) ;

#else

  #define check(condition, exception) { if (!(condition)) throw exception ; }

#endif




#endif /*_PU_KERNEL_ERROR_H_*/
