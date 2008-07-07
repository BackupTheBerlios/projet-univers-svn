/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <iostream>
#include <OIS/OIS.h>
#include <kernel/timer.h>
#include <display/display_input.h>
#include <display/implementation/ogre/ogre.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/input_object.h>

using namespace ProjetUnivers ;


void displayAxes(const std::map<Model::PlayerConfiguration::InputAxis,
                                Kernel::Percentage>& axes)
{
  int number = 0 ;
  for(std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage>::const_iterator axis = axes.begin() ;
      axis != axes.end() ;
      ++axis,++number)
  {
    std::cout << "axis" << number << "=" << int(axis->second) ;
  }
  
  std::cout << std::endl ;
}

int main( int argc, char* argv[] )
{
  Display::Implementation::Ogre::init(false) ;
  Input::init() ;
  
  Kernel::Timer global_timer ;
  Kernel::Timer timer ;
  
  while(global_timer.getSecond() < 10)
  {
    Input::update() ;
    if (timer.getSecond() > 0.2)
    {
      if (Input::getJoystick())
        displayAxes(Input::getJoystick()->getAxes()) ;
      timer.reset() ;
    }
  }

  Input::close() ;
  
  return 0 ;
}


