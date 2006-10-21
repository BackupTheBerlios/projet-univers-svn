/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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
#include <base/iterateur_ensemble_composition.h>

#include <affichage/exception.h>
#include <affichage/point_de_vue.h>

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
        Base::Traceur::MessageInterne("Entering Affichage::Objet::Objet") ;
        
        this->pointDeVue = _pointDeVue ;

        Base::Traceur::MessageInterne("Leaving Affichage::Objet::Objet") ;
      }
          
      /// Initialise les facettes de la vue puis ses fils
      void Objet::Initialiser() 
      {

        Base::Traceur::MessageInterne("Entering Objet::Initialiser") ;
        Base::Traceur::MessageInterne("Initialising facettes") ;

        for(Base::IterateurEnsembleAssociation<Facette> facette(ensembleFacettes) ;
            facette.Valide() ;
            ++facette)
        {
          facette->Initialiser() ;
        }

        Base::Traceur::MessageInterne("Initialising sub-objects") ;
        
        for(Base::IterateurEnsembleComposition<Objet> fils(this->contenu) ;
            fils.Valide() ;
            ++fils)
        {
          fils->Initialiser() ;
        }
      }
      
      void Objet::Terminer()
      {
        
      }

      void Objet::Raffraichir()
      {
        /// il faut voir si de nouvelles facettes sont apparues
        
        /// il faut regarder si les liens de parentés ont changés
      }


      Base::Association<Objet> Objet::Ajouter(Objet* _contenu)
      {
        if (_contenu)
        {
          _contenu->conteneur = *this ;
          this->contenu.Ajouter(_contenu) ;
        }
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
        _facette->pointDeVue = this->pointDeVue ;
        
        ensembleFacettes.Ajouter(temporaire) ;
        
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

