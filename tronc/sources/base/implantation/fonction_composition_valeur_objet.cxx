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
      Vider() ;
    }

    template <typename Valeur, class Objet >
    void 
    FonctionCompositionValeurObjet<Valeur,Objet>::Vider()
    {
      // détruire tous les éléments.
      for(typename std::map<Valeur,Objet*>::iterator i(fonction.begin()) ;
          i != fonction.end() ;
          ++i)
      {
        delete (*i).second ;
      }
      
      fonction.clear() ;
      
    }


    template <typename Valeur, class Objet > 
    void FonctionCompositionValeurObjet<Valeur,Objet>::
    Ajouter(const Valeur& _cle, Objet* _image)
    {
      fonction[_cle] = _image ;
    }
    
    template <typename Valeur, class Objet > 
    void FonctionCompositionValeurObjet<Valeur,Objet>::
    Modifier(const Valeur& _cle, Objet* _image)
    {
      // l'ancien
      Objet* temporaire = fonction[_cle] ;
      
      delete temporaire ;
      
      fonction[_cle] = _image ;
    }

    template <typename Valeur, class Objet > 
    Association<Objet> FonctionCompositionValeurObjet<Valeur,Objet>::
    operator[](const Valeur& _cle) const
    {
      /// l'élément est-il dans la fonction ?
      typename std::map<Valeur,Objet*>::const_iterator estDedans 
          = this->fonction.find(_cle) ;
          
      if (estDedans == this->fonction.end())
      {
        /// pas d'objet associé à @c _cle
        /*!
          @todo
            trouver un moye nde différencier entre 
            - _cle est associé à NULL
            - _cle n'est associé à personne
        */
        return Association<Objet>() ;
      }
      else
      {
        return *(estDedans->second) ;
      }
    }

    template <typename Valeur, class Objet > 

    Booleen FonctionCompositionValeurObjet<Valeur,Objet>::operator==(
      const FonctionCompositionValeurObjet<Valeur,Objet >& _right) 
      const
    {
      return fonction == _right.fonction ;      
    }

    template <typename Valeur, class Objet > 
    Objet* 
    FonctionCompositionValeurObjet<Valeur,Objet>::
    Enlever(const Valeur& _element)
    {
      Objet* result = this->fonction[_element] ;
      this->fonction[_element] = NULL ;
      return result ;
    }
    
  }
}
