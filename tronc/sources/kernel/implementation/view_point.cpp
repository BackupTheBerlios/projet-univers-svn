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
#include <kernel/error.h>
#include <kernel/exception_kernel.h>
#include <kernel/log.h>

#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/view_point.h>


namespace ProjetUnivers {
  namespace Kernel {


    ViewPoint::~ViewPoint()
    {
      InternalMessage("Kernel","ViewPoint::~ViewPoint destroying") ;
      close() ;
      InternalMessage("Kernel","ViewPoint::~ViewPoint destroyed") ;
    }

    ViewPoint::ViewPoint(Model* model)
    : m_initialised(false),
      m_model_attached(model),
      m_model(model)
    {}

    void ViewPoint::init()
    {
      if (! m_initialised)
      {
        if (m_model)
        {
          m_model->_register(this) ;
        }

        /// call local init for viewpoint
        onInit() ;
        
        m_initialised = true ;
        
        /// must init all the objects according to current viewpoint
        if (m_model)
        {
          m_model->_init(this) ;
        }
      }
    }

    void ViewPoint::close()
    {
      InternalMessage("Kernel","ViewPoint::close Entering") ;
      if (m_initialised && m_model)
      {
        /// must close all the objects according to current viewpoint
        m_model->_close(this) ;

        InternalMessage("Kernel","ViewPoint::close #1") ;
        /// call local close for viewpoint
        onClose() ;

        InternalMessage("Kernel","ViewPoint::close #2") ;

        m_model->_unregister(this) ;
        m_model = NULL ;
        m_model_attached = false ;
        m_initialised = false ;
      }
      InternalMessage("Kernel","ViewPoint::close Leaving") ;
    }
    
    void ViewPoint::setModel(Model* model)
    {
      InternalMessage("Kernel","ViewPoint::setModel Entering") ;
      if (m_initialised && m_model)
      {
        /// must close all the objects according to current viewpoint
        m_model->_close(this) ;
        m_model->_unregister(this) ;
      }
      
      m_model = model ;
      
      if (m_model)
      {
        m_model->_register(this) ;
        m_model->_init(this) ;
        m_model_attached = true ;
      }
      InternalMessage("Kernel","ViewPoint::setModel Entering") ;
    }
    
    Model* ViewPoint::getModel() const
    {
      return m_model ;
    }
        
    bool ViewPoint::isInitialised() const
    {
      return m_initialised ;
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

