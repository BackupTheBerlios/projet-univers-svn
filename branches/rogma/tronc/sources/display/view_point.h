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

#ifndef _PU_AFFICHAGE_POINT_DE_VUE_H_
#define _PU_AFFICHAGE_POINT_DE_VUE_H_

#include <base/traceur.h>

#include <boost/function.hpp>

#include <base/fonction_valeur_valeur.h>
#include <base/association.h>
#include <base/point_de_vue.h>
#include <base/chaine.h>


namespace ProjetUnivers {

  namespace Model { 
    class Object ;
    class Trait ;
  }

  namespace Display {

    class Object ;
    class Trait ;
    
    /// Type des fonction de construction de facette.
    typedef 
    boost::function1<Trait*, const Base::Association<Model::Trait>&>
    ConstructeurVue ;

    /// Le point de vue subjectif par rapport à un observateur.
    /*!
      C'est par exmple la vue à la première personne d'un personnage.
      
      @par Type de classe :
      - Object
      - Abstrait
    */
    class ViewPoint : public Base::ViewPoint 
    {
    public:

      /// Construit un point de vue.
      static ViewPoint* 
          Construire(const Base::Association<Model::Object>& _observateur) ;

      /// Le point de vue est celui affiché.
      virtual void Activer() = 0 ;

      /// Le point de vue n'est plus affiché.
      virtual void Desactiver() = 0 ;
 
      /// Initialise le point de vue
      virtual void init() = 0 ;

      /// Termine le point de vue
      virtual void close() = 0 ;

      /// Demande au point de vue de détruire une de ses vue.
      virtual void destroy
        (const Base::Association<Base::Implantation::BaseVue>&) ;

      /// Destructeur de classe abstraite.
      virtual ~ViewPoint() ;

      /// Change l'observateur de la vue.
      virtual void ChangerObservateur
        (const Base::Association<Model::Object>& _observateur) = 0 ;

      /// La vue de l'observateur.
      Base::Association<Object> AccesVueObservateur() const ;

      /// Retrouver une vue à partir du modèle.
      Base::Association<Object> RechercherVue
        (const Base::Association<Model::Object>& _objet) const ;


    
    protected:

    /*!
      @name Construction
    */
    // @{
      
      /// Constructeur.
      ViewPoint(const Base::Association<Model::Object>& _observateur) ;
      
      /// Constructeur.
      /*!
        Vu que lors d'un appel à un constructeur de classe abstraite, on ne 
        sait pas dans quelle sous classe on est, la construction se fait en 
        deux temps.
      */
      void Construire() ;
      
      /// Construit récursivement une structure de vue pour @c _modele.
      /*!
        Si ! this->EstVisible(_modele) renvoie NULL
        @todo Tester.
      */
      Object* ConstruireVue(const Base::Association<Model::Object>& _modele) ;
      
      /// Vrai si l'objet doit être représenté dans le point de vue.
      /*!
        @constraint
          Si objet1 n'est pas visible alors aucun de ses composants ne l'est
      */
      virtual Base::Booleen EstVisible
              (const Base::Association<Model::Object>& _modele) const = 0 ;

          
    // @}
    
      /// L'observateur.
      Base::Association<Model::Object> observateur ;

      /// L'observateur coté affichage.
      Base::Association<Object> vueObservateur ;

      Base::Booleen initialise ;
      
      /// Constructeurs des vues.
      static 
      Base::FonctionValeurValeur<
          std::pair<std::string,std::string>, 
          ConstructeurVue> constructeurs ;
      
      /// Enregistre @c _constructeur comme constructeur de @c _classeModel 
      /// dans @c _classeViewPoint.
      static void EnregistreConstruction(const std::string& _classeModel,
                                         const std::string& _classeViewPoint,
                                         ConstructeurVue _constructeur) ;
      
      template <class Model, class ViewPoint> friend class EnregistrementVue ;
      friend class Object ;
    };
    
    /// Indique que ClasseVue est la vue de ClasseModel dans ClasseViewPoint
    /*!
    @par Utilisation
      
      Dans le cpp d'une classe de Vue faire : 
      
        EnregistreVue(ClasseVue,ClasseModel,ClasseViewPoint) ;
        
    @example
      EnregistreVue(Display::Mobile,Model::Mobile,Ogre::ViewPoint) ;
      
    
    @par Fonctionnement
      Exactement le même principe de fonctionnement que 
        CPPUNIT_TEST_SUITE_REGISTRATION
      
    */
    #define EnregistreVue(ClasseVue,ClasseModel,ClasseViewPoint)   \
      namespace {                                                    \
        Trait* construction(                                       \
                      const Base::Association<Model::Trait>& _modele)\
        {                                                            \
          Base::Association<ClasseModel> temp(                       \
            * static_cast<ClasseModel*>( & (*_modele))) ;          \
          return new ClasseVue(temp) ;                            \
        }                                                            \
        EnregistrementVue<ClasseModel, ClasseViewPoint>           \
            temp(&construction) ;                                    \
      }                                                                
      
    template <class M, class P> class EnregistrementVue
    {
    public:
      
      /// Constructeur.
      /*!
        Ce constructeur est appelé à l'initialisation du module à cause de la 
        déclaration de variable statique dans la macro EnregistreVue.
        
        Le nom interne des classes M et P sert de clé à l'enregistrement de la 
        fonction constructrice.
      */
      EnregistrementVue(ConstructeurVue constructeur)
      {
        
        Display::ViewPoint::EnregistreConstruction(typeid(M).name(),
                                                      typeid(P).name(),
                                                      constructeur) ;
      }
    };
    
          
  }
}


#endif
