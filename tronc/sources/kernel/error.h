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
#ifndef PU_KERNEL_ERROR_H_
#define PU_KERNEL_ERROR_H_

#include <cassert>
#include <kernel/log.h>
/*!
  @name Error handling
  
  Compile time choosing between assertion and exception.  
  
*/


/// Raise an error/exception if @c condition is false.
/*!
  @param condition a boolean expression 
  @param message a string 
*/
#ifdef _DEBUG
  
  #define CHECK(condition,message) assert((condition)) ;

#else

  #define CHECK(condition,message) { if (!(condition)) { ErrorMessage(message) ; throw message ; } }

#endif




#endif /*PU_KERNEL_ERROR_H_*/
