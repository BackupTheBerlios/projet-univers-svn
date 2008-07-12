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
#include <model/menu.h>


namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(Menu) ;

    Menu::Menu(const std::string& file)
    : m_file(file)
    {}

    Kernel::Trait* Menu::read(Kernel::Reader* reader)
    {
      Menu* result = new Menu("") ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("file") ;
      if (finder != reader->getAttributes().end())
      {
        result->m_file = finder->second.c_str() ;
      }
      else
      {
        ErrorMessage("Model::Menu::read required attribute : file") ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;

      return result ;
    }
    
    const std::string& Menu::getFileName() const
    {
      return m_file ;
    }
  }
}
