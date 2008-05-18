/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_MODEL_DETECTION_DATA_H_
#define PU_MODEL_DETECTION_DATA_H_

#include <model/computer_data.h>

namespace ProjetUnivers {
  namespace Model {
      
    /// Represents detection information on objects.
    /*!
      Detection data are generally also Positionned, in that case, the position 
      is in the local space of the Computer holding the data. 
    */
    class DetectionData : public ComputerData
    {
    public:

      /// Constructs.
      DetectionData(Kernel::Object* computer) ;
    };
  }
}

#endif /*PU_MODEL_DETECTION_DATA_H_*/
