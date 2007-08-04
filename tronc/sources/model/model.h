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

#ifndef PU_MODEL_MODEL_H_
#define PU_MODEL_MODEL_H_

#include <string>


namespace ProjetUnivers {
  
  namespace Kernel {
    class Object ;
    class Trait ;
    class Model ;
  }
   
  /// Game data model.
  /*!
  @par Introduction
  
    Model part of Model/View/Control. Functionnal core.
    
    This module contains all data about manipulated objects in the game 
    regardless of displaying and events that triggers modifications.
    
  */ 
  namespace Model 
  {
    
  
  /*!
    @name Init/Close.
  */
  //@{        
    
    /// Starts the module.
    void init() ;

    /// Closes le module.
    void close() ;

    /// Load a model from disk.
    void load(const std::string& _name) ;

    /// Load and init external ressources.
    void initRessources() ;
        
  //@}
  /*!
    @name Modification Interface
    
  */
  // @{

    /// Get an object.
    Kernel::Object* getObject(const std::string& i_name) ;
      
    /// Creates a new Kernel::Object with name.
    Kernel::Object* createObject(const std::string& i_name) ; 

    /// Creates a new Kernel::Object.
    Kernel::Object* createObject() ; 

    /// Creates a new Kernel::Object with name and given parent.
    Kernel::Object* createObject(const std::string& i_name, 
                                 Kernel::Object* i_parent) ; 

    /// Creates a new Kernel::Object with given parent.
    Kernel::Object* createObject(Kernel::Object* i_parent) ; 

    /// Destroy an Kernel::Object of given name.
    void destroyObject(const std::string& i_name) ;

    /// Destroy a given Kernel::Object.
    void destroyObject(Kernel::Object* i_object) ;

    /// Changes parent of a given Kernel::Object.
    void changeParent(Kernel::Object* i_object, 
                      Kernel::Object* i_new_parent) ;

    /// Adds a new trait to an Kernel::Object.
    void addTrait(Kernel::Object* i_object, 
                  Kernel::Trait* i_new_trait) ;

    /// Destroy an Kernel::Object's trait.
    void destroyTrait(Kernel::Object* i_object, 
                      Kernel::Trait* i_trait) ;

  // @}
  /*!
    @name Semantic relationships 
  
    Parentship has several meanings according to object structure. For 
    example isInside relationship is used for 3 object relative placement. 
    isPartOf is used for physics and collision.  
    
    Definition of these relationship is mainly for internal documentation  
    purpose; as a kind of model describing.

    @todo 
      Define 
      - isOn : a person is on a planet, a worm is inside a planet
      - isMember : a person is a member of a party
  */
  // @{

    /// True iff @c i_content is inside @c i_contener.
    /*!
      @c i_content is inside @c i_contener iff 
      - both are Positionned and 
      - @c i_contener is an ancestor of @c i_content 
    */
    bool isInside(Kernel::Object* i_content,Kernel::Object* i_contener) ;


    /// True iff @c i_part is a part of @c i_whole.
    /*!
      @c i_part is a part of @c i_whole iff 
      - @c i_part is a direct part of @c i_whole or 
      - @c i_part is a part of x and x is a direct part of @c i_whole

      @c i_part is a direct part of @c i_whole iff 
      - both are Positionned and 
      - @c i_whole is Composite
      - @c i_part is Component
      - @c i_whole is the parent of @c i_part 
    */
    bool isPartOf(Kernel::Object* i_part,Kernel::Object* i_whole) ;

    /// True iff @c i_object is a whole.
    /*!
      @c i_object is a whole iff :
      - @c i_object is not component
      
      @remark 
        If an object is an elementary whole (i.e. an object whitout component) 
        it still remains a whole when subdividing it into compenents. It is 
        a very good idea that view points relies on being a whole, because it 
        is more likely to be a property that resists model evolutions.   
    
    */
    bool isAWhole(Kernel::Object* i_object) ;

  //@}
  /*!
    @name Interface for other modules
    
    Ce n'est pas au point. Pour l'instant c'est ce qu'utilise display .
    
    --> le sortir en model_display.h
  */
  // @{

    /// Access to real world model. 
    Kernel::Model* getRealWorlModel() ;
  
  // @}
  
  }
  
}

#endif

