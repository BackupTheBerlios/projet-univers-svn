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
#ifndef PU_MODEL_PHYSICAL_WORLD_H_
#define PU_MODEL_PHYSICAL_WORLD_H_

#include <kernel/deduced_trait.h>

#include <model/positionned.h>
#include <model/whole.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that are inertial reference frame.
    /*!
      @see http://en.wikipedia.org/wiki/Inertial_frame_of_reference
      
      It is a "r�f�rentiel galil�en" where physic laws are valid. 
      Any Mobile object has a speed relative to its PhysicalWorld parent.
      @see Model::Mobile.
      
    */
    class PhysicalWorld : public Kernel::DeducedTrait
    {};
  }
}

#endif /*PU_MODEL_PHYSICAL_WORLD_H_*/
