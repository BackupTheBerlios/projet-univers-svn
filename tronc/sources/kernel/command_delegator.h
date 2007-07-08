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
#ifndef PU_KERNEL_COMMAND_DELEGATOR_H_
#define PU_KERNEL_COMMAND_DELEGATOR_H_

#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Kernel {
   
    /// A predefined trait that delegates command to other pbjects 
    /*!
      Simply add this trait to an object and add delegate objects.

      @example 
        * add a CommandDelegator to a pilot object, 
        * then add stick and throttle as delegates to the CommandDelegator
        * the pilot will respond to stick and throttle command relaying them 
          to these components 
    */
    class CommandDelegator : public Trait
    {
    public:

      /// Constructs.     
      CommandDelegator() ;
      
      /// Trait will delegate commands to @c i_delegate. 
      void addDelegate(Object* i_delegate) ;
      
    protected:

      /// call a void command returns true iff succedeed.
      virtual bool call(const TypeIdentifier& i_trait_type,
                        const std::string&    i_command) ;

      /// call an int command returns true iff succedeed.
      virtual bool call(const TypeIdentifier& i_trait_type,
                        const std::string&    i_command, 
                        const int&            i_parameter) ;

      /// Access to all commands understood be the trait.
      virtual std::set<std::string> getCommands() const ;
      
    private:
    
      /// Objects to which commands are send
      std::set<Object*> m_delegates ;
    
    };
  }
}


#endif /*PU_KERNEL_COMMAND_DELEGATOR_H_*/
