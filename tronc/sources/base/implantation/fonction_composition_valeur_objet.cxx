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

#include <iterator>

namespace ProjetUnivers {

  namespace Base {

    template <typename Valeur, class Objet > 
    FonctionCompositionValeurObjet<Valeur,Objet>::
    FonctionCompositionValeurObjet()
    {}
    
    template <typename Valeur, class Objet > 
    FonctionCompositionValeurObjet<Valeur,Objet>::
    ~FonctionCompositionValeurObjet()
    {
      // détruire tous les éléments.
      for(typename std::map<Valeur,Objet*>::iterator i(fonction.begin()) ;
          i != fonction.end() ;
          ++i)
      {
        delete (*i).second ;
      }
    }
    
    template <typename Valeur, class Objet > 
    void FonctionCompositionValeurObjet<Valeur,Objet>::
    Ajouter(const Valeur& _cle, const Objet* _image)
    {
      fonction[_cle] = _image ;
    }
    
    template <typename Valeur, class Objet > 
    void FonctionCompositionValeurObjet<Valeur,Objet>::
    Modifier(const Valeur& _cle, const Objet* _image)
    {
      // l'ancien
      Objet* temporaire = fonction[_cle] ;
      
      delete temporaire ;
      
      fonction[_cle] = _image ;
    }

//    template <typename Valeur, class Objet > 
//    Objet* FonctionCompositionValeurObjet<Valeur,Objet>::
//    Liberer(const Valeur& _element)
//    {
//      // l'ancien
//      Objet* temporaire = fonction[_cle] ;
//      
//      fonction[_cle] = NULL ;
//      
//      return temporaire ;
//    }

//    template <typename Valeur, class Objet > 
//    Objet* FonctionCompositionValeurObjet<Valeur,Objet>::
//    Enlever(const Valeur& _element) 
//    {
//      // l'ancien
//      Objet* temporaire = fonction[_cle] ;
//      
//      fonction[_cle] = NULL ;
//      
//      return temporaire ;
//      
//    }

   
  }
}
