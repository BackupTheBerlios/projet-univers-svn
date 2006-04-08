/***************************************************************************
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

#include <modele/objet.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
    class Contrainte ;
    class PlanDAssemblage ;
    class Positionne ;
      
    ///  Un assemblage d'objets.
    
    /*!
    Un assemblage est le regroupement d'un ensemble d'objets qui sont 
    physiquement reli�s les uns aux autres.
    
    
    @par Type de classe
    - Concr�te
    - Objet
      
    @todo
      trouver une forme canonique unique pour tous les assemblages et 
      contraintes.
      
    @par Description g�n�rale
    
      Les notions d'assemblage et de contraintes d'assemblages rel�vent du 
      domaine de la CAO (conception assist�e par ordinateur). Il s'agit ici de 
      g�n�raliser des notions de m�canique/ing�ni�rie de la construction des 
      machines physiques. 
      
    @par Etat de l'art
    
      Il convient de consid�rer des logiciels comme OpenCascade.
      
     
    */
    class Assemblage : public virtual Objet
    {
    public:

    // ***************************************************
    /*!
      @name M�thodes principales
    */
    // ***************************************************
    // @{
      
      /// Constructeur.
      /*!
        @param[in] _nom Le nom de l'objet
        @param[in] _plan Le plan d�crivant l'assemblage
      */
      Assemblage(const Base::Association<PlanDAssemblage>& _plan) ;
      Assemblage(const Nom& _nom, 
                 const Base::Association<PlanDAssemblage>& _plan) ;


    // @}
    // *********************************************
    /*!
      @name Construction d'un assemblage "� la main"

      @par Cas d'utilisation 1
      
      Cela sert classiquement � modifier un assemblage existant pour le 
      casser.

      @par Cas d'utilisation 2
      
      -# Construire un objet avec Assemblage
      -# Ajouter les objets par AjouterObjet
      -# Ajouter les conrtaintes par AjouterContrainte

      @remark
       Cette m�thode de construction n'est pas recommand�e.

    */
    // *********************************************
    // @{

      /// Constructeur.
      Assemblage() ;
      Assemblage(const Nom& _nom) ;


      /// Ajoute un objet avec une certaine contrainte.
      void AjouterObjet(const Base::Association<Positionne>& _objet) ;

      /// Ajoute une contrainte entre objets.
      /*!
        @pre les objets intervenant dans la contrainte doivent �tre des objets 
        de l'assemblage.
      */
      void AjouterContrainte(const Base::Association<Contrainte>& _liberte) ;
      
      /// Enl�ve un objet.
      void EnleverObjet(const Base::Association<Objet>& _objet) ;
      
      /// Enl�ve une contrainte.
      void EnleverContrainte(const Base::Association<Contrainte>& _objet) ;
 
      
    // @}
    /*!
      @name Affichage
    */
    // @{
    
      /// Chaine repr�sentant une r�f�rence � l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine repr�sentant la d�finition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;
      
    // @}
     
      
      
    private:

      /*!
      @remark
          Les objets ont tous des positions relatives � l'assemblage.
      */
      Base::EnsembleAssociation<Positionne> composants ;

      /// Les contraintes entre les composants de l'assemblage.
      /*!
      Chacune des contraintes doit porter sur des objets de composants.
      */
      Base::EnsembleAssociation<Contrainte> contraintes ;

      Base::Association<PlanDAssemblage> plan ;

    };
    
    
  }

}

#endif
