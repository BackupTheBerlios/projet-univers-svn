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


#ifndef _AFFICHAGE_IMPLANTATION_PLANETOIDE_H_
#define _AFFICHAGE_IMPLANTATION_PLANETOIDE_H_

#include <base/association.h>
#include <base/vue.h>


namespace ProjetUnivers {
  
  namespace Modele
  {
    class Planetoide ;
  }
  
  
  namespace Affichage {

    namespace Implantation {


      

      /// Partie affichage d'un planetoide.
      /*!
        @deprecated
      
        
      */
      class Planetoide : public Base::Vue<Modele::Planetoide>
      {
      public:
        /*!
          @name Raffraichissement
          
          
        */  
        // @{
        
        
        /// Le modèle a changé, on réactualise la vue.
        virtual void Raffraichir() ;
          
            
        // @}

        virtual ~Planetoide() ;

      protected:
            
        /// Constructeur.
        Planetoide(const Base::Association< Modele::Planetoide>& _planetoide) ;
        
      private:
      
      
        
              
      };



        /*!
          Est redéfini dans les modules d'extensions pour construire celui de la 
          bonne classe ???
          
          \todo
            En fait on doit se doter d'une classe qui construit, i.e., une classe 
            fabricante, qu'on redéfinira dans les modules. Mais qui construira 
            l'objet de la classe fabricante ? :)
        */
      Planetoide* Construire(
        const Base::Association< Modele::Planetoide>& _planetoide) ;
  
    }
  }
}

#endif //_AFFICHAGE_IMPLANTATION_PLANETOIDE_H_
