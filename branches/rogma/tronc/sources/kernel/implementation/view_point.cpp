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

#include <kernel/implementation/base_vue.h>
#include <kernel/point_de_vue.h>
#include <kernel/iterateur_ensemble_valeur.h>


namespace ProjetUnivers {
  namespace Kernel {

    void ViewPoint::update()
    {
      
      for(IterateurEnsembleValeur<ViewPoint::Rafraichissement> rafraichissement(rafraichissements) ;
          rafraichissement.Valide() ;
          ++rafraichissement)
      {
        rafraichissement->vue->update(rafraichissement->evenement) ;
      }
      rafraichissements.Vider() ;

      for (std::vector<Implementation::KernelView*>::iterator vue = vuesAdestroy.begin() ;
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

    void ViewPoint::add(Implementation::KernelView* _vue)
    {
      if (_vue)
      {
        _vue->pointDeView = *this ;
        vues.add(_vue) ;
      }
      // sinon ... ???
    }
    
    void ViewPoint::remove(const Association<Implementation::KernelView>& _vue)
    {
      vues.remove(_vue) ;
    }
    
    void ViewPoint::PenserAupdate(
                                  const Association<Implementation::KernelView> _vue,
                                  const Event& _evenement)
    {
      rafraichissements.add(Rafraichissement(_vue,_evenement)) ;
    }
    
    void ViewPoint::PenserAdestroy(
                                  const Association<Implementation::KernelView> _vue)
    {
      vuesAdestroy.push_back(&*_vue) ;
    }
    void ViewPoint::destroy(const Association<Implementation::KernelView>& _vue)
    {
      this->vues.remove(_vue) ;
    }
    
    
  }
}

