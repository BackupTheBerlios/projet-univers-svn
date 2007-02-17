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
  namespace Display {

  /*!
    @name Attributs
  */
  // @{

    /// Les points de vue g�r�s par l'affichage.
    Base::EnsembleComposition<ViewPoint> pointsDeVue ;

    /// Le point de vue actif.
    Base::Association<ViewPoint> pointDeVueActif ;

    Base::Booleen initialise = Base::FAUX ;

  // @}
    
    Base::Booleen init() 
    {
      if (! initialise)
      {
        Base::Booleen resultat = Implantation::Ogre::init() ; 
        
        initialise = Base::VRAI ;
        
        if (pointDeVueActif)
        {
          pointDeVueActif->init() ;
        }      
      
        return resultat ;
      }
      else
      {
        // d�j� initialis�
        return Base::VRAI ;
      }
    }
    
    void close()
    {
      pointsDeVue.Vider() ;
      Implantation::Ogre::close() ;
    }

    size_t DescripteurFenetre()
    {
      VerifieCondition(initialise, Exception("Module non initialis�")) ;
      
      return Implantation::Ogre::DescripteurFenetre() ;
    }

    /// Acc�s � la taille de la fen�tre
    void TailleFenetre(unsigned int& width,
                       unsigned int& height,
                       unsigned int& depth,
                       int& left,
                       int& top)
    {
      VerifieCondition(initialise, Exception("Module non initialis�")) ;

      Implantation::Ogre::TailleFenetre(width,height,depth,left,top) ;
    }

    /// Ajoute un point de vue.
    Base::Association<ViewPoint> addViewPoint(ViewPoint* _pdv)
    {
      Base::Composition<ViewPoint> temp(_pdv) ;
      Base::Association<ViewPoint> resultat(temp) ;
      
      pointsDeVue.add(temp.Liberer()) ;
      
      return resultat ;
    }

    /// Supprime le point de vue.
    void SupprimerPointdeVue(const Base::Association<ViewPoint>& _pdv)
    {
      pointsDeVue.remove(_pdv) ;

    }
    
    
    /// 
    /*!
      Inutile car il suffit d'activer un autre point de vue ?
    */
    void DesactiverViewPoint(const Base::Association<ViewPoint>& _pdv)
    {
      if (_pdv)
      {
        _pdv->Desactiver() ;
      }
    }
    
    /// Le point de vue devient celui actif.
    void ActiverViewPoint(const Base::Association<ViewPoint>& _pdv)
    {
      DesactiverViewPoint(pointDeVueActif) ;
      pointDeVueActif = _pdv ;
      
      pointDeVueActif->init() ;
      
      pointDeVueActif->Activer() ;
      
    }
  
  
    void update() 
    {
      VerifieCondition(initialise, Exception("Module non initialis�")) ;
      VerifieCondition(Base::Booleen(pointDeVueActif), Exception("Pas de point de vue actif")) ;
    
      pointDeVueActif->update() ;
      Implantation::Ogre::update() ;
    }
  }
  
}
