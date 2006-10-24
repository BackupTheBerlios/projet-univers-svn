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

    void PointDeVue::Rafraichir()
    {
      
      for(IterateurEnsembleValeur<PointDeVue::Rafraichissement> rafraichissement(rafraichissements) ;
          rafraichissement.Valide() ;
          ++rafraichissement)
      {
        rafraichissement->vue->Rafraichir(rafraichissement->evenement) ;
      }
      rafraichissements.Vider() ;

      for (IterateurEnsembleAssociation<Implantation::BaseVue> vue(vuesADetruire) ;
           vue.Valide() ;
           ++vue)
      {
        this->vues.Enlever(*vue) ;
      }
      
      vuesADetruire.Vider() ;
    }
  
    PointDeVue::PointDeVue()
    {}

    void PointDeVue::Ajouter(Implantation::BaseVue* _vue)
    {
      if (_vue)
      {
        _vue->pointDeVue = *this ;
        vues.Ajouter(_vue) ;
      }
      // sinon ... ???
    }
    
    void PointDeVue::Enlever(const Association<Implantation::BaseVue>& _vue)
    {
      vues.Enlever(_vue) ;
    }
    
    void PointDeVue::PenserARafraichir(
                                  const Association<Implantation::BaseVue> _vue,
                                  const Evenement& _evenement)
    {
      rafraichissements.Ajouter(Rafraichissement(_vue,_evenement)) ;
    }
    
    void PointDeVue::PenserADetruire(
                                  const Association<Implantation::BaseVue> _vue)
    {
      if (this->vues.Contient(_vue))
      {
        vuesADetruire.Ajouter(_vue) ;
      }
    }
    
    
  }
}

