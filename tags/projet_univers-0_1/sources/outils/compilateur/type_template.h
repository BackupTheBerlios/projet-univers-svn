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



#ifndef _PU_COMPILATEUR_TYPE_TEMPLATE_H_
#define _PU_COMPILATEUR_TYPE_TEMPLATE_H_

#include <opencxx/TypeInfo.h>
#include <opencxx/TemplateClass.h>


#include <outils/compilateur/type.h>

#include <base/implantation/liste_composition.h>



namespace ProjetUnivers {

  namespace Outils {
      
    namespace Compilateur 
    {
  
      class ParametreTemplate ;

      /// Les diff�rents templates du module Base
      enum BaseTemplate
      {
        NonPrisEnCompte,
        Association,
        Composition,
        EnsembleAssociation,
        EnsembleComposition,
        EnsembleValeur,
        FonctionObjetValeur,
        FonctionCompositionObjetObjet,
        FonctionAssociationObjetObjet,
        FonctionCompositionValeurObjet,
        FonctionAssociationValeurObjet
      } ;
      
      /// Type des templates C++.
      class TypeTemplate : public Type
      {
      public:
      
        /// Faux constructeur.
        static TypeTemplate* Construire(Opencxx::TypeInfo& informationType,
                                        Opencxx::Environment* environement) ;

        /// Initialisation de la structure.
        virtual void Initialiser() ;
        
        /// Determine si ce type est un type autoris� pour un attribut.
        /*!
          Ce type est un type autoris� pour un attribut si c'est une des 
          classes suivantes :
          
          - ProjetUnivers::Base::Association< OBJET >
          
          ...

        */
        virtual Base::Booleen TypeAttributCorrect() const ;

        virtual Base::Booleen TypeParametreCorrect() const ;      

        /// Transforme en chaine pour l'affichage.
        virtual Base::Chaine Afficher() const ;


      private:



        /*!
          @name Outils de construction
        */        
        //@{

      
        /// Constructeur  
        TypeTemplate(
          Opencxx::TemplateClass* _ClassTemplate,
          Opencxx::Ptree* _parametres) ;

        /// Constructeur  
        TypeTemplate(Opencxx::TemplateClass* _ClassTemplate) ;


        static TypeTemplate* IdentifierTypeTemplate
                    (Opencxx::TypeInfo informationType, 
                     Opencxx::Environment* environement) ;

        static TypeTemplate* IdentifierParcoursNamespace
                  (Opencxx::Ptree* type, Opencxx::Environment* environement) ;
            
             
        //@}
        /*!
          @name Introspection
        */        
        //@{





        /// Template de base.
        BaseTemplate TemplateDeBase() const ;

        /// Vrai si le template fait partie de ::ProjetUnivers::Base.
        Base::Booleen NamespaceProjetUniversBase() const ;
        
        virtual Base::Booleen Valeur() const ;

        virtual Base::Booleen Objet() const ;

        /// Vrai si le type repr�sente une composition.
        Base::Booleen EstComposition() const ;


        //@}
        /*!
          @name Attributs
        */        
        //@{
        
        /// Classe template
        Opencxx::TemplateClass* classeTemplate ;
        
        /// Les param�tres.
        Base::Implantation::ListeComposition<ParametreTemplate> _parametres ;
        
        /*!
          @deprecated
        */
        Opencxx::Ptree* parametres ;

        //@}
        

      
      };
  
    } 

  }  
}

#endif //_PU_COMPILATEUR_TYPE_TEMPLATE_H_
