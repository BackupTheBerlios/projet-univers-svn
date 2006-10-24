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

#include <base/traceur.h>

#include <base/implantation/base_vue.h>
#include <base/modele.h>

#include <base/iterateur_ensemble_association.h>


namespace ProjetUnivers {

  namespace Base {
    
    void Modele::AjouterVue(const Association<Implantation::BaseVue>& _vue)
    {
      observateurs.Ajouter(_vue) ;  
    }
      
    void Modele::EnleverVue(const Association<Implantation::BaseVue>& _vue)
    {
      observateurs.Enlever(_vue) ;
    }
    
    Modele::~Modele()
    {
      
      Traceur::MessageInterne(Chaine(observateurs.NombreDElements()) + " elements") ;
      for(IterateurEnsembleAssociation<Implantation::BaseVue> vue(observateurs) ;
          vue.Valide() ;
          ++vue)
      {
        vue->MarquerADetruire() ;
        vue->DetacherDeModele() ;
      }
      
    }
    
    Modele::Modele()
    {}

    void Modele::Notifier(const Evenement& _evenement)
    {
      for(IterateurEnsembleAssociation<Implantation::BaseVue> vue(observateurs) ;
          vue.Valide() ;
          ++vue)
      {
        vue->MarquerARafraichir(_evenement) ;
      }  
    }
    
    
  }
}


