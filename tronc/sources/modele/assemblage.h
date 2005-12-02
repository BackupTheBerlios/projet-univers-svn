../***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#ifndef _PU_MODELE_ASSEMBLAGE_H_
#define _PU_MODELE_ASSEMBLAGE_H_

#include <base/ensemble_association.h>
#include <modele/objet_physique.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
    
      
    ///  Un assemblage d'objets.
    
    /*!
    Un assemblage est le regroupement d'un ensemble d'objets physiques qui sont 
    physiquement reliés les uns aux autres.
    
    
    @par Type de classe
    - Concrète
    - Objet
      
    @todo
      trouver une forme canonique unique pour tous les assemblages et 
      contraintes.
      
    @par Description générale
    
      Les notions d'assemblage et de contraintes d'assemblages relèvent du 
      domaine de la CAO (conception assistée par ordinateur). Il s'agit ici de 
      généraliser des notions de mécanique/ingéniérie de la construction des 
      machines physiques. 
      
    @par Etat de l'art
    
      Il convient de considérer des logiciels comme OpenCascade.
      
    @par Fonctionnement
    
    @par Questions
    
      Est-ce un objet physique ?
        - si oui alors un assemblage peut être un élément d'un autre assemblage
      
    */
    class Assemblage : public ObjetPhysique
    {
    public:

      /// Constructeur.
      Assemblage() ;

      /// Ajoute un objet avec une certaine contrainte.
      void Ajouter(ObjetPhysique* _objet) ;

      /// Ajoute un objet avec une certaine contrainte.
      void Ajouter(Contrainte* _liberte) ;
      
      /// Enlève l'objet, celui-ci est renvoyé.
      ObjetPhysique* Enlever(const Base::Association<ObjetPhysique>& _objet) ;
 
    private:

      /*!
      @remark
          Les objets ont tous des positions relatives à l'assemblage.
      */
      Base::EnsembleAssociation<ObjetPhysique> composants ;

      /// Les contraintes entre les composants de l'assemblage.
      /*!
      Chacune des contraintes doit porter sur des objets de composants.
      */
      Base::EnsembleAssociation<Contrainte> constraintes ;


    };
    
    
  }

}

#endif
