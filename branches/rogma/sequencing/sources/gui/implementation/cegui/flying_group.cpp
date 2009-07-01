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
#include <math.h>
#include <CEGUI.h>

#include <kernel/log.h>
#include <kernel/controler.h>
#include <kernel/object.h>

#include <model/custom_mission.h>
#include <model/flying_group.h>

#include <input/input_gui.h>

#include <gui/implementation/gui_internal.h>
#include <gui/implementation/cegui/cegui.h>
#include <gui/implementation/cegui/flying_group.h>
#include <gui/implementation/cegui/team.h>
#include <gui/implementation/cegui/gui_controler_set.h>

namespace ProjetUnivers
{
  namespace GUI
  {
    namespace Implementation
    {
      namespace CEGUI
      {

        RegisterControler(FlyingGroup,
                          EditedFlyingGroup,
                          GUIControlerSet) ;

        void FlyingGroup::onInit()
        {
          InternalMessage("CustomMission","CEGUI::FlyingGroup::onInit") ;

          m_updating = false ;

          m_team = getControler<Team>() ;

          m_window = m_team->addGroupWindow(getObject()) ;

          m_group = getTrait<Model::FlyingGroup>() ;

          ::CEGUI::WindowManager& manager = ::CEGUI::WindowManager::getSingleton() ;

          // title
          m_name = createWindow(m_window,"ProjetUnivers/Editbox","name") ;
          m_name->setText(m_group->getName()) ;
          m_name->setArea(::CEGUI::UDim(0,5),
                          ::CEGUI::UDim(0,0),
                          ::CEGUI::UDim(0.1,-5),
                          ::CEGUI::UDim(1,0)) ;

          m_name->subscribeEvent(::CEGUI::Window::EventTextChanged,
                                 ::CEGUI::Event::Subscriber(&FlyingGroup::changedName,this)) ;

          m_pilot = createWindow(m_window,"ProjetUnivers/StaticText","pilot") ;
          m_pilot->setText(m_group->hasPlayer()?"Player":"AI") ;
          m_pilot->setArea(::CEGUI::UDim(0.1,0),
                           ::CEGUI::UDim(0,0),
                           ::CEGUI::UDim(0.1,0),
                           ::CEGUI::UDim(1,0)) ;

          m_ship = createWindow(m_window,"ProjetUnivers/StaticText","ship") ;
          m_ship->setText(m_group->getShipName()) ;
          m_ship->setArea(::CEGUI::UDim(0.2,0),
                          ::CEGUI::UDim(0,0),
                          ::CEGUI::UDim(0.1,0),
                          ::CEGUI::UDim(1,0)) ;

          m_number_of_ships = createWindow(m_window,"ProjetUnivers/StaticText","InitialNumberOfShips") ;
          m_number_of_ships->setText(Kernel::toString(m_group->getInitialNumberOfShips())) ;
          m_number_of_ships->setArea(::CEGUI::UDim(0.3,10),
                                     ::CEGUI::UDim(0,0),
                                     ::CEGUI::UDim(0.1,-20),
                                     ::CEGUI::UDim(1,0)) ;
          m_number_of_ships->setProperty("HorzFormatting","HorzCentred") ;

          ::CEGUI::Window* decrease = createWindow(m_window,"ProjetUnivers/DecreaseButton","decreaseInitialNumberOfShips") ;
          decrease->setArea(::CEGUI::UDim(0.3,0),
                            ::CEGUI::UDim(0,0),
                            ::CEGUI::UDim(0,10),
                            ::CEGUI::UDim(1,0)) ;
          decrease->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                   ::CEGUI::Event::Subscriber(&FlyingGroup::decreaseNumberOfShips,this)) ;

          ::CEGUI::Window* increase = createWindow(m_window,"ProjetUnivers/IncreaseButton","increaseInitialNumberOfShips") ;
          increase->setArea(::CEGUI::UDim(0.4,-10),
                            ::CEGUI::UDim(0,0),
                            ::CEGUI::UDim(0,10),
                            ::CEGUI::UDim(1,0)) ;
          increase->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                   ::CEGUI::Event::Subscriber(&FlyingGroup::increaseNumberOfShips,this)) ;


          ::CEGUI::Window* objective = createWindow(m_window,"ProjetUnivers/StaticText","objective") ;
          objective->setText("Attack") ;
          objective->setArea(::CEGUI::UDim(0.4,0),
                             ::CEGUI::UDim(0,0),
                             ::CEGUI::UDim(0.1,0),
                             ::CEGUI::UDim(1,0)) ;


