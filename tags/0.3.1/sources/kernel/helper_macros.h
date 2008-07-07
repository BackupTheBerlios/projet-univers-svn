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
#ifndef PU_KERNEL_HELPER_MACROS_H_
#define PU_KERNEL_HELPER_MACROS_H_

/*!
  Taken from Cppunit licensed under LGPL.
*/

/// internal
#define PU_JOIN( symbol1, symbol2 ) _PU_DO_JOIN( symbol1, symbol2 )
#define _PU_DO_JOIN( symbol1, symbol2 ) _PU_DO_JOIN2( symbol1, symbol2 )
#define _PU_DO_JOIN2( symbol1, symbol2 ) symbol1##symbol2

/// Generate a "fairly" unique name.
#define PU_MAKE_UNIQUE_NAME( prefix ) PU_JOIN( prefix, __LINE__ )


#endif /*PU_KERNEL_HELPER_MACROS_H_*/
