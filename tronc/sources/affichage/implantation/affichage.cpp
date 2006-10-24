/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#include <base/ensemble_composition.h>


#include <affichage/exception.h>
#include <affichage/implantation/ogre/ogre.h>
#include <affichage/point_de_vue.h>

#include <affichage/affichage.h>

namespace ProjetUnivers {
  namespace Affichage {

  /*!
    @name Attributs
  */
  // @{

    /// Les points de vue gérés par l'affichage.
    Base::EnsembleComposition<PointDeVue> pointsDeVue ;

    /// Le point de vue actif.
    Base::Association<PointDeVue> pointDeVueActif ;

    Base::Booleen initialise = Base::FAUX ;

  // @}
    
    Base::Booleen Initialiser() 
    {
      if (! initialise)
      {
        Base::Booleen resultat = Implantation::Ogre::Initialiser() ; 
        
        initialise = Base::VRAI ;
        
        if (pointDeVueActif)
        {
          pointDeVueActif->Initialiser() ;
        }      
      
        return resultat ;
      }
      else
      {
        // déjà initialisé
        return Base::VRAI ;
      }
    }
    
    void Terminer()
    {
      pointsDeVue.Vider() ;
      Implantation::Ogre::Terminer() ;
    }

    size_t DescripteurFenetre()
    {
      VerifieCondition(initialise, Exception("Module non initialisé")) ;
      
      return Implantation::Ogre::DescripteurFenetre() ;
    }

    /// Accès à la taille de la fenêtre
    void TailleFenetre(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top)
    {
      VerifieCondition(initialise, Exception("Module non initialisé")) ;

      Implantation::Ogre::TailleFenetre(width,height,depth,left,top) ;
    }

    /// Ajoute un point de vue.
    Base::Association<PointDeVue> AjouterPointDeVue(PointDeVue* _pdv)
    {
      Base::Composition<PointDeVue> temp(_pdv) ;
      Base::Association<PointDeVue> resultat(temp) ;
      
      pointsDeVue.Ajouter(temp.Liberer()) ;
      
      return resultat ;
    }

    /// Supprime le point de vue.
    void SupprimerPointdeVue(const Base::Association<PointDeVue>& _pdv)
    {
      pointsDeVue.Enlever(_pdv) ;

    }
    
    
    /// 
    /*!
      Inutile car il suffit d'activer un autre point de vue ?
    */
    void DesactiverPointDeVue(const Base::Association<PointDeVue>& _pdv)
    {
      if (_pdv)
      {
        _pdv->Desactiver() ;
      }
    }
    
    /// Le point de vue devient celui actif.
    void ActiverPointDeVue(const Base::Association<PointDeVue>& _pdv)
    {
      DesactiverPointDeVue(pointDeVueActif) ;
      pointDeVueActif = _pdv ;
      
      pointDeVueActif->Initialiser() ;
      
      pointDeVueActif->Activer() ;
      
    }
  
  
    void Rafraichir() 
    {
      VerifieCondition(initialise, Exception("Module non initialisé")) ;
      VerifieCondition(Base::Booleen(pointDeVueActif), Exception("Pas de point de vue actif")) ;
    
      pointDeVueActif->Rafraichir() ;
      Implantation::Ogre::Rafraichir() ;
    }
  }
  
}
