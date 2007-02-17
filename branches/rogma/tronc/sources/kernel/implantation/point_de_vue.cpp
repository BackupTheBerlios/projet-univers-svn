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

#include <base/implantation/base_vue.h>
#include <base/point_de_vue.h>
#include <base/iterateur_ensemble_valeur.h>


namespace ProjetUnivers {
  namespace Base {

    void ViewPoint::update()
    {
      
      for(IterateurEnsembleValeur<ViewPoint::Rafraichissement> rafraichissement(rafraichissements) ;
          rafraichissement.Valide() ;
          ++rafraichissement)
      {
        rafraichissement->vue->update(rafraichissement->evenement) ;
      }
      rafraichissements.Vider() ;

      for (std::vector<Implantation::BaseVue*>::iterator vue = vuesAdestroy.begin() ;
           vue != vuesAdestroy.end() ;
           ++vue)
      {
        this->destroy(**vue) ;
      }
      
      /// on vide sans détruire l'espace alloué
      vuesAdestroy.resize(0) ;
    }
  
    ViewPoint::ViewPoint()
    {}

    void ViewPoint::add(Implantation::BaseVue* _vue)
    {
      if (_vue)
      {
        _vue->pointDeVue = *this ;
        vues.add(_vue) ;
      }
      // sinon ... ???
    }
    
    void ViewPoint::remove(const Association<Implantation::BaseVue>& _vue)
    {
      vues.remove(_vue) ;
    }
    
    void ViewPoint::PenserAupdate(
                                  const Association<Implantation::BaseVue> _vue,
                                  const Evenement& _evenement)
    {
      rafraichissements.add(Rafraichissement(_vue,_evenement)) ;
    }
    
    void ViewPoint::PenserAdestroy(
                                  const Association<Implantation::BaseVue> _vue)
    {
      vuesAdestroy.push_back(&*_vue) ;
    }
    void ViewPoint::destroy(const Association<Implantation::BaseVue>& _vue)
    {
      this->vues.remove(_vue) ;
    }
    
    
  }
}

