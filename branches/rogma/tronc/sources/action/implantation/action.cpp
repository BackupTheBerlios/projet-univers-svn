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

#include <OgreVector3.h>

#include <base/implantation/liste_valeur.h>
#include <base/traceur.h>

#include <modele/modele.h>
#include <modele/objet.h>
#include <modele/positionne.h>
#include <modele/solide.h>
#include <modele/systeme_stellaire.h>

#include <action/action.h>

using namespace ProjetUnivers::Model ;
using namespace ::Ogre ;

namespace ProjetUnivers {
  namespace Action {

    Base::Booleen finished ;

    struct Action
    {
      /// nom de l'action
      std::string nom ;
      
      /// Moment de l'action
      
    };

    /// Actions à traiter
    /*!
    */
    Base::Implantation::ListeValeur<Action> actions ;
    
    
    void Traiter(const Action& _action)
    {
      if (_action.nom == "Sortie")
      {
        finished = Base::VRAI ;
      }
      else if (_action.nom == "Haut")
      {
        Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
        Base::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::NEGATIVE_UNIT_X))) ;
            
        
      }
      else if (_action.nom == "Bas")
      {
        Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
        Base::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::UNIT_X))) ;
        
      }
      else if (_action.nom == "Droite")
      {
        Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
        Base::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::NEGATIVE_UNIT_Y))) ;
        
      }
      else if (_action.nom == "Gauche")
      {
        Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
        Base::Association<Model::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Model::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Quaternion(Degree(45),Vector3::UNIT_Y))) ;
        
        
      }
      else if (_action.nom == "RegarderVaisseau")
      {
        /*!
          @par Etat 
            planning...
        */
        Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
        Base::Association<Model::Positionne> observateurPositionne(*observateur) ;

        Base::Association<Model::Object> vaisseau(Model::AccesObject("Vaisseau")) ;
        Base::Association<Model::Positionne> vaisseauPositionne(*vaisseau) ;
        
      }
      else if (_action.nom == "CreerObject")
      {
        Base::Association<Model::Object> observateur(Model::AccesObject("Observateur")) ;
        
        Base::Association<Model::Object> systeme(
          observateur->AccesParent<Model::SystemeStellaire>()->AccesObject()) ;
        
        Base::Association<Object> vaisseau = systeme->add(new Object(Nom("Vaisseau2"))) ;
        vaisseau->add(new Positionne(Position(Distance(Distance::_Metre, 0),
                                                  Distance(Distance::_Metre, 500000),
                                                  Distance(Distance::_Metre, 0)) )) ;
        
        vaisseau->add(new Solide(Model3D("razor.mesh"))) ;
        
      }
      else if (_action.nom == "destroyObject")
      {
        Base::Association<Model::Object> vaisseau(Model::AccesObject("Vaisseau2")) ;
        Base::Traceur::MessageInterne("perparing to destroy object") ;
        Model::remove(vaisseau) ;
      }
    }
    
    
    void init()
    {
      actions.Vider() ;
      finished = Base::FAUX ;
    }

    void close()
    {
      actions.Vider() ;
    }

    void Traiter()
    {
      for(Base::Implantation::IterateurListeValeur<Action> action(actions) ;
          action.Valide() ;
          ++action)
      {
        Traiter(action) ;
      }
      
      actions.Vider() ;
    }

    void add(const std::string& _nomAction)
    {
      Action temp ;
      temp.nom = _nomAction ;
      actions.addEnQueue(temp) ;
    }

    Base::Booleen Termine()
    {
      return finished ;
    }


  }
}

