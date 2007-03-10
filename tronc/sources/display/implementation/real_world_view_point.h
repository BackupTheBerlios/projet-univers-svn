/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#ifndef PU_DISPLAY_VIEW_POINT_H_
#define PU_DISPLAY_VIEW_POINT_H_

#include <kernel/view_point.h>


namespace ProjetUnivers {

  namespace Kernel { 
    class Object ;
  }

  namespace Display {
    namespace Implementation {
        
      /// ViewPoint on the real world.
      /*!
      */
      class RealWorldViewPoint : public Kernel::ViewPoint 
      {
      public:
  
        /// Abstractclass means virtual destructor..
        virtual ~RealWorldViewPoint() ;
  
        /// La vue de l'observateur.
        Kernel::Object* getObserverView() const ;
        
        /// Make this as the displayed viewpoint. 
        virtual void activate() = 0 ;
        
      protected:
        
        /// protected constructor
        RealWorldViewPoint(Kernel::Object* i_observer) ;
  
        Kernel::Object* observer ;
      };

    }            
  }
}


#endif
