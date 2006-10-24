/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_BASE_SINGLETON_H_
#define _PU_BASE_SINGLETON_H_


namespace ProjetUnivers {
  namespace Base {
    
    
    /// Propriété pour une classe de n'avoir qu'une seule instance.
    /*!
    @par Etat
      planning
    */
    template <class Objet> class Singleton
    {
    public:
    
      /// Acces à l'instance.
      Association<Objet> AccesInstance() ;
      
      /// Destructeur de classe abstraite.
      virtual ~Singleton() ;
      
    private:
      
      /// L'instance unique
      static Composition<Objet> instance ;
      
    };
    
  }
  
}


#endif //_PU_BASE_OBJET_H_
#ifndef SINGLETON_H_
#define SINGLETON_H_

#endif /*SINGLETON_H_*/
