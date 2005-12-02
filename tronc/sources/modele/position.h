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

#ifndef _PU_MODELE_POSITION_H_
#define _PU_MODELE_POSITION_H_


#include <base/association.h>
#include <modele/distance.h>

namespace ProjetUnivers {

  namespace Modele {


    class Objet ;

    /// Une position dans un espace à trois dimensions.
    /*!
      Une position est :
      - un point d'origine : une sorte de référentiel
      - 3 coordonnées par rapport à ce point
      
      @see Objet
    */
    class Position 
    {
    public:
    
      /// @name Constructeurs
      // @{  


      /// Constructeur par défaut.
      /// Position() ;
     
      /// La position d'un objet physique.
      /*!
      */
      Position(const Base::Association<Objet>& _objet) ;

      /// La même position mais relative à un objet particulier.
      /*! 
        La position et l'objet doivent être dans le même espace.

      @dot
      digraph example {

        node [shape=record, style=rounded, fontname=Helvetica, fontsize=10];
      
        
        Affichage [ label="Affichage" URL="\ref Affichage"];
        Modele [ label="Modele" URL="\ref Modele"];
        Controle [ label="Controle" URL="\ref Controle"];
      
        Controle -> Modele [ label="lecture/modification" arrowhead="open", style="dashed" ];
        Controle -> Affichage [ label="lecture/modification" arrowhead="open", style="dashed" ];
        Affichage -> Modele [ label="lecture" arrowhead="open", style="dashed" ];
        Modele -> Affichage [ label="notification" arrowhead="open", style="dashed" ];
      }
      @enddot
         
        @remark
          Position(p,objet) == p
      */
      Position(const Position&, const Base::Association<Objet>&) ;

      /// Relocalise la position par rapport à un objet particulier.
      /*!
        Tout se passe comme si on déplaçait l'objet.
        Sa nouvelle origine est l'objet passé en paramètre.
        
        @remark
          objet != p.origine => p != p.Relocaliser(objet)
      */
      Position Relocaliser(const Base::Association<Objet>&) const ;


      /// Construit la position indiquée.
      /*!
        On donne une origine et 3 distances.
      */  
      Position(const Position& _origine,
               const Distance& x, 
               const Distance& y, 
               const Distance& z) ;
      

      /// Constructeur de copie.
      Position(const Position&) ;
      
      // @}

      // *************************
      /// @name Accès
      // *************************      
      // @{  
      
      /// Opérateur d'égatité.
      Base::Booleen operator==(const Position&) const ;
      
      // Distance entre 2 Position.
      Distance CalculerDistance(const Position&) const ; 
    
      // @}
    
    private:
    

      /// Vrai si this est utilisé comme origine de _position
//      Base::Booleen EstOrigine(const Position& _position) const ;

      /*!
        Implantation l'aide de trois distances, 
        qui sont les distances entre les divers projections sur les plans 
        des coordonnées et le point qui sert d'origine au système.      
      */
      Base::Association<Objet> origine ;
      Distance coordonneeX ;
      Distance coordonneeY ;
      Distance coordonneeZ ;      
      
      /// Le référentiel du système de coordonnées.
      Base::Association<Objet> referentiel ;
  
      friend class Objet ;
      
    };
  }
}
#endif
