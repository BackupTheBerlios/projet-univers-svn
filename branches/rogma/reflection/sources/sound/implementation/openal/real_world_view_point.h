/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD                               *
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

#include <kernel/object.h>
#include <kernel/view_point.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        /// Standard sound viewpoint.
        class RealWorldViewPoint : public Kernel::ViewPoint 
        {
        public:
        /*!
          @name Construction 
        */
        // @{
          
          /// Constructor.
          RealWorldViewPoint(Kernel::Model* model) ;

          void setListener(Kernel::Object*) ;

        // @}

          /// Get the current listener.
          Kernel::Object* getListener() const ;

        protected:
        
          virtual void onInit() ;
          
          virtual void update(const float&) ;
        
        private:

          Kernel::ObjectReference m_listener ;
        };
      }
    }
  }
}
