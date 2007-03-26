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
#ifndef PU_DISPLAY_DISPLAY_H_
#define PU_DISPLAY_DISPLAY_H_



namespace ProjetUnivers {
  namespace Kernel
  {
    class Object ;
  }

 
  /// Le module r�alisant l'affichage des objets de Model.
  /*!
    C'est la View de Model qui r�alise l'affichage � l'�cran.
    
    - l'affichage poss�de l'�cran et la racine
    - il a des points de vues qui eux poss�dent des scene manager
    - un est affich� (actif), les autres sont maintenus mais ne sont pas affich�s
  */ 
  namespace Display {
    
    namespace Implementation
    {
      class RealWorldViewPoint ;
    }
    
    /// Module initialisation.
    bool init() ;
    
    /// Module closing.
    void close() ;
  
    /// Creates the standard representation for the world 
    Kernel::ViewPoint* buildRealWorldViewPoint(Kernel::Object* i_observer) ; 
    
    /// Make @c i_viewpoint the displayed viewpoint. 
    void activateViewPoint(Implementation::RealWorldViewPoint* i_viewpoint) ;
    
    /// Update display
    void update() ;
    
  }
  
}



#endif //PU_DISPLAY_DISPLAY_H_
