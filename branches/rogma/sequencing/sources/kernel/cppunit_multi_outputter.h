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
#ifndef CPPUNIT_MULTI_OUTPUTTER_H_
#define CPPUNIT_MULTI_OUTPUTTER_H_

#include <set>
#include <cppunit/Outputter.h>

CPPUNIT_NS_BEGIN

/// Broadcast output to multiple Outputter.
class CPPUNIT_API MultiOutputter : public CPPUNIT_NS::Outputter
{
public:
  
  /// Build
  MultiOutputter() ;

  /// Add an outputter to broadcast to.
  void add(Outputter*) ;
  
  /// Destructor.
  virtual ~MultiOutputter() ;

  virtual void write() ;

protected:
  
  std::set<Outputter*> m_outputters ;
};

CPPUNIT_NS_END

#endif /*CPPUNIT_MULTI_OUTPUTTER_H_*/
