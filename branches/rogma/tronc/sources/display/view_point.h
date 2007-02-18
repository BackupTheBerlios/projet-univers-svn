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

#ifndef _PU_DISPLAY_VIEW_POINT_H_
#define _PU_DISPLAY_VIEW_POINT_H_

#include <kernel/log.h>

#include <boost/function.hpp>

#include <kernel/view_point.h>


namespace ProjetUnivers {

  namespace Model { 
    class Object ;
    class Trait ;
  }

  namespace Display {

    class Object ;
    class Trait ;
    
    /// Type des fonction de construction de facette.
    typedef boost::function1<Trait*, Model::Trait*> ViewBuilder ;

    /// Le point de vue subjectif par rapport à un observateur.
    /*!
      C'est par exmple la vue à la première personne d'un personnage.
      
      @par Type de classe :
      - Object
      - Abstrait
    */
    class ViewPoint : public Kernel::ViewPoint 
    {
    public:

      /// Construit un point de vue.
      static ViewPoint* build(Model::Object* _observer) ;

      /// Le point de vue est celui affiché.
      virtual void activate() = 0 ;

      /// Le point de vue n'est plus affiché.
      virtual void desactivate() = 0 ;
 
      /// Initialise le point de vue
      virtual void init() = 0 ;

      /// Termine le point de vue
      virtual void close() = 0 ;

      /// Demande au point de vue de détruire une de ses vue.
      virtual void destroy
        (Kernel::Implementation::KernelView*) ;

      /// Destructeur de classe abstraite.
      virtual ~ViewPoint() ;

      /// Change l'observateur de la vue.
      virtual void changeObserver(Model::Object* _observer) = 0 ;

      /// La vue de l'observateur.
      Object* getObserverView() const ;

      /// Retrouver une vue à partir du modèle.
      Object* getView(Model::Object* _model) const ;


    
    protected:

    /*!
      @name Construction
    */
    // @{
      
      /// Constructeur.
      ViewPoint(Model::Object* _observer) ;
      
      /// Constructeur.
      /*!
        Vu que lors d'un appel à un constructeur de classe abstraite, on ne 
        sait pas dans quelle sous classe on est, la construction se fait en 
        deux temps.
      */
      void build() ;
      
      /// Construit récursivement une structure de vue pour @c _modele.
      /*!
        Si ! this->isVisible(_modele) renvoie NULL
        @todo Tester.
      */
      Object* buildView(Model::Object* _model) ;
      
      /// Vrai si l'objet doit être représenté dans le point de vue.
      /*!
        @constraint
          Si objet1 n'est pas visible alors aucun de ses composants ne l'est
      */
      virtual bool isVisible(Model::Object* _model) const = 0 ;

          
    // @}
    
      /// L'observateur.
      Model::Object* observer ;

      /// L'observateur coté affichage.
      Object* observerView ;

      bool initialised ;
      
      /// Constructeurs des vues.
      static std::map<std::pair<std::string,std::string>,
                      ViewBuilder> builders ;
      
      /// Register @c _constructeur comme constructeur de @c _classeModel 
      /// dans @c _classeViewPoint.
      static void registerbuilder(const std::string& _classModel,
                                  const std::string& _classViewPoint,
                                  ViewBuilder _builder) ;
      
      template <class Model, class ViewPoint> friend class ViewRegistration ;
      friend class Object ;
    };
    
    /// Indique que ClasseView est la vue de ClasseModel dans ClasseViewPoint
    /*!
    @par Utilisation
      
      Dans le cpp d'une classe de View faire : 
      
        RegisterView(ClasseView,ClasseModel,ClasseViewPoint) ;
        
    @example
      RegisterView(Display::Mobile,Model::Mobile,Ogre::ViewPoint) ;
      
    
    @par Fonctionnement
      Exactement le même principe de fonctionnement que 
        CPPUNIT_TEST_SUITE_REGISTRATION
      
    */
    #define registerView(ClassView,ClassModel,ClassViewPoint)   \
      namespace {                                               \
        Trait* build(Model::Trait* _model)                      \
        {                                                       \
          ClassModel* temp(static_cast<ClassModel*>( _model))) ;\
          return new ClassView(temp) ;                          \
        }                                                       \
        ViewRegistration<ClassModel, ClassViewPoint>            \
            temp(&build) ;                                      \
      }                                                                
      
    template <class M, class P> class ViewRegistration
    {
    public:
      
      /// Constructeur.
      /*!
        Ce constructeur est appelé à l'initialisation du module à cause de la 
        déclaration de variable statique dans la macro RegisterView.
        
        Le nom interne des classes M et P sert de clé à l'enregistrement de la 
        fonction constructrice.
      */
      ViewRegistration(ViewBuilder builder)
      {
        
        Display::ViewPoint::registerBuilder(typeid(M).name(),
                                            typeid(P).name(),
                                            builder) ;
      }
    };
    
          
  }
}


#endif
