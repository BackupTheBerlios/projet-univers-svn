/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_KERNEL_VIEW_POINT_H_
#define _PU_KERNEL_VIEW_POINT_H_

#include <vector>
#include <std>

#include <kernel/event.h>
#include <kernel/implementation/base_view.h>

namespace ProjetUnivers {
  namespace Kernel {
    
    

    /// Un point de vue est une observation coh�rente d'un mod�le de donn�es.
    /*!
      Un point de vue est un ensemble de vues. G�n�ralement, toutes ces vues 
      portent sur des mod�les reli�s les uns aux autres. 
      
      Ces vues doivent toutes avoir �t� rafraichies pour que le point de vue 
      puisse �tre affich�. 
      
      @par Exemples 
      - ce que voit un personnage
      - ce que d�tecte un capteur
    
      @par Utilisation 
      -# Cr�ation d'un point de vue
      -# Registerment des vues par ViewPoint::add
      -# Raffraichissement p�riodique par ViewPoint::Raffraichir
        
    */
    class ViewPoint 
    {
    public:

    /*!
      @name Construction
      
    */
    // @{

      /// Constructeur.
      ViewPoint() ;

      /// Ajoute une vue.
      void add(Implementation::KernelView* _vue) ;

      /// Enl�ve une vue.
      void remove(Implementation::BaseView* _vue) ;

    // @}
    /*!
      @name Utilisation
      
    */
    // @{

    
      /// Rafraichissement du point de vue.
      virtual void update() ;

      /// Demande au point de vue de d�truire la vue.
      virtual void destroy(Implementation::BaseView*) ;
    
    // @}
      
      /// Destructeur, d�truit les vues.
      virtual ~ViewPoint()
      {}

    protected:
    
      /// Les vues constituant ce point de vue.
      std::set<Implementation::BaseView*> views ;
    
      
    private:

    /*!
      @name Pour la gestion des vues
      
      
    */
    // @{
    
      /// Marque _vue comme devant �tre rafraichie.
      void markToUdate(const Association<Implementation::KernelView> _vue,
                       const Event& _evenement) ;
    
      /// Marque _vue comme devant �tre supprim�e.
      void markToDestroy(const Association<Implementation::KernelView> _vue) ;
      
    //@}

      /// Les vues qui doivent �tre d�truites au prochain tour.
      /*!
      C'est une collection 
      -# ordonn�e (car l'ordre est important pour la destruction) en effet on 
         suppose que l'ordre de destruction des objets du mod�le respecte la 
         composition (ce qui est le cas).
      -# pour le reste, il serait plus judicieux de mettre un vecteur sans 
         d�salocation (pour ne pas r�allouer l'espace allou�) �tant donn� que 
         le nombre d'objets � d�truire sera en pratique "born�".
      */
      std::vector<Implementation::KernelView*> viewsToDestroy ;
      
      
      struct Update
      {
        Update(const Association<Implementation::KernelView>& _view,
                         const Event& _event)
        : view(_view), event(_event)
        {}

        bool operator==(const Update& _r) const
        {
          return view == _r.view && event == _r.event ;
        }
          
        Implementation::BaseView* view ;
        Event event ;
      };
      
      /// Les rafraichissements � effectuer au prochain tour.
      /*!
        N'importe quelles des vues constituant r�cursivement ce point de vue.
      */
      std::set<Update> rafraichissements ;
      
      friend class Implementation::BaseView ;
      
    };

    
  }
}


#endif

