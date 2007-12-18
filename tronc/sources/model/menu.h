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
#ifndef PU_MODEL_MENU_H_
#define PU_MODEL_MENU_H_

#include <string>
#include <kernel/trait.h>
#include <kernel/reader.h>


namespace ProjetUnivers {
  namespace Model {

    /// For objects that are a menu
    class Menu : public Kernel::Trait
    {
    public:
      
      /// Construct.
      Menu(const std::string& file) ;

      /// Read a Menu trait.
      /*!
        stored as <Menu file="..."/>
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Access to layout filename.
      const std::string& getFileName() const ;
      
    private:
      
      /// Layout file.
      std::string m_file ;
    };
  }
}

#endif /*PU_MODEL_MENU_H_*/
