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

  namespace Modele { 
    class Objet ;
    class Facette ;
  }

  namespace Affichage {

    class Objet ;
    class Facette ;
    
    /// Type des fonction de construction de facette.
    typedef 
    boost::function1<Facette*, const Base::Association<Modele::Facette>&>
    ConstructeurVue ;

    /// Le point de vue subjectif par rapport � un observateur.
    /*!
      C'est par exmple la vue � la premi�re personne d'un personnage.
      
      @par Type de classe :
      - Objet
      - Abstrait
    */
    class PointDeVue : public Base::PointDeVue 
    {
    public:

      /// Construit un point de vue.
      static PointDeVue* 
          Construire(const Base::Association<Modele::Objet>& _observateur) ;

      /// Le point de vue est celui affich�.
      virtual void Activer() = 0 ;

      /// Le point de vue n'est plus affich�.
      virtual void Desactiver() = 0 ;
 
      /// Initialise le point de vue
      virtual void Initialiser() = 0 ;

      /// Termine le point de vue
      virtual void Terminer() = 0 ;

      /// Demande au point de vue de d�truire une de ses vue.
      virtual void Detruire
        (const Base::Association<Base::Implantation::BaseVue>&) ;

      /// Destructeur de classe abstraite.
      virtual ~PointDeVue() ;

      /// Change l'observateur de la vue.
      virtual void ChangerObservateur
        (const Base::Association<Modele::Objet>& _observateur) = 0 ;

      /// La vue de l'observateur.
      Base::Association<Objet> AccesVueObservateur() const ;

      /// Retrouver une vue � partir du mod�le.
      Base::Association<Objet> RechercherVue
        (const Base::Association<Modele::Objet>& _objet) const ;


    
    protected:

    /*!
      @name Construction
    */
    // @{
      
      /// Constructeur.
      PointDeVue(const Base::Association<Modele::Objet>& _observateur) ;
      
      /// Constructeur.
      /*!
        Vu que lors d'un appel � un constructeur de classe abstraite, on ne 
        sait pas dans quelle sous classe on est, la construction se fait en 
        deux temps.
      */
      void Construire() ;
      
      /// Construit r�cursivement une structure de vue pour @c _modele.
      /*!
        Si ! this->EstVisible(_modele) renvoie NULL
        @todo Tester.
      */
      Objet* ConstruireVue(const Base::Association<Modele::Objet>& _modele) ;
      
      /// Vrai si l'objet doit �tre repr�sent� dans le point de vue.
      /*!
        @constraint
          Si objet1 n'est pas visible alors aucun de ses composants ne l'est
      */
      virtual Base::Booleen EstVisible
              (const Base::Association<Modele::Objet>& _modele) const = 0 ;

          
    // @}
    
      /// L'observateur.
      Base::Association<Modele::Objet> observateur ;

      /// L'observateur cot� affichage.
      Base::Association<Objet> vueObservateur ;

      Base::Booleen initialise ;
      
      /// Constructeurs des vues.
      static 
      Base::FonctionValeurValeur<
          std::pair<Base::Chaine,Base::Chaine>, 
          ConstructeurVue> constructeurs ;
      
      /// Enregistre @c _constructeur comme constructeur de @c _classeModele 
      /// dans @c _classePointDeVue.
      static void EnregistreConstruction(const Base::Chaine& _classeModele,
                                         const Base::Chaine& _classePointDeVue,
                                         ConstructeurVue _constructeur) ;
      
      template <class Modele, class PointDeVue> friend class EnregistrementVue ;
      friend class Objet ;
    };
    
    /// Indique que ClasseVue est la vue de ClasseModele dans ClassePointDeVue
    /*!
    @par Utilisation
      
      Dans le cpp d'une classe de Vue faire : 
      
        EnregistreVue(ClasseVue,ClasseModele,ClassePointDeVue) ;
        
    @example
      EnregistreVue(Affichage::Mobile,Modele::Mobile,Ogre::PointDeVue) ;
      
    
    @par Fonctionnement
      Exactement le m�me principe de fonctionnement que 
        CPPUNIT_TEST_SUITE_REGISTRATION
      
    */
    #define EnregistreVue(ClasseVue,ClasseModele,ClassePointDeVue)   \
      namespace {                                                    \
        Facette* construction(                                       \
                      const Base::Association<Modele::Facette>& _modele)\
        {                                                            \
          Base::Association<ClasseModele> temp(                       \
            * static_cast<ClasseModele*>( & (*_modele))) ;          \
          return new ClasseVue(temp) ;                            \
        }                                                            \
        EnregistrementVue<ClasseModele, ClassePointDeVue>           \
            temp(&construction) ;                                    \
      }                                                                
      
    template <class M, class P> class EnregistrementVue
    {
    public:
      
      /// Constructeur.
      /*!
        Ce constructeur est appel� � l'initialisation du module � cause de la 
        d�claration de variable statique dans la macro EnregistreVue.
        
        Le nom interne des classes M et P sert de cl� � l'enregistrement de la 
        fonction constructrice.
      */
      EnregistrementVue(ConstructeurVue constructeur)
      {
        
        Affichage::PointDeVue::EnregistreConstruction(typeid(M).name(),
                                                      typeid(P).name(),
                                                      constructeur) ;
      }
    };
    
          
  }
}


#endif
