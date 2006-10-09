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

//#include <base/iterateur_fonction_composition_valeur_objet.h>

#include <base/traceur.h>
#include <base/erreur.h>

#include <affichage/exception.h>
#include <affichage/objet.h>


namespace ProjetUnivers {
  namespace Affichage {


    /*!
      @name Construction
    */
    // @{

      /// Constructeur.
      Objet::Objet(const Base::Association<Modele::Objet>& _objet, 
                   const Base::Association<PointDeVue>& _pointDeVue)
      : Base::Vue<Modele::Objet>(_objet)
      {
        /// on a besoin d'un constructeur de vue
        /*!
          Quelque chose qui permet à chaque classe de vue de s'enregistrer 
          auprès d'une facette
          
          dans le .cpp de la vue : 
          
          DECLARE_VUE(Vue, Modele, PointDeVue) ;
          
          qui ajoute dans une map 
          

        */
        Base::Traceur::MessageInterne("Entering Affichage::Objet::Objet") ;
        Base::Traceur::MessageInterne("Leaving Affichage::Objet::Objet") ;
        
        
        
      }
          
      /// Initialise le point de vue
      void Objet::Initialiser() 
      {
//        for(Base::IterateurFonctionCompositionValeurObjet<Base::Chaine, Facette> facette(facettes) ;
//            facette.Valide() ;
//            ++facette)
//        {
//          facette->Initialiser() ;
//        }
      }
      
      void Objet::Terminer()
      {
        
      }

      Base::Association<Objet> Objet::Ajouter(Objet* _contenu)
      {
        this->contenu.Ajouter(_contenu) ;
      }
    
      Base::Association<Objet> Objet::Ajouter(Facette* _facette)
      {
        /// Composition temporaire pour détruire l'objet au cas où.
        Base::Composition<Facette> temporaire(_facette) ;
        
        /// erreur si l'objet a déjà une facette de ce type là
        VerifieCondition(facettes[typeid(*_facette).name()] 
                         == 
                         Base::Association<Facette>(), 
                         Exception("facette déjà existante")) ;
        
        
        _facette->objet = *this ;
        /// on range les facettes en fonction de leur classe
          facettes.Ajouter(typeid(*_facette).name(), temporaire.Liberer()) ;
        }
 
      /// Acces au conteneur de la vue
      Base::Association<Objet> Objet::AccesConteneur() const
      {
        return this->conteneur ;
      }
 
  }
}

