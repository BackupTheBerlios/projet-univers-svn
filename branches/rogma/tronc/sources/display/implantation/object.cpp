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
  namespace Display {


    /*!
      @name Construction
    */
    // @{

      /// Constructeur.
      Object::Object(const Base::Association<Model::Object>& _objet, 
                   const Base::Association<ViewPoint>& _pointDeVue)
      : Base::Vue<Model::Object>(_objet)
      {
        Base::Traceur::MessageInterne("Entering Display::Object::Object") ;
        
        this->pointDeVue = _pointDeVue ;

        Base::Traceur::MessageInterne("Leaving Display::Object::Object") ;
      }
          
      /// Initialise les facettes de la vue puis ses fils
      void Object::init() 
      {

        Base::Traceur::MessageInterne("Entering Object::init") ;
        Base::Traceur::MessageInterne("Initialising facettes") ;

        for(Base::IterateurEnsembleAssociation<Trait> facette(ensembleTraits) ;
            facette.Valide() ;
            ++facette)
        {
          facette->init() ;
        }

        Base::Traceur::MessageInterne("Initialising sub-objects") ;
        
        for(Base::IterateurEnsembleComposition<Object> fils(this->contenu) ;
            fils.Valide() ;
            ++fils)
        {
          fils->init() ;
        }
      }
      
      void Object::close()
      {
        
      }

      void Object::update(const Base::Evenement& _evenement)
      {
        /// il faut voir si de nouvelles facettes sont apparues

        /// il faut regarder si les liens de parentés ont changés
        if (_evenement.nom == "fils") 
        {
          switch(_evenement.action)
          {
          case Base::Evenement::Ajout :
          {
            Base::Association<Model::Object> nouveau(
              *dynamic_cast<Model::Object*>(&*_evenement.parametre)) ;
            
            Base::Association<Object> nouvelle_vue(  
              this->add(this->AccesViewPoint()->ConstruireVue(nouveau))) ;
            
            nouvelle_vue->init() ;
                          
          }          
          break ;
          case Base::Evenement::Suppression :
          {
            /// le paramètre a déjà été supprimé...
            Base::Association<Model::Object> supprime(
              *dynamic_cast<Model::Object*>(&*_evenement.parametre)) ;

            /// récupérer la vue correspondant à cet 
          }          
          break ;
          default:
            break ;
          }
        }
      }


      Base::Association<Object> Object::add(Object* _contenu)
      {
        if (_contenu)
        {
          _contenu->conteneur = *this ;
          this->contenu.add(_contenu) ;
          return *_contenu ;
        }
        
        return Base::Association<Object>() ;
      }
    
      Base::Association<Trait> Object::add(Trait* _facette)
      {
        /// Composition temporaire pour détruire l'objet au cas où.
        Base::Composition<Trait> temporaire(_facette) ;
        
        /// erreur si l'objet a déjà une facette de ce type là
        VerifieCondition(facettes[typeid(*_facette).name()] 
                         == 
                         Base::Association<Trait>(), 
                         Exception("facette déjà existante")) ;
        
        Base::Traceur::MessageInterne(std::string("registering facette ") + 
            typeid(*_facette).name()) ;
        
        _facette->objet = *this ;
        _facette->pointDeVue = this->pointDeVue ;
        
        ensembleTraits.add(temporaire) ;
        
        /// on range les facettes en fonction de leur classe
        facettes.add(typeid(*_facette).name(), temporaire.Liberer()) ;
        
        return *_facette ;
      }
      
      void Object::remove(const Base::Association<Object>& _objet)
      {
        this->contenu.remove(_objet) ;
      }
      
      void Object::remove(const Base::Association<Trait>& _facette)
      {
        Base::Traceur::MessageInterne(typeid(*_facette).name()) ;
        
        _facette->close() ;
        this->ensembleTraits.remove(_facette) ;
        Trait* element = this->facettes.remove(typeid(*_facette).name()) ;
        delete element ;
      }
      
 
 
      /// Acces au conteneur de la vue
      Base::Association<Object> Object::AccesConteneur() const
      {
        return this->conteneur ;
      }
 
      Base::Association<ViewPoint> Object::AccesViewPoint() const
      {
        ViewPoint* temp = static_cast<ViewPoint*>( &(*this->pointDeVue));
        return *temp ;
      }

      Base::Association<Object> Object::RechercherFils
        (const Base::Association<Model::Object>& _objet) const
      {
        for(Base::IterateurEnsembleComposition<Object> fils(this->contenu) ;
            fils.Valide() ;
            ++fils)
        {
          if (fils->AccesObserve() == _objet)
          {
            return fils ;
          }
        }
        
        throw Exception("fils non trouve") ;        
       }

 
  }
}

