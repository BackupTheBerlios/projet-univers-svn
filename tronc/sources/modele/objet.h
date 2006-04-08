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

#ifndef _PU_MODELE_OBJET_H_
#define _PU_MODELE_OBJET_H_

#include <base/chaine.h>
#include <base/ensemble_association.h>

#include <modele/nom.h>
#include <modele/identificateur.h>
#include <modele/attribut_inexistant.h>

namespace ProjetUnivers {

  namespace Modele {
  
    class EnsembleDObjets ;
    class Valeur ;
    
    /// Un objet du jeu.
    class Objet {
    public:
  
      /// Construction d'un objet appartenants à certains ensembles.
      static 
        Identificateur 
        ConstruireObjet(const Base::EnsembleAssociation<EnsembleDObjets>& _types) ;

    /*!
      @name Affichage
      
      Construit une chaine XML représentant l'objet.
    */
    // @{

      /// Chaine représentant une référence à l'objet.
      virtual Base::Chaine AfficherReference() const ;
      
      /// Chaine représentant la définition de l'objet.      
      virtual Base::Chaine AfficherDefinition() const ;

    // @}
      
//      /*!
//        @name Accès aux attributs
//      */
//      // @{
//      
//      /// Accès à la valeur d'un attribut.
//      virtual Valeur AccesAttribut(const Base::Chaine& _nomAttribut) const  
//      throw(AttributInexistant) = 0 ;
//
//      /// Modifie la valeur d'un attribut.      
//      virtual void ModifierAttribut(const Base::Chaine& _nomAttribut,
//                                    const Valeur& _nouvelleValeur) = 0 ;
//      
//      // @}
//      /*!
//        @name Accès aux ensembles
//      */
//      // @{
//      
//      virtual Base::Booleen 
//              EstDans(const Base::Association<EnsembleDObjets>& _ensemble) 
//              const = 0 ;
//      
//      // @}
      
      /// Destructeur de classe abstraite.
      virtual ~Objet() ;

    protected:

      /// Constructeurs de classe abstraite.  
      Objet() ;
      Objet(const Nom&) ;
    
      
      /// Accès aux attributs locaux
      
      Valeur 
      AccesAttributLocal(const Base::Chaine& _nomAttribut) const  
      throw(AttributInexistant) ;
      
      void ModifierAttributLocal(const Base::Chaine& _nomAttribut,
                                    const Valeur& _nouvelleValeur) ;
      
    // @}
    /*!
      @name Accès aux ensembles
    */
    // @{
      
      Base::Booleen 
      EstDansLocal(const Base::Association<EnsembleDObjets>& _ensemble) const ;
    
    
    // @}
    /*!
      @name Attributs
    */
    // @{
       
      /// Identificateur de l'objet.
      Identificateur identificateur ;

      /// Nom de l'objet.
      /*!
        Pas forcément unique.
      */
      Nom nom ;

    /*!
     * 
    
      /// Ensembles d'appartenance de l'objet.
      Base::EnsembleAssociation<EnsembleDObjets> types ;
      
      /// Les valeurs des attributs de l'objet qui ne sont pas codées en dur.
      Base::FonctionValeurValeur<Base::Chaine,Valeur> champs ;
      
      /// Ensembles d'appartenance de l'objet.
      Base::EnsembleAssociation<EnsembleDObjet> ensembles ;
      */
      
      // @}
      
    };  
  } 
  
}


#endif // _PU_MODELE_OBJET_H_
