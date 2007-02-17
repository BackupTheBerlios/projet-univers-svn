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

#ifndef _BASE_H_
#define _BASE_H_


namespace ProjetUnivers {

  /// Biblioth�que de templates et de types.
  
  /*!
    Cette biblioth�que met l'accent sur la dif�rence entre composition et 
    association. La composition permet d'automatiquement d�truire l'objet 
    point�. L'association elle se comporte comme une r�f�rence standard.

    Pour une m�me classe d'objet T on se retrouve avec 3 types distincts :
    
    - Composition<T> 
        c'est une composition mono-valu�e
    - Association<T>
        c'est une association mono-valu�e
    - T*
        c'est le type "temporaire" des objets qui ont �t� cr��s mais qui 
        ne sont pas encore composant d'un autre objet
    
    Si on veut une relation multi-valu�e, il faut alors utiliser 
    EnsembleComposition, EnsembleAssociation ou EnsembleValeur, selon le cas.
    
    Enfin, s'il s'agit d'une fonction (au sens) math�matique que l'on veut il 
    faut utiliser...

  \todo
    EnsembleValeur
    Fonction...  
  */ 
  namespace Base 
  {}
  
}


#endif //_BASE_H_
