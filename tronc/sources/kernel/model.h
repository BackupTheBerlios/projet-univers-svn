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

#ifndef _PU_KERNEL_MODEL_H_
#define _PU_KERNEL_MODEL_H_

#include <set>

#include <kernel/event.h>


namespace ProjetUnivers {
  namespace Kernel {
    
    namespace Implementation
    {
      class BaseView ;
    }

    class Object ;
    
    /// L'abstraction d'un mod�le.
    /*!
      A utiliser en combinaison avec ProjetUnivers::Kernel::View.
    */
    class Model
    {
    public:
    
      /// Register une vue.
      /*!
        Toutes les vues enregistr�es seront notifi�es des changements 
        de cet objet.
      */
      void addView(Implementation::BaseView* _view) ;
      
      /// Des-enregistre une vue.
      void removeView(Implementation::BaseView* _view) ;
    
      /// Classe abstraite donc destructeur virtuel.
      virtual ~Model() ;
    
    protected:

      /// Classe abstraite donc constructeur prot�g�.
      Model() ;

      /// Notifie les vues du changement.
      void notify(const Event& _event = Event()) ;
    
    private:
    
      /// Les vues pour lesquelles il faut avertir des changements.
      std::set<Implementation::BaseView*> views ;

    };
    
  }
}

#endif

