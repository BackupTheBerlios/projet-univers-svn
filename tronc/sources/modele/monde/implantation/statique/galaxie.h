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

#ifndef _PU_MODELE_GALAXIE_H_
#define _PU_MODELE_GALAXIE_H_

#include <base/chaine.h>
#include <base/ensemble_composition.h>


#include <modele/nom.h>
#include <modele/objet_physique.h>


namespace ProjetUnivers {

  namespace Modele {
    
    
    
    class SystemeStellaire ;
    
      
    ///  Une galaxie.

    /*!
      C'est l'objet physique qui repr�sente une partie de la galaxie.

      
      @deprecated ???
        Soit : 
        - Une galaxie n'a d'int�ret que comme une information encyclop�dique � 
        propos des syst�mes
        - soit, on s�pare information encyclop�dique, et mod�les r��l (qui est 
        une "instantiation" du premier)... ce qui donne 2 mod�les 
        par exemple on peut avoir 2 groupes de personnes se battant chacun dans 
        la m�me galaxie l'un � l'autre bout avec une transmission vid�o entre eux 
        (comme dans X2) 
      
    */
    class Galaxie : public ObjetPhysique {
    public:

      /// Constructeur.
      Galaxie(const Nom& _nom) ;
      
      /// Ajoute un nouveau syst�me
      void Ajouter(SystemeStellaire* _systeme) ;
      
      
    private:
      

      Nom nom ;

      /// Les syst�mes "actifs".
      /*!
        Ceux dont on a obligatoirement besoin pour le jeux...
      */      
      Base::EnsembleComposition<SystemeStellaire> systemes ;
      

    };
    
    
  }

}

#endif
