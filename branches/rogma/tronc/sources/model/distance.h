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

#ifndef _PU_MODELE_DISTANCE_H_
#define _PU_MODELE_DISTANCE_H_

#include <base/types.h>

namespace ProjetUnivers {

  namespace Model {

    namespace Test
    {
      class TestDistance ;
    }
      
    /// Une distance éloignant deux points.
    
    /*!  
      La distance est stockée dans n'importe quelle unité pour des raisons de 
      précision. Ainsi, de grandes distances pouront être stokées en parsecs et
      de petites distances en mètres.

      Type de classe :
      - Valeur
    */
    class Distance 
    {
    public:
    
    // ********************
    /// @name Constructeurs
    // ********************
    // @{   
    
      /// Les différentes unités de mesure utilisée.
      typedef enum {
        _Metre,
        _AnneeLumiere, 
        _Parsec 
      } Unite ;

      /// Distance nulle.
      Distance() ;
      
      /// Constructeur de copie.
      Distance(const Distance&) ;

      /// Constructeur unité, valeur
      Distance(const Unite&, const Base::Reel&) ;
    
      /// Calcul
      Distance operator +(const Distance&) const ;

      /// Calcul
      Distance operator -(const Distance&) const ;



      
    // @}
    // ******************
    /// @name Conversions
    // ******************
    // @{
      

      /// Convertit la distance en parsecs.
      Base::Reel Parsec() const ; 
      
      /// Convertit la distance en mètres.
      Base::Reel Metre() const ; 
      
      /// Convertit la distance en années lumières.
      Base::Reel AnneeLumiere() const ; 

    
    // @}    
    // ************
    /// @name Accès
    // ************
    // @{
      
      

      /// Comparaison avec une autre distance. 
      /*!
        Plus ou moins précis en fonction de la Distance : deux distances 
        importantes, peuvent être considérées comme égales alors qu'elles sont 
        véritablement différentes.
      */
      // BooleenEtendu Comparer(const Distance&) const ;
    
    // @}
      
    private:
    

      /// Valeur.
      Base::Reel distance ;
  
      /// Unité de la distance
      Unite unite ;    
  
      friend Base::Booleen operator<=(Distance::Unite, Distance::Unite) ;
                            
      friend class ::ProjetUnivers::Model::Test::TestDistance ;
    };

    Base::Booleen operator<=(Distance::Unite,Distance::Unite) ;


  }
}




#endif
