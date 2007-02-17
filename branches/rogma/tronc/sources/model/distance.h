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
      
    /// Une distance �loignant deux points.
    
    /*!  
      La distance est stock�e dans n'importe quelle unit� pour des raisons de 
      pr�cision. Ainsi, de grandes distances pouront �tre stok�es en parsecs et
      de petites distances en m�tres.

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
    
      /// Les diff�rentes unit�s de mesure utilis�e.
      typedef enum {
        _Metre,
        _AnneeLumiere, 
        _Parsec 
      } Unite ;

      /// Distance nulle.
      Distance() ;
      
      /// Constructeur de copie.
      Distance(const Distance&) ;

      /// Constructeur unit�, valeur
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
      
      /// Convertit la distance en m�tres.
      Base::Reel Metre() const ; 
      
      /// Convertit la distance en ann�es lumi�res.
      Base::Reel AnneeLumiere() const ; 

    
    // @}    
    // ************
    /// @name Acc�s
    // ************
    // @{
      
      

      /// Comparaison avec une autre distance. 
      /*!
        Plus ou moins pr�cis en fonction de la Distance : deux distances 
        importantes, peuvent �tre consid�r�es comme �gales alors qu'elles sont 
        v�ritablement diff�rentes.
      */
      // BooleenEtendu Comparer(const Distance&) const ;
    
    // @}
      
    private:
    

      /// Valeur.
      Base::Reel distance ;
  
      /// Unit� de la distance
      Unite unite ;    
  
      friend Base::Booleen operator<=(Distance::Unite, Distance::Unite) ;
                            
      friend class ::ProjetUnivers::Model::Test::TestDistance ;
    };

    Base::Booleen operator<=(Distance::Unite,Distance::Unite) ;


  }
}




#endif
