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

#ifndef _PU_MODEL_DISTANCE_H_
#define _PU_MODEL_DISTANCE_H_


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
        _Meter,
        _LightYear, 
        _Parsec 
      } Unit ;

      /// Distance nulle.
      Distance() ;
      
      /// Constructeur de copie.
      Distance(const Distance&) ;

      /// Constructeur unit�, valeur
      Distance(const Unit&, const float&) ;
    
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
      float Parsec() const ; 
      
      /// Convertit la distance en m�tres.
      float Meter() const ; 
      
      /// Convertit la distance en ann�es lumi�res.
      float LightYear() const ; 

    
    // @}    
    // ************
    /// @name Acc�s
    // ************
    // @{
      
    
    // @}
      
    private:
    

      /// Valeur.
      float distance ;
  
      /// Unit� de la distance
      Unit unit ;    
  
      friend bool operator<=(Distance::Unit, Distance::Unit) ;
                            
      friend class ::ProjetUnivers::Model::Test::TestDistance ;
    };

    bool operator<=(Distance::Unit,Distance::Unit) ;


  }
}




#endif
