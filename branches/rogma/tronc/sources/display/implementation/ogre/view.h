/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_VIEW_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_VIEW_H_

#include <kernel/view.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        class ViewPoint ;
                      
        /// Une vue Ogre.
        /*!
          Sert à factoriser certaines opérations.
        */
        template <class Model> class View : public Kernel::View<Model>
        {
        public:
    
          /// Object de cette facette.          
          ViewPoint* getViewPoint() const ;

          /// Mise à jour de la vue.
          virtual void update(const Kernel::Event&) = 0 ;
    
          /// Destructeur de classe abstraite.    
          virtual ~View() ;
        
        protected: 
        
          /// Constructeur de classe abstraite.
          View(Model* _model) ;
        };
      }
    }
  }
}

#include <display/implementation/ogre/view.cxx>

#endif /*PU_DISPLAY_IMPLEMENTATION_OGRE_VIEW_H_*/