          m_number_of_spawn = createWindow(m_window,
                                           "ProjetUnivers/StaticText",
                                           "NumberOfSpawn") ;
          m_number_of_spawn->setText(Kernel::toString(m_group->getNumberOfSpawn())) ;
          m_number_of_spawn->setArea(::CEGUI::UDim(0.5,10),
                                     ::CEGUI::UDim(0,0),
                                     ::CEGUI::UDim(0.1,-20),
                                     ::CEGUI::UDim(1,0)) ;
          m_number_of_spawn->setProperty("HorzFormatting","HorzCentred") ;

          decrease = createWindow(m_window,
                                  "ProjetUnivers/DecreaseButton",
                                  "decreaseNumberOfSpawn") ;
          decrease->setArea(::CEGUI::UDim(0.5,0),
                            ::CEGUI::UDim(0,0),
                            ::CEGUI::UDim(0,10),
                            ::CEGUI::UDim(1,0)) ;
          decrease->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                   ::CEGUI::Event::Subscriber(&FlyingGroup::decreaseNumberOfSpawn,this)) ;

          increase = createWindow(m_window,
                                  "ProjetUnivers/IncreaseButton",
                                  "increaseNumberOfSpawn") ;
          increase->setArea(::CEGUI::UDim(0.6,-10),
                            ::CEGUI::UDim(0,0),
                            ::CEGUI::UDim(0,10),
                            ::CEGUI::UDim(1,0)) ;
          increase->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                   ::CEGUI::Event::Subscriber(&FlyingGroup::increaseNumberOfSpawn,this)) ;

          // delete
          ::CEGUI::Window* button_delete = createWindow(m_window,"ProjetUnivers/DeleteButton","delete") ;
          button_delete->setArea(::CEGUI::UDim(0.8,0),
                                 ::CEGUI::UDim(0,0),
                                 ::CEGUI::UDim(0.2,0),
                                 ::CEGUI::UDim(1,0)) ;
          button_delete->setText("Delete FlyingGroup") ;
          button_delete->subscribeEvent(::CEGUI::Window::EventMouseClick,
                                        ::CEGUI::Event::Subscriber(&FlyingGroup::deleteGroup,this)) ;

          InternalMessage("GUI",printStructure(m_window,0)) ;
        }

        void FlyingGroup::onClose()
        {
          InternalMessage("CustomMission","CEGUI::FlyingGroup::onClose") ;
          m_team->removeGroupWindow(m_window) ;
          if (m_window)
          {
             ::CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }

        void FlyingGroup::onUpdate()
        {
          m_updating = true ;

          m_name->setText(m_group->getName()) ;
          m_ship->setText(m_group->getShipName()) ;
          m_number_of_ships->setText(Kernel::toString(m_group->getInitialNumberOfShips())) ;
          m_number_of_spawn->setText(Kernel::toString(m_group->getNumberOfSpawn())) ;
          m_pilot->setText(m_group->hasPlayer()?"Player":"AI") ;

          m_updating = false ;
        }

        bool FlyingGroup::deleteGroup(const ::CEGUI::EventArgs& args)
        {
          getObject()->destroyObject() ;
          return true ;
        }

        bool FlyingGroup::changedName(const ::CEGUI::EventArgs& args)
        {
          const ::CEGUI::WindowEventArgs* argument = dynamic_cast<const ::CEGUI::WindowEventArgs*>(&args) ;
          if (!m_updating && argument && argument->window)
          {
            m_group->setName(argument->window->getText().c_str()) ;
          }
          return true ;
        }

        bool FlyingGroup::decreaseNumberOfShips(const ::CEGUI::EventArgs& args)
        {
          if (m_group->getInitialNumberOfShips()>1)
            m_group->setInitialNumberOfShips(m_group->getInitialNumberOfShips()-1) ;
          return true ;
        }

        bool FlyingGroup::increaseNumberOfShips(const ::CEGUI::EventArgs& args)
        {
          m_group->setInitialNumberOfShips(m_group->getInitialNumberOfShips()+1) ;
          return true ;
        }

        bool FlyingGroup::decreaseNumberOfSpawn(const ::CEGUI::EventArgs& args)
        {
          if (m_group->getNumberOfSpawn()>1)
          m_group->setNumberOfSpawn(m_group->getNumberOfSpawn()-1) ;
          return true ;
        }

        bool FlyingGroup::increaseNumberOfSpawn(const ::CEGUI::EventArgs& args)
        {
          m_group->setNumberOfSpawn(m_group->getNumberOfSpawn()+1) ;
          return true ;
        }


      }
    }
  }
}
