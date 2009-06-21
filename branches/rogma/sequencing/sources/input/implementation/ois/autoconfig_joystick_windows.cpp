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
#include <windows.h>
#include <dinput.h>


IDirectInput8* direct_input ;
IDirectInputDevice8* joystick ;
unsigned int axis_number = 0 ;

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,
                                    VOID* pContext)
{
  HRESULT hr;

  // Obtain an interface to the enumerated joystick.
  hr = direct_input->CreateDevice(pdidInstance->guidInstance,&joystick,NULL) ;

  // If it failed, then we can't use this joystick. (Maybe the user unplugged
  // it while we were in the middle of enumerating it.)
  if( FAILED(hr) )
    return DIENUM_CONTINUE;

  // Stop enumeration. Note: we're just taking the first joystick we get. You
  // could store all the enumerated joysticks and let the user pick.
  return DIENUM_STOP;
}

BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi,
                                  VOID* pContext)
{
  // Set the UI to reflect what objects the joystick supports
  if (pdidoi->guidType == GUID_XAxis)
  {
    std::cout << "OIS.X=" << axis_number << std::endl ;
  }
  else if (pdidoi->guidType == GUID_YAxis)
  {
    std::cout << "OIS.Y=" << axis_number << std::endl ;
  }
  else if (pdidoi->guidType == GUID_ZAxis)
  {
    std::cout << "OIS.Z=" << axis_number << std::endl ;
  }
  else if (pdidoi->guidType == GUID_RxAxis)
  {
    std::cout << "OIS.RX =" << axis_number << std::endl ;
  }
  else if (pdidoi->guidType == GUID_RyAxis)
  {
    std::cout << "OIS.RY=" << axis_number << std::endl ;
  }
  else if (pdidoi->guidType == GUID_RzAxis)
  {
    std::cout << "OIS.RZ=" << axis_number << std::endl ;
  }
  else if (pdidoi->guidType == GUID_Slider)
  {
    std::cout << "OIS.Slider=" << axis_number << std::endl ;
  }
  ++axis_number ;
}

/*!
  Utility program that determine mapping between symbolic axes and OIS axes for 
  Joystick. 
*/
int main()
{
  HRESULT hr;
  hr = DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(VOID**)&direct_input, NULL) ;
  std::cout << "[Joystick]" << std::endl ;
  if (FAILED(hr))
  {
    std::cout << "OIS.Joystick.Error=true" << std::endl ;
    return 0 ;
  }
  // search for joystick
  hr = direct_input->EnumDevices(DI8DEVCLASS_GAMECTRL,EnumJoysticksCallback,NULL,DIEDFL_ATTACHEDONLY) ;

  if (!joystick)
  {
    std::cout << "OIS.Joystick.Error=true" << std::endl ;
    return 0 ;
  }

  hr = joystick->EnumObjects(EnumObjectsCallback,NULL,DIDFT_AXIS) ;
  return 0 ;
}
