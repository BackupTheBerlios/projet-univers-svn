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
#include <kernel/error.h>
#include <kernel/exception_kernel.h>

#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/view_point.h>


namespace ProjetUnivers {
  namespace Kernel {


    ViewPoint::~ViewPoint()
    {
      close() ;
    }

    ViewPoint::ViewPoint(Model* i_model)
    : initialised(false),
      model(i_model)
    {
    }

    void ViewPoint::init()
    {
      if (! initialised)
      {
        model->_register(this) ;

        /// call local init for viewpoint
        onInit() ;
        
        initialised = true ;
        
        /// must init all the objects according to current viewpoint
        model->_init(this) ;
      }
    }

    void ViewPoint::close()
    {
      if (initialised && model)
      {
        /// must init all the objects according to current viewpoint
        model->_close(this) ;

        /// call local close for viewpoint
        onClose() ;

        model->_unregister(this) ;
        initialised = false ;
      }
    }

    void ViewPoint::onInit()
    {
    }
    void ViewPoint::onClose()
    {
    }

    void ViewPoint::onChangeObserver()
    {
    }

    bool ViewPoint::isVisible(Object* i_object) const
    {
      return true ;
    }
  }
}

