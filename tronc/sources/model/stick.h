/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#ifndef PU_MODEL_STICK_H_
#define PU_MODEL_STICK_H_

#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that are a stick.
    /*!
    */
    class Stick : public Oriented
    {
    public:
    
      /// Constructor.
      Stick() ;

      /// Access redefinition.
      virtual const Orientation& getOrientation() const ;

      /// Modify coordinates.
      void modifyX(const int& i_delta_x) ;
      void modifyY(const int& i_delta_y) ;
      void modifyZ(const int& i_delta_z) ;

      void setX(const int& i_x) ;
      void setY(const int& i_y) ;
      void setZ(const int& i_z) ;
    
    private:
      
      int m_x ;
      int m_y ;
      int m_z ;

      /// Update local orientation before access.
      void updateOrientation() const ;
    
      bool m_updated ;

    };
  }
}

#endif /*PU_MODEL_STICK_H_*/
