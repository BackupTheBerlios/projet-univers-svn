/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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
#ifndef PU_MODEL_TRAIT_H_
#define PU_MODEL_TRAIT_H_

#include <kernel/model.h>


namespace ProjetUnivers {
  namespace Model {

    class Object ;

    /// Une facette d'un objet.
    /*!
      C'est une partie d'un objet dans un modèle à délégation.
      Une facette appartient à un seul objet. 
      Un objet peut avoir autant de facettes qu'il veut.
      Un objet ne peut avoir qu'une seule facette d'un certain type :
      - par exemple, un objet ne peut avoir qu'une seule facette de type 
        Positionné, car l'objet n'a qu'une seule position.
        
      Une facette d'objet regoupe un ensemble d'attributs de l'objet.
    */
    class Trait : public Kernel::Model
    {
    public:

      /// Access to object.      
      Object* getObject() const ;

      virtual ~Trait() ;
    

    protected: 
    
      /// Créé une facette pour un objet.
      Trait() ;
      
      /// Object sur lequel s'applique la facette.
      Object* object ;
      
      friend class Object ;
            
    };



  }
}



#endif /*PU_MODEL_TRAIT_H_*/
