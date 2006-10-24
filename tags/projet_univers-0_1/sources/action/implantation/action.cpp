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


#include <base/implantation/liste_valeur.h>

#include <modele/modele.h>
#include <modele/objet.h>
#include <modele/positionne.h>

#include <action/action.h>

namespace ProjetUnivers {
  
  namespace Action 
  {

    Base::Booleen finished ;

    struct Action
    {
      /// nom de l'action
      Base::Chaine nom ;
      
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
        Base::Association<Modele::Objet> observateur(Modele::AccesObjet("Observateur")) ;
        Base::Association<Modele::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Modele::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Ogre::Quaternion(sqrt(0.5),0,sqrt(0.5),0))) ;
            
        
      }
      else if (_action.nom == "Bas")
      {
        Base::Association<Modele::Objet> observateur(Modele::AccesObjet("Observateur")) ;
        Base::Association<Modele::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Modele::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Ogre::Quaternion(sqrt(0.5),0,-sqrt(0.5),0))) ;
        
      }
      else if (_action.nom == "Droite")
      {
        Base::Association<Modele::Objet> observateur(Modele::AccesObjet("Observateur")) ;
        Base::Association<Modele::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Modele::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Ogre::Quaternion(sqrt(0.5),-sqrt(0.5),0,0))) ;
        
      }
      else if (_action.nom == "Gauche")
      {
        Base::Association<Modele::Objet> observateur(Modele::AccesObjet("Observateur")) ;
        Base::Association<Modele::Positionne> positionne(*observateur) ;
        
        positionne->ModifierOrientation(
          Modele::Orientation(
            positionne->AccesOrientation().AccesQuaternion() 
            * 
            Ogre::Quaternion(sqrt(0.5),sqrt(0.5),0,0))) ;
        
        
      }
      else if (_action.nom == "RegarderVaisseau")
      {
        Base::Association<Modele::Objet> observateur(Modele::AccesObjet("Observateur")) ;
        Base::Association<Modele::Positionne> observateurPositionne(*observateur) ;

        Base::Association<Modele::Objet> vaisseau(Modele::AccesObjet("Vaisseau")) ;
        Base::Association<Modele::Positionne> vaisseauPositionne(*vaisseau) ;

        
        
      }
      
      
    }
    
    
    void Initialiser()
    {
      actions.Vider() ;
      finished = Base::FAUX ;
    }

    void Terminer()
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

    void Ajouter(const Base::Chaine& _nomAction)
    {
      Action temp ;
      temp.nom = _nomAction ;
      actions.AjouterEnQueue(temp) ;
    }

    Base::Booleen Termine()
    {
      return finished ;
    }


  }
}

